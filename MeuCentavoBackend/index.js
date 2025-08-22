const express = require('express');
const mysql = require('mysql2/promise'); // Usamos a versão com "Promises" para um código mais limpo
const bcrypt = require('bcrypt');
const { body, validationResult } = require('express-validator');
const axios = require('axios');
const jwt = require('jsonwebtoken');
const app = express();
const port = 3000;
const multer = require('multer');
const { createWorker } = require('tesseract.js');
const upload = multer({ storage: multer.memoryStorage() }); // Configuração do Multer para guardar o ficheiro temporariamente em memória
const pdfjsLib = require('pdfjs-dist/legacy/build/pdf.js');
const { createCanvas } = require('canvas');


// Middleware para interpretar o corpo de requisições como JSON
app.use(express.json());

// Configuração da conexão com o banco de dados
const pool = mysql.createPool({
  host: 'localhost',
  user: 'bruno',
  password: '8243', // Sua senha
  database: 'meucentavodb',
  waitForConnections: true,
  connectionLimit: 10,
  queueLimit: 0,
  decimalNumbers: true
});

// --- LÓGICA DE COTAÇÃO DE CÂMBIO (VERSÃO CORRIGIDA) ---

// Cache em memória para evitar chamar a API a cada requisição
let cacheCotacoes = {
  timestamp: 0,
  taxas: null,
  promessaPendente: null // Guarda a requisição que está em andamento
};

async function obterCotacoes() {
  const agora = Date.now();
  // Validade do cache: 1 hora (3600000 milissegundos)
  if (cacheCotacoes.taxas && (agora - cacheCotacoes.timestamp < 3600000)) {
    console.log("Usando cotações do cache.");
    return cacheCotacoes.taxas;
  }

  // Se já existe uma requisição em andamento, não faça uma nova, apenas espere a existente terminar.
  if (cacheCotacoes.promessaPendente) {
    console.log("Aguardando requisição de cotação já em andamento...");
    return cacheCotacoes.promessaPendente;
  }

  // Cria a promessa da requisição e a armazena no cache
  cacheCotacoes.promessaPendente = (async () => {
    try {
      console.log("Buscando novas cotações da API externa...");
      const apiKey = '43948e889cc19dd294bbe5ea';
      const response = await axios.get(`https://v6.exchangerate-api.com/v6/${apiKey}/latest/BRL`);

      const taxasDaApi = response.data.conversion_rates;
      const taxasRelevantes = {
        BRL: 1,
        USD: taxasDaApi.USD,
        EUR: taxasDaApi.EUR
      };

      // Atualiza o cache com os dados e o tempo
      cacheCotacoes.taxas = taxasRelevantes;
      cacheCotacoes.timestamp = Date.now();
      
      return taxasRelevantes;

    } catch (error) {
      console.error("Erro ao buscar cotações:", error.message);
      // Em caso de erro, retorna taxas fixas para não quebrar a aplicação
      return { BRL: 1, USD: 5.0, EUR: 6.0 };
    } finally {
        // Independentemente de sucesso ou falha, limpa a promessa pendente
        cacheCotacoes.promessaPendente = null;
    }
  })();

  return cacheCotacoes.promessaPendente;
}

// Middleware para verificar o Token JWT
const authenticateToken = (req, res, next) => {
    const authHeader = req.headers['authorization'];
    const token = authHeader && authHeader.split(' ')[1]; // Formato "Bearer TOKEN"

    if (token == null) {
        return res.sendStatus(401); // Unauthorized - Nenhum token enviado
    }

    jwt.verify(token, 'sua_chave_super_secreta_pode_ser_qualquer_coisa', (err, user) => {
        if (err) {
            return res.sendStatus(403); // Forbidden - Token inválido ou expirado
        }
        req.user = user; // Salva os dados do usuário na requisição para uso futuro
        next(); // Continua para a rota
    });
};


// -----ROTAS DE USUARIO------

app.get('/', (req, res) => {
  res.send('<h1>Backend "Meu Centavo" no ar!</h1>');
});

app.get('/api/usuarios/inicial', async (req, res) => {
    try {
        const [users] = await pool.query('SELECT * FROM usuario ORDER BY user_id DESC LIMIT 1');
        if (users.length > 0) {
            res.json(users[0]); // Retorna o primeiro (e único) usuário encontrado
        } else {
            res.json({}); // Retorna um objeto vazio se não houver usuários
        }
    } catch (error) {
        res.status(500).json({ message: 'Erro interno do servidor.' });
    }
});



// Rota para REGISTRAR um novo usuário
app.post(
    '/api/usuarios/registrar',
    // Regras de validação
    body('username').isLength({ min: 3 }).withMessage('O nome de usuário precisa ter no mínimo 3 caracteres.'),
    body('password').isLength({ min: 6 }).withMessage('A senha precisa ter no mínimo 6 caracteres.'),

    async (req, res) => {
        // 1. Verifica se houve erros de validação
        const errors = validationResult(req);
        if (!errors.isEmpty()) {
            return res.status(400).json({ errors: errors.array() });
        }

        try {
            const { username, password } = req.body;

            // 2. Verifica se o usuário já existe no banco
            const [users] = await pool.query('SELECT * FROM usuario WHERE user_usuario = ?', [username]);
            if (users.length > 0) {
                return res.status(409).json({ message: 'Este nome de usuário já está em uso.' }); // 409 Conflict
            }

            // 3. Criptografa (hash) a senha
            const saltRounds = 10; // Fator de segurança
            const hashedPassword = await bcrypt.hash(password, saltRounds);

            // 4. Insere o novo usuário no banco de dados com a senha hasheada
            const [result] = await pool.query(
                'INSERT INTO usuario (user_usuario, user_password) VALUES (?, ?)',
                [username, hashedPassword]
            );

            // 5. Envia uma resposta de sucesso
            res.status(201).json({
                message: 'Usuário registrado com sucesso!',
                user: {
                    user_id: result.insertId,
                    user_usuario: username
                }
            });

        } catch (error) {
            console.error("Erro no registro:", error);
            res.status(500).json({ message: 'Erro interno do servidor.' });
        }
    }
);

// Rota para LOGAR um usuário existente (VERSÃO CORRIGIDA COM PERFIS)
app.post(
    '/api/usuarios/login',
    body('username').notEmpty().withMessage('O nome de usuário é obrigatório.'),
    body('password').notEmpty().withMessage('A senha é obrigatória.'),
    async (req, res) => {
        const errors = validationResult(req);
        if (!errors.isEmpty()) {
            return res.status(400).json({ errors: errors.array() });
        }

        try {
            const { username, password } = req.body;

            // 1. Encontra o usuário no banco de dados
            const [users] = await pool.query('SELECT * FROM usuario WHERE user_usuario = ?', [username]);
            if (users.length === 0) {
                return res.status(401).json({ message: 'Credenciais inválidas.' });
            }
            const user = users[0];

            // 2. Compara a senha
            const isPasswordCorrect = await bcrypt.compare(password, user.user_password);
            if (!isPasswordCorrect) {
                return res.status(401).json({ message: 'Credenciais inválidas.' });
            }

            // 3. Busca o perfil padrão (PF) do usuário para incluir no token
            const [perfis] = await pool.query(
                "SELECT id_perfil FROM perfis WHERE id_usuario = ? AND tipo_perfil = 'PF' LIMIT 1",
                [user.user_id]
            );

            if (perfis.length === 0) {
                // Isso não deveria acontecer para usuários existentes após a migração
                return res.status(500).json({ message: 'Erro: Perfil de usuário não encontrado.' });
            }
            const perfilPadraoId = perfis[0].id_perfil;


            // 4. Se a senha está correta, cria o JWT Token (agora com o perfilId)
            const payload = {
                userId: user.user_id,
                username: user.user_usuario,
                perfilId: perfilPadraoId // <-- USA A VARIÁVEL CORRETA
            };
            const secretKey = 'sua_chave_super_secreta_pode_ser_qualquer_coisa';
            const token = jwt.sign(payload, secretKey, { expiresIn: '1h' });

            // 5. Envia o token de volta para o cliente
            res.json({
                message: 'Login bem-sucedido!',
                token: token,
                user: {
                    user_id: user.user_id,
                    user_usuario: user.user_usuario
                }
            });

        } catch (error) {
            console.error("Erro no login:", error);
            res.status(500).json({ message: 'Erro interno do servidor.' });
        }
    }
);



// Rota para BUSCAR TODOS os usuários (protegida por autenticação)
app.get('/api/usuarios', authenticateToken, async (req, res) => {
    try {
        // Busca todos os usuários, selecionando apenas os campos necessários
        const [users] = await pool.query('SELECT user_id, user_usuario FROM usuario');
        res.json(users); // Retorna a lista de usuários como um array JSON
    } catch (error) {
        console.error("Erro ao buscar usuários:", error);
        res.status(500).json({ message: 'Erro interno do servidor.' });
    }
});

// Rota para BUSCAR um usuário específico pelo ID
app.get('/api/usuarios/:id', async (req, res) => {
    try {
        const { id } = req.params; // Captura o ID da URL (ex: o "22" de "/api/usuarios/22")

        // Busca no banco de dados pelo usuário com o ID correspondente
        const [users] = await pool.query('SELECT user_id, user_usuario FROM usuario WHERE user_id = ?', [id]);

        if (users.length > 0) {
            // Se encontrou, retorna o usuário como um objeto JSON
            res.json(users[0]);
        } else {
            // Se não encontrou nenhum usuário com esse ID, retorna 404 Not Found
            res.status(404).json({ message: 'Usuário não encontrado.' });
        }
    } catch (error) {
        console.error("Erro ao buscar usuário por ID:", error);
        res.status(500).json({ message: 'Erro interno do servidor.' });
    }
});

// Rota para EXCLUIR um usuário (protegida por autenticação) - VERSÃO CORRIGIDA
app.delete('/api/usuarios/:id', authenticateToken, async (req, res) => {
    try {
        // Precisamos extrair o 'id' dos parâmetros da URL e guardá-lo em uma variável.
        const idParaExcluir = req.params.id;

        const idDoRequisitante = req.user.userId; // ID de quem está logado (vem do token)

        // Verificação de auto-exclusão
        if (Number(idParaExcluir) === idDoRequisitante) {
            return res.status(403).json({ message: 'Você não pode excluir o seu próprio usuário.' });
        }

        // Agora usamos a variável 'idParaExcluir' que acabamos de criar na consulta.
        const [result] = await pool.query('DELETE FROM usuario WHERE user_id = ?', [idParaExcluir]);

        if (result.affectedRows > 0) {
            res.status(200).json({ message: 'Usuário excluído com sucesso.' });
        } else {
            res.status(404).json({ message: 'Usuário não encontrado.' });
        }

    } catch (error) {
        // A mensagem de erro que você viu no log do servidor vem daqui.
        console.error("Erro ao excluir usuário:", error);
        res.status(500).json({ message: 'Erro interno do servidor.' });
    }
});

// --- ROTAS PARA PERFIS (PF/PJ) ---
app.post('/api/perfis/selecionar/:id', authenticateToken, async (req, res) => {
    try {
        const idUsuario = req.user.userId;
        const idPerfilSelecionado = req.params.id;

        // --- CORREÇÃO AQUI ---
        // Agora também selecionamos o tipo_perfil para colocar no novo token
        const [perfis] = await pool.query(
            'SELECT id_perfil, tipo_perfil FROM perfis WHERE id_perfil = ? AND id_usuario = ?',
            [idPerfilSelecionado, idUsuario]
        );
        // --------------------

        if (perfis.length === 0) {
            return res.status(403).json({ message: 'Acesso ao perfil negado.' });
        }
        const perfilSelecionado = perfis[0];

        // Gera um novo token com o perfilId E o tipoPerfil atualizados
        const payload = {
            userId: req.user.userId,
            username: req.user.username,
            perfilId: perfilSelecionado.id_perfil,
            tipoPerfil: perfilSelecionado.tipo_perfil // <-- CAMPO ADICIONADO!
        };
        const secretKey = 'sua_chave_super_secreta_pode_ser_qualquer_coisa';
        const token = jwt.sign(payload, secretKey, { expiresIn: '1h' });

        res.json({ token: token });

    } catch (error) {
        console.error("Erro ao selecionar perfil:", error.message);
        res.status(500).json({ message: 'Erro interno do servidor.' });
    }
});


// Rota para BUSCAR TODOS os perfis do usuário logado
app.get('/api/perfis', authenticateToken, async (req, res) => {
    try {
        const idUsuario = req.user.userId;
        const [perfis] = await pool.query('SELECT * FROM perfis WHERE id_usuario = ?', [idUsuario]);
        res.json(perfis);
    } catch (error) {
        console.error("Erro ao buscar perfis:", error.message);
        res.status(500).json({ message: "Erro interno do servidor" });
    }
});

// Rota para ADICIONAR um novo perfil PJ
app.post('/api/perfis', authenticateToken, async (req, res) => {
    try {
        const { nome_perfil, documento, razao_social } = req.body;
        const idUsuario = req.user.userId;

        // Validação dos campos obrigatórios
        if (!nome_perfil) {
            return res.status(400).json({ message: 'O nome do perfil é obrigatório.' });
        }

        // Insere o novo perfil no banco de dados. O tipo 'PJ' é fixo.
        const [result] = await pool.query(
            'INSERT INTO perfis (id_usuario, nome_perfil, tipo_perfil, documento, razao_social) VALUES (?, ?, ?, ?, ?)',
            [idUsuario, nome_perfil, 'PJ', documento || null, razao_social || null]
        );

        // Retorna o perfil recém-criado
        res.status(201).json({
            id_perfil: result.insertId,
            id_usuario: idUsuario,
            nome_perfil: nome_perfil,
            tipo_perfil: 'PJ',
            documento: documento || null,
            razao_social: razao_social || null
        });

    } catch (error) {
        console.error("Erro ao adicionar perfil:", error.message);
        res.status(500).json({ message: "Erro interno do servidor" });
    }
});

// Rota para EXCLUIR um perfil PJ
app.delete('/api/perfis/:id', authenticateToken, async (req, res) => {
    try {
        const idPerfilParaExcluir = req.params.id;
        const idUsuario = req.user.userId;

        // 1. Busca o perfil para garantir que ele pertence ao usuário e que não é o perfil PF
        const [perfis] = await pool.query(
            'SELECT tipo_perfil FROM perfis WHERE id_perfil = ? AND id_usuario = ?',
            [idPerfilParaExcluir, idUsuario]
        );

        if (perfis.length === 0) {
            return res.status(404).json({ message: 'Perfil não encontrado ou não autorizado.' });
        }

        if (perfis[0].tipo_perfil === 'PF') {
            return res.status(403).json({ message: 'Não é permitido excluir o perfil principal de Pessoa Física.' });
        }

        // 2. Procede com a exclusão
        await pool.query('DELETE FROM perfis WHERE id_perfil = ?', [idPerfilParaExcluir]);

        res.status(200).json({ message: 'Perfil excluído com sucesso.' });

    } catch (error) {
        console.error("Erro ao excluir perfil:", error.message);
        res.status(500).json({ message: "Erro interno do servidor." });
    }
});

//------ROTAS DE LANÇAMENTO---------

// Rota para BUSCAR os lançamentos mais recentes (VERSÃO CORRIGIDA COM FILTRO DE PERFIL)
app.get('/api/lancamentos/recentes', authenticateToken, async (req, res) => {
    try {
        const usuarioId = req.user.userId;
        const idPerfil = req.user.perfilId; 
        const limite = parseInt(req.query.limite) || 5;

        // Adiciona o filtro AND id_perfil = ?
        const [lancamentos] = await pool.query(
            'SELECT * FROM lancamentos WHERE id_usuario = ? AND id_perfil = ? ORDER BY data_lancamento DESC, id DESC LIMIT ?',
            [usuarioId, idPerfil, limite]
        );
    
        res.json(lancamentos);

    } catch (error) {
        console.error("Erro ao buscar lançamentos recentes:", error);
        res.status(500).json({ message: 'Erro interno do servidor.' });
    }
});


// Rota para BUSCAR um resumo de receitas e despesas do mês atual
app.get('/api/lancamentos/resumo/mes', authenticateToken, async (req, res) => {
    try {
        const usuarioId = req.user.userId;
        const idPerfil = req.user.perfilId;
        
        // Adiciona o filtro AND id_perfil = ? à cláusula WHERE
        const [rows] = await pool.query(
            `SELECT tipo, SUM(valor) as total
             FROM lancamentos
             WHERE id_usuario = ? AND id_perfil = ? AND MONTH(data_lancamento) = MONTH(CURRENT_DATE()) AND YEAR(data_lancamento) = YEAR(CURRENT_DATE())
             GROUP BY tipo`,
            [usuarioId, idPerfil]
        );
        

        // Processa o resultado para enviar um JSON limpo para o C++
        let resumo = {
            receitas: 0.00,
            despesas: 0.00
        };

        for (const row of rows) {
            if (row.tipo === 'Receita') {
                resumo.receitas = parseFloat(row.total);
            } else if (row.tipo === 'Despesa') {
                resumo.despesas = parseFloat(row.total);
            }
        }

        res.json(resumo);

    } catch (error) {
        console.error("Erro ao buscar resumo do mês:", error);
        res.status(500).json({ message: 'Erro interno do servidor.' });
    }
});

// Rota para BUSCAR gastos agrupados por categoria (VERSÃO COM FILTROS)
app.get('/api/lancamentos/gastos/categoria', authenticateToken, async (req, res) => {
    try {
        const usuarioId = req.user.userId;
        const idPerfil = req.user.perfilId; // Pega o perfil ativo
        const { data_inicio, data_fim, id_conta } = req.query;

        // 1. Busca as taxas de câmbio atuais
        const taxas = await obterCotacoes();

        // Adiciona l.id_perfil = ? à lista de filtros
        let whereClauses = [`l.id_usuario = ?`, `l.id_perfil = ?`, `l.tipo = 'Despesa'`];
        let params = [usuarioId, idPerfil];

        // 2. Monta a query, mas usando as taxas reais
        const query = `
            SELECT
                cat.nome,
                SUM(
                    CASE
                        WHEN l.moeda_codigo_original = 'USD' THEN l.valor_original / ${taxas.USD}
                        WHEN l.moeda_codigo_original = 'EUR' THEN l.valor_original / ${taxas.EUR}
                        ELSE l.valor_original
                    END
                ) as total
            FROM lancamentos l
            JOIN categorias cat ON l.id_categoria = cat.id_categoria
            WHERE ${whereClauses.join(' AND ')}
            GROUP BY l.id_categoria, cat.nome
            ORDER BY total DESC
        `;

        const [gastos] = await pool.query(query, params);
        res.json(gastos);

    } catch (error) {
        console.error("Erro ao buscar gastos por categoria:", error);
        res.status(500).json({ message: 'Erro interno do servidor.' });
    }
});

// Rota para buscar o comparativo mensal de receitas e despesas
// Rota para buscar o comparativo mensal (VERSÃO FINAL E CORRIGIDA)
app.get('/api/lancamentos/comparativo/mensal', authenticateToken, async (req, res) => {
    try {
        const usuarioId = req.user.userId;
        const idPerfil = req.user.perfilId;

        // --- CORREÇÃO CRÍTICA AQUI ---
        // Extrai os filtros da query string da URL. Esta linha estava faltando.
        const { data_inicio, data_fim, id_conta } = req.query;
        // --------------------------------

        let whereClauses = [`id_usuario = ?`, `id_perfil = ?`];
        let params = [usuarioId, idPerfil];

        if (data_inicio) {
            whereClauses.push(`data_lancamento >= ?`);
            params.push(`${data_inicio} 00:00:00`);
        }
        if (data_fim) {
            whereClauses.push(`data_lancamento <= ?`);
            params.push(`${data_fim} 23:59:59`);
        }
        if (id_conta && id_conta != -1) {
            whereClauses.push(`id_conta = ?`);
            params.push(id_conta);
        }

        const query = `
            SELECT
                DATE_FORMAT(data_lancamento, '%Y-%m') as mes,
                SUM(CASE WHEN tipo = 'Receita' THEN valor ELSE 0 END) as receitas,
                SUM(CASE WHEN tipo = 'Despesa' THEN valor ELSE 0 END) as despesas
            FROM
                lancamentos
            WHERE ${whereClauses.join(' AND ')}
            GROUP BY
                YEAR(data_lancamento), MONTH(data_lancamento)
            ORDER BY
                mes ASC;
        `;

        const [results] = await pool.query(query, params);
        res.json(results);

    } catch (error) {
        console.error("Erro ao buscar comparativo mensal:", error.message);
        res.status(500).json({ message: 'Erro interno do servidor.' });
    }
});

// Rota para ADICIONAR um novo lançamento (VERSÃO FINAL E CORRIGIDA COM PERFIS)
app.post('/api/lancamentos/adicionar', authenticateToken, async (req, res) => {
    try {
        const { descricao, valor, data_lancamento, tipo, id_conta, id_categoria, id_meta,
                valor_original, moeda_codigo_original, taxa_cambio_usada } = req.body;
        
        // Pega o id_usuario E o id_perfil DO TOKEN da sessão ativa
        const id_usuario = req.user.userId;
        const id_perfil = req.user.perfilId; // <-- PONTO CRÍTICO 1

        if (!descricao || !valor || !data_lancamento || !tipo || !id_conta || !id_categoria) {
            return res.status(400).json({ message: 'Campos principais são obrigatórios.' });
        }
        if (!id_perfil) { // Segurança extra
            return res.status(400).json({ message: 'Perfil de usuário inválido na sessão.' });
        }

        // Adicionamos a coluna `id_perfil` à query INSERT
        const [result] = await pool.query(
            `INSERT INTO lancamentos (descricao, valor, data_lancamento, tipo, id_usuario, id_conta, id_categoria, id_meta, 
                                      valor_original, moeda_codigo_original, taxa_cambio_usada, id_perfil) 
             VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)`,
            [descricao, valor, data_lancamento, tipo, id_usuario, id_conta, id_categoria, id_meta || null,
             valor_original || valor, moeda_codigo_original || 'BRL', taxa_cambio_usada || 1, id_perfil] // <-- Passa o id_perfil para a query
        );

        // --- INÍCIO DA LÓGICA DE APRENDIZADO (VERSÃO APRIMORADA) ---
        (async () => {
            try {
                // Palavras comuns a serem ignoradas (stopwords)
                const stopwords = new Set(['DE', 'DO', 'DA', 'A', 'O', 'E', 'NO', 'NA', 'PARA', 'COM', 'EM']);
                
                // 1. Limpa a descrição e a divide em palavras-chave potenciais
                const palavrasChave = descricao.toUpperCase()
                                            .replace(/[^A-Z0-9\s]/g, '') // Remove pontuação
                                            .split(' ')
                                            .filter(p => p.length > 3 && !stopwords.has(p)); // Filtra palavras curtas e stopwords

                if (palavrasChave.length > 0) {
                    console.log(`Backend: Aprendendo com as palavras-chave: [${palavrasChave.join(', ')}] para a categoria ID ${id_categoria}`);
                    
                    // 2. Para cada palavra-chave encontrada, cria ou atualiza uma regra de mapeamento
                    for (const palavra of palavrasChave) {
                        const mapeamentoQuery = `
                            INSERT INTO mapeamentos_categorias (id_perfil, palavra_chave, id_categoria_sugerida)
                            VALUES (?, ?, ?)
                            ON DUPLICATE KEY UPDATE id_categoria_sugerida = ?;
                        `;
                        await pool.query(mapeamentoQuery, [id_perfil, palavra, id_categoria, id_categoria]);
                    }
                }
            } catch (learnError) {
                console.error("Erro no processo de aprendizado de categoria:", learnError.message);
            }
        })();
        // --- FIM DA LÓGICA DE APRENDIZADO ---

        res.status(201).json({ message: 'Lançamento adicionado com sucesso!', insertId: result.insertId });

    } catch (error) {
        console.error("Erro ao adicionar lançamento:", error);
        res.status(500).json({ message: 'Erro interno do servidor.' });
    }
});

// --- ROTA PARA SUGERIR CATEGORIAS (VERSÃO MELHORADA) ---
app.post('/api/categorias/sugerir', authenticateToken, async (req, res) => {
    try {
        const idPerfil = req.user.perfilId;
        const { descricoes } = req.body;

        if (!descricoes || !Array.isArray(descricoes)) {
            return res.status(400).json({ message: 'O corpo da requisição deve conter um array de "descricoes".' });
        }

        // 1. Pega TODOS os mapeamentos que o sistema já aprendeu para este perfil.
        const [mapeamentos] = await pool.query(
            'SELECT palavra_chave, id_categoria_sugerida FROM mapeamentos_categorias WHERE id_perfil = ?',
            [idPerfil]
        );

        if (mapeamentos.length === 0) {
            // Se não aprendeu nada ainda, retorna uma resposta vazia rapidamente.
            return res.json({ sugestoes: [] });
        }

        const sugestoes = [];

        // 2. Para cada descrição nova que o frontend enviou...
        for (const descricao of descricoes) {
            let idCategoriaSugerida = null;
            const descricaoUpper = descricao.toUpperCase(); // Converte a descrição para maiúsculas uma vez.

            // 3. ...procure por CADA palavra-chave que o sistema já conhece.
            for (const mapeamento of mapeamentos) {
                // 4. Se a descrição contiver a palavra-chave...
                if (descricaoUpper.includes(mapeamento.palavra_chave)) {
                    // ...encontramos uma sugestão!
                    idCategoriaSugerida = mapeamento.id_categoria_sugerida;
                    break; // Para o loop interno e vai para a próxima descrição.
                }
            }

            sugestoes.push({
                descricaoOriginal: descricao,
                idCategoriaSugerida: idCategoriaSugerida
            });
        }

        res.json({ sugestoes });

    } catch (error) {
        console.error("Erro ao sugerir categorias:", error.message);
        res.status(500).json({ message: "Erro interno do servidor" });
    }
});

// Rota para BUSCAR TODOS os lançamentos do usuário logado (VERSÃO FINAL COM FILTRO DE PERFIL)
app.get('/api/lancamentos', authenticateToken, async (req, res) => {
    try {
        const usuarioId = req.user.userId;
        const idPerfil = req.user.perfilId; // <-- Pega o perfil ativo do token

        if (!idPerfil) {
            return res.status(400).json({ message: "Nenhum perfil ativo na sessão." });
        }

        const { data_inicio, data_fim, id_conta } = req.query;

        // Adicionamos l.id_perfil = ? à lista de filtros
        let whereClauses = [`l.id_usuario = ?`, `l.id_perfil = ?`];
        let params = [usuarioId, idPerfil];


        if (data_inicio) {
            whereClauses.push(`l.data_lancamento >= ?`);
            params.push(`${data_inicio} 00:00:00`);
        }   
        if (data_fim) {
            whereClauses.push(`l.data_lancamento <= ?`);
            params.push(`${data_fim} 23:59:59`);
        }
        if (id_conta && id_conta != -1) {
            whereClauses.push(`l.id_conta = ?`);
            params.push(id_conta);
        }

        const query = `
             SELECT
                l.*,
                c.nome as nome_conta,
                cat.nome as nome_categoria
             FROM lancamentos l
             LEFT JOIN contas c ON l.id_conta = c.id_conta
             LEFT JOIN categorias cat ON l.id_categoria = cat.id_categoria
             WHERE ${whereClauses.join(' AND ')}
             ORDER BY l.data_lancamento DESC, l.id DESC`;

        console.log("Executando Query:", query);
        console.log("Com Parâmetros:", params);

        const [lancamentos] = await pool.query(query, params);
        res.json(lancamentos);

    } catch (error) {
        console.error("Erro ao buscar lançamentos:", error);
        res.status(500).json({ message: 'Erro interno do servidor.' });
    }
});


// Rota para EDITAR (Atualizar) um lançamento existente (VERSÃO FINAL E CORRIGIDA)
app.put('/api/lancamentos/:id', authenticateToken, async (req, res) => {
    try {
        // 1. Coleta TODOS os dados do corpo da requisição, incluindo os de moeda
        const { descricao, valor, data_lancamento, tipo, id_conta, id_categoria,
                valor_original, moeda_codigo_original, taxa_cambio_usada } = req.body;
        
        const idLancamento = req.params.id;
        const idUsuario = req.user.userId;
        const idPerfil = req.user.perfilId;

        // Validação
        if (!descricao || !valor || !data_lancamento || !tipo || !id_conta || !id_categoria) {
            return res.status(400).json({ message: 'Todos os campos são obrigatórios.' });
        }

        // --- CORREÇÃO CRÍTICA AQUI ---
        // A query UPDATE agora inclui os campos valor_original e moeda_codigo_original
        const query = `
            UPDATE lancamentos 
            SET 
                descricao = ?, valor = ?, data_lancamento = ?, tipo = ?, 
                id_conta = ?, id_categoria = ?, valor_original = ?, moeda_codigo_original = ?, 
                taxa_cambio_usada = ?
            WHERE 
                id = ? AND id_usuario = ? AND id_perfil = ?
        `;
        
        const params = [
            descricao, valor, data_lancamento, tipo, id_conta, id_categoria,
            valor_original || valor, // Usa o valor_original se existir, senão o valor principal
            moeda_codigo_original || 'BRL',
            taxa_cambio_usada || 1,
            idLancamento, idUsuario, idPerfil
        ];

        const [result] = await pool.query(query, params);
        // --- FIM DA CORREÇÃO ---

        if (result.affectedRows > 0) {
            res.status(200).json({ message: 'Lançamento atualizado com sucesso.' });
        } else {
            res.status(404).json({ message: 'Lançamento não encontrado ou não autorizado para este perfil.' });
        }

    } catch (error) {
        console.error("Erro ao editar lançamento:", error);
        res.status(500).json({ message: "Erro interno do servidor ao editar lançamento." });
    }
});


// Rota para EXCLUIR um lançamento 
app.delete('/api/lancamentos/:id', authenticateToken, async (req, res) => {
    try {
        const idLancamento = req.params.id;
        const idUsuario = req.user.userId;
        const idPerfil = req.user.perfilId;

        const [result] = await pool.query(
            'DELETE FROM lancamentos WHERE id = ? AND id_usuario = ? AND id_perfil = ?',
            [idLancamento, idUsuario, idPerfil]
        );

        if (result.affectedRows > 0) {
            res.status(200).json({ message: 'Lançamento excluído com sucesso.' });
        } else {
            res.status(404).json({ message: 'Lançamento não encontrado ou não autorizado.' });
        }
    } catch (error) {
        console.error("Erro ao excluir lançamento:", error);
        res.status(500).json({ message: "Erro interno do servidor ao excluir lançamento." });
    }
});

// --- ROTA PARA TENDÊNCIA DE GASTOS POR CATEGORIA ---
app.get('/api/relatorios/tendencia-categoria', authenticateToken, async (req, res) => {
    try {
        const idUsuario = req.user.userId;
        const idPerfil = req.user.perfilId;
        const { id_categoria, meses_atras } = req.query;

        if (!id_categoria) {
            return res.status(400).json({ message: 'O ID da categoria é obrigatório.' });
        }

        const numMeses = parseInt(meses_atras) || 6; // Padrão de 6 meses se não for especificado

        // Query que busca os gastos da categoria especificada, agrupados por mês
        const query = `
            SELECT
                DATE_FORMAT(data_lancamento, '%Y-%m') as mes,
                SUM(valor) as total_gasto -- Assume que 'valor' está na moeda principal (BRL)
            FROM
                lancamentos
            WHERE
                id_usuario = ?
                AND id_perfil = ?
                AND id_categoria = ?
                AND tipo = 'Despesa'
                AND data_lancamento >= CURDATE() - INTERVAL ? MONTH
            GROUP BY
                YEAR(data_lancamento), MONTH(data_lancamento)
            ORDER BY
                mes ASC;
        `;

        const [tendencia] = await pool.query(query, [idUsuario, idPerfil, id_categoria, numMeses]);
        res.json(tendencia);

    } catch (error) {
        console.error("Erro ao buscar tendência da categoria:", error.message);
        res.status(500).json({ message: "Erro interno do servidor" });
    }
});

// --- ROTA PARA O RELATÓRIO DRE (DEMONSTRATIVO DE RESULTADOS) ---
app.get('/api/relatorios/dre', authenticateToken, async (req, res) => {
    try {
        const idPerfil = req.user.perfilId;
        const { data_inicio, data_fim } = req.query;

        // Validação
        if (!data_inicio || !data_fim) {
            return res.status(400).json({ message: 'Data de início e fim são obrigatórias.' });
        }
        if (!idPerfil) {
            return res.status(400).json({ message: 'Nenhum perfil ativo na sessão.' });
        }

        // 1. Busca todos os totais agrupados pela classificação contábil no período
        const query = `
            SELECT
                c.classificacao_contabil,
                SUM(l.valor_original) as total
            FROM lancamentos l
            JOIN categorias c ON l.id_categoria = c.id_categoria
            WHERE l.id_perfil = ? AND l.data_lancamento BETWEEN ? AND ?
            GROUP BY c.classificacao_contabil;
        `;
        const [resultados] = await pool.query(query, [idPerfil, `${data_inicio} 00:00:00`, `${data_fim} 23:59:59`]);

        // 2. Estrutura os resultados no formato de um DRE
        const dre = {
            'Receita Bruta': 0,
            'Dedução da Receita': 0,
            'Receita Líquida': 0,
            'Custo do Serviço/Produto': 0,
            'Lucro Bruto': 0,
            'Despesa Operacional': 0,
            'Lucro Operacional': 0,
            'Receita Financeira': 0,
            'Despesa Financeira': 0,
            'Resultado Antes dos Impostos': 0,
            'Imposto sobre o Lucro': 0,
            'Lucro Líquido': 0
        };

        // Preenche o DRE com os dados do banco
        resultados.forEach(r => {
            if (dre.hasOwnProperty(r.classificacao_contabil)) {
                dre[r.classificacao_contabil] = parseFloat(r.total);
            }
        });

        // 3. Calcula os subtotais
        dre['Receita Líquida'] = dre['Receita Bruta'] - dre['Dedução da Receita'];
        dre['Lucro Bruto'] = dre['Receita Líquida'] - dre['Custo do Serviço/Produto'];
        dre['Lucro Operacional'] = dre['Lucro Bruto'] - dre['Despesa Operacional'];
        dre['Resultado Antes dos Impostos'] = dre['Lucro Operacional'] + dre['Receita Financeira'] - dre['Despesa Financeira'];
        dre['Lucro Líquido'] = dre['Resultado Antes dos Impostos'] - dre['Imposto sobre o Lucro'];

        res.json(dre);

    } catch (error) {
        console.error("Erro ao gerar DRE:", error.message);
        res.status(500).json({ message: "Erro interno do servidor" });
    }
});

// --- ROTA PARA O RELATÓRIO DE FLUXO DE CAIXA ---
app.get('/api/relatorios/fluxo-caixa', authenticateToken, async (req, res) => {
    try {
        const idPerfil = req.user.perfilId;
        const { data_inicio, data_fim } = req.query;

        if (!data_inicio || !data_fim) {
            return res.status(400).json({ message: 'Data de início e fim são obrigatórias.' });
        }

        // 1. Calcula o Saldo Inicial (soma de todos os saldos de contas no início do período)
        // Esta é uma query simplificada; uma versão mais complexa calcularia o saldo exato.
        const [saldoInicialData] = await pool.query(
            'SELECT SUM(saldo_inicial) as total FROM contas WHERE id_perfil = ?',
            [idPerfil]
        );
        const saldoInicial = parseFloat(saldoInicialData[0].total) || 0;
        
        // 2. Calcula o total de Entradas (Receitas) e Saídas (Despesas) no período
        const [fluxoData] = await pool.query(
            `SELECT
                SUM(CASE WHEN tipo = 'Receita' THEN valor_original ELSE 0 END) as total_entradas,
                SUM(CASE WHEN tipo = 'Despesa' THEN valor_original ELSE 0 END) as total_saidas
            FROM lancamentos
            WHERE id_perfil = ? AND data_lancamento BETWEEN ? AND ?`,
            [idPerfil, `${data_inicio} 00:00:00`, `${data_fim} 23:59:59`]
        );

        const totalEntradas = parseFloat(fluxoData[0].total_entradas) || 0;
        const totalSaidas = parseFloat(fluxoData[0].total_saidas) || 0;

        // 3. Monta o resultado final
        const fluxoDeCaixa = {
            'Saldo Inicial': saldoInicial,
            'Total de Entradas': totalEntradas,
            'Total de Saídas': totalSaidas,
            'Fluxo de Caixa Líquido': totalEntradas - totalSaidas,
            'Saldo Final': saldoInicial + totalEntradas - totalSaidas
        };
        
        console.log(`Backend: Enviando dados do Fluxo de Caixa para o perfil ${idPerfil}:`, fluxoDeCaixa);
        
        res.json(fluxoDeCaixa);

    } catch (error) {
        console.error("Erro ao gerar Fluxo de Caixa:", error.message);
        res.status(500).json({ message: "Erro interno do servidor" });
    }
});

// --- ROTAS DE CATEGORIAS  ---

// Rota para BUSCAR TODAS as categorias do usuário logado (VERSÃO CORRIGIDA COM FILTRO DE PERFIL)
app.get('/api/categorias', authenticateToken, async (req, res) => {
    try {
        const idUsuario = req.user.userId;
        const idPerfil = req.user.perfilId; // Pega o perfil ativo do token

        // Segurança extra para garantir que o perfil existe na sessão
        if (!idPerfil) {
            return res.status(400).json({ message: "Nenhum perfil ativo na sessão. Faça login novamente." });
        }

        // --- CORREÇÃO AQUI ---
        // Adiciona o filtro "AND id_perfil = ?" para buscar apenas as categorias do perfil ativo.
        const [categorias] = await pool.query(
            'SELECT * FROM categorias WHERE id_usuario = ? AND id_perfil = ?',
            [idUsuario, idPerfil]
        );

        res.json(categorias);
    } catch (error) {
        console.error("Erro ao buscar categorias:", error);
        res.status(500).json({ message: "Erro interno do servidor" });
    }
});


// Rota para ADICIONAR uma nova categoria (VERSÃO ATUALIZADA PARA PJ)
app.post('/api/categorias', authenticateToken, async (req, res) => {
    try {
        // 1. Extrai o novo campo opcional do corpo da requisição
        const { nome, tipo, classificacao_contabil } = req.body;
        const idUsuario = req.user.userId;
        const idPerfil = req.user.perfilId; // Pega o perfil ativo

        // Validações básicas
        if (!nome || !tipo) {
            return res.status(400).json({ message: 'O nome e o tipo da categoria são obrigatórios.' });
        }

        // 2. Adiciona a coluna e o valor na query INSERT
        const [result] = await pool.query(
            'INSERT INTO categorias (nome, tipo, id_usuario, id_perfil, classificacao_contabil) VALUES (?, ?, ?, ?, ?)',
            [nome, tipo, idUsuario, idPerfil, classificacao_contabil || null]
        );

        res.status(201).json({
            id_categoria: result.insertId,
            nome: nome,
            tipo: tipo,
            id_usuario: idUsuario,
            id_perfil: idPerfil,
            classificacao_contabil: classificacao_contabil || null
        });

    } catch (error) {
        console.error("Erro ao adicionar categoria:", error);
        res.status(500).json({ message: "Erro interno do servidor" });
    }
});

// Rota para EDITAR uma categoria existente (VERSÃO ATUALIZADA PARA PJ)
app.put('/api/categorias/:id', authenticateToken, async (req, res) => {
    try {
        // 1. Extrai o novo campo opcional
        const { nome, classificacao_contabil } = req.body;
        const idCategoria = req.params.id;
        const idPerfil = req.user.perfilId;
        
        if (!nome) {
            return res.status(400).json({ message: 'O novo nome é obrigatório.' });
        }

        // 2. Adiciona o novo campo à query UPDATE
        const [result] = await pool.query(
            'UPDATE categorias SET nome = ?, classificacao_contabil = ? WHERE id_categoria = ? AND id_perfil = ?',
            [nome, classificacao_contabil || null, idCategoria, idPerfil]
        );

        if (result.affectedRows > 0) {
            res.status(200).json({ message: 'Categoria atualizada com sucesso.' });
        } else {
            res.status(404).json({ message: 'Categoria não encontrada ou não autorizada para este perfil.' });
        }
    } catch (error) {
        console.error("Erro ao editar categoria:", error);
        res.status(500).json({ message: "Erro interno do servidor" });
    }
});


// Rota para EXCLUIR uma categoria existente
app.delete('/api/categorias/:id', authenticateToken, async (req, res) => {
    try {
        const idCategoria = req.params.id;
        const idUsuario = req.user.userId;

        const [result] = await pool.query(
            'DELETE FROM categorias WHERE id_categoria = ? AND id_usuario = ?',
            [idCategoria, idUsuario]
        );

        if (result.affectedRows > 0) {
            res.status(200).json({ message: 'Categoria excluída com sucesso.' });
        } else {
            res.status(404).json({ message: 'Categoria não encontrada ou não autorizada.' });
        }
    } catch (error) {
        console.error("Erro ao excluir categoria:", error);
        res.status(500).json({ message: "Erro interno do servidor" });
    }
});

// Rota para BUSCAR TODAS as contas do usuário logado
app.get('/api/contas', authenticateToken, async (req, res) => {
    try {
        const idUsuario = req.user.userId;
        const idPerfil = req.user.perfilId;
        // Busca todas as contas que pertencem ao usuário, ordenadas por nome
        const [contas] = await pool.query(
            'SELECT * FROM contas WHERE id_usuario = ? AND id_perfil = ? ORDER BY nome ASC', 
            [idUsuario, idPerfil] 
        );
        res.json(contas);
    } catch (error) {
        console.error("Erro ao buscar contas:", error);
        res.status(500).json({ message: "Erro interno do servidor ao buscar contas." });
    }
});


// Rota para ADICIONAR uma nova conta (VERSÃO FINAL E CORRIGIDA COM PERFIS)
app.post('/api/contas', authenticateToken, async (req, res) => {
    try {
        // Pega os dados enviados pelo formulário
        const { nome, tipo_conta, saldo_inicial, moeda_codigo, taxa_juros, valor_total_divida, data_vencimento } = req.body;
        
        // Pega o id_usuario E o id_perfil DO TOKEN da sessão ativa
        const idUsuario = req.user.userId;
        const idPerfil = req.user.perfilId; // <-- PONTO CRÍTICO 1

        // Validação
        if (!nome || !tipo_conta || !moeda_codigo) {
            return res.status(400).json({ message: 'Nome, tipo e moeda da conta são obrigatórios.' });
        }
        if (!idPerfil) { // Segurança extra para garantir que o perfil existe no token
             return res.status(400).json({ message: 'Perfil de usuário inválido na sessão. Faça login novamente.' });
        }

        // --- CORREÇÃO AQUI ---
        // Adicionamos a coluna `id_perfil` à query INSERT
        const [result] = await pool.query(
            'INSERT INTO contas (nome, tipo_conta, saldo_inicial, id_usuario, moeda_codigo, taxa_juros, valor_total_divida, data_vencimento, id_perfil) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)',
            [nome, tipo_conta, saldo_inicial || 0.00, idUsuario, moeda_codigo, taxa_juros || null, valor_total_divida || null, data_vencimento || null, idPerfil] // <-- PONTO CRÍTICO 2: Passa o idPerfil para a query
        );

        res.status(201).json({ message: 'Conta/Dívida adicionada com sucesso!', insertId: result.insertId });

    } catch (error) {
        console.error("Erro ao adicionar conta:", error);
        res.status(500).json({ message: "Erro interno do servidor ao adicionar conta." });
    }
});

// Rota para EDITAR (Atualizar) uma conta existente (agora com campos de dívida)
app.put('/api/contas/:id', authenticateToken, async (req, res) => {
    try {
        // 1. Desestruture os novos campos opcionais
        const { nome, tipo_conta, saldo_inicial, moeda_codigo, taxa_juros, valor_total_divida, data_vencimento } = req.body;
        const idConta = req.params.id;
        const idUsuario = req.user.userId;

        // Validação principal (continua a mesma)
        if (!nome || !tipo_conta || saldo_inicial === undefined || !moeda_codigo) {
            return res.status(400).json({ message: 'Todos os campos são obrigatórios.' });
        }

        // 2. Adicione as novas colunas e valores ao UPDATE
        const [result] = await pool.query(
            'UPDATE contas SET nome = ?, tipo_conta = ?, saldo_inicial = ?, moeda_codigo = ?, taxa_juros = ?, valor_total_divida = ?, data_vencimento = ? WHERE id_conta = ? AND id_usuario = ?',
            [nome, tipo_conta, saldo_inicial, moeda_codigo, taxa_juros || null, valor_total_divida || null, data_vencimento || null, idConta, idUsuario]
        );

        if (result.affectedRows > 0) {
            res.status(200).json({ message: 'Conta/Dívida atualizada com sucesso.' });
        } else {
            res.status(404).json({ message: 'Conta não encontrada ou não autorizada.' });
        }
    } catch (error) {
        console.error("Erro ao editar conta:", error);
        res.status(500).json({ message: "Erro interno do servidor ao editar conta." });
    }
});

// Rota para EXCLUIR uma conta existente
app.delete('/api/contas/:id', authenticateToken, async (req, res) => {
    try {
        const idConta = req.params.id;
        const idUsuario = req.user.userId;

        // A condição 'AND id_usuario = ?' também é CRÍTICA aqui.
        const [result] = await pool.query(
            'DELETE FROM contas WHERE id_conta = ? AND id_usuario = ?',
            [idConta, idUsuario]
        );

        if (result.affectedRows > 0) {
            res.status(200).json({ message: 'Conta excluída com sucesso.' });
        } else {
            res.status(404).json({ message: 'Conta não encontrada ou não autorizada.' });
        }
    } catch (error) {
        // Se a conta tiver lançamentos associados, poderá dar um erro de Foreign Key.
        // É importante tratar isso no futuro, mas por agora esta é a base.
        console.error("Erro ao excluir conta:", error);
        res.status(500).json({ message: "Erro interno do servidor ao excluir conta." });
    }
});

// --- ROTAS PARA METAS ---

// Rota para BUSCAR TODAS as metas do usuário logado
app.get('/api/metas', authenticateToken, async (req, res) => {
    try {
        const idUsuario = req.user.userId;
        const idPerfil = req.user.perfilId;

        // 1. Busca as taxas de câmbio atuais
        const taxas = await obterCotacoes();

        // 2. Monta a query usando as taxas
        const query = `
            SELECT
                m.id_meta, m.nome, m.valor_alvo, m.moeda_codigo, m.data_alvo,
                COALESCE(SUM(
                    l.valor_original *
                    CASE l.moeda_codigo_original
                        WHEN 'USD' THEN 1 / ${taxas.USD}
                        WHEN 'EUR' THEN 1 / ${taxas.EUR}
                        ELSE 1.0
                    END
                    /
                    CASE m.moeda_codigo
                        WHEN 'USD' THEN 1 / ${taxas.USD}
                        WHEN 'EUR' THEN 1 / ${taxas.EUR}
                        ELSE 1.0
                    END
                ), 0) as valor_atual
            FROM metas m
            LEFT JOIN lancamentos l ON m.id_meta = l.id_meta AND l.tipo = 'Receita' AND l.id_perfil = m.id_perfil            
            WHERE m.id_usuario = ? AND m.id_perfil = ?
            GROUP BY m.id_meta
            ORDER BY m.data_alvo ASC;
        `;
        const [metas] = await pool.query(query, [idUsuario, idPerfil]);
        res.json(metas);
    } catch (error) {
        console.error("Erro ao buscar metas:", error);
        res.status(500).json({ message: "Erro interno do servidor" });
    }
});

// Rota para ADICIONAR uma nova meta
app.post('/api/metas', authenticateToken, async (req, res) => {
    try {
        
        // 2. Desestruture o novo campo moeda_codigo que virá do frontend
        const { nome, valor_alvo, data_alvo, moeda_codigo } = req.body;
        const idUsuario = req.user.userId;

        // 3. Adicione a validação para o novo campo
        if (!nome || !valor_alvo || !moeda_codigo) {
            return res.status(400).json({ message: 'O nome, valor alvo e moeda da meta são obrigatórios.' });
        }

        // 4. Adicione a coluna e o valor na query INSERT
        const [result] = await pool.query(
            'INSERT INTO metas (id_usuario, nome, valor_alvo, data_alvo, moeda_codigo, id_perfil) VALUES (?, ?, ?, ?, ?, ?)', // Coluna adicionada
            [req.user.userId, nome, valor_alvo, data_alvo || null, moeda_codigo, req.user.perfilId] // Valor adicionado
        
        );

        res.status(201).json({ message: 'Meta criada com sucesso!', id_meta: result.insertId });

    } catch (error) {
        console.error("Erro ao adicionar meta:", error);
        res.status(500).json({ message: "Erro interno do servidor" });
    }
});

// Rota para EDITAR (Atualizar) uma meta existente
app.put('/api/metas/:id', authenticateToken, async (req, res) => {
    try {
        // 5. Desestruture o novo campo moeda_codigo
        const { nome, valor_alvo, data_alvo, moeda_codigo } = req.body;
        const idMeta = req.params.id;
        const idUsuario = req.user.userId;

        // 6. Adicione a validação
        if (!nome || !valor_alvo || !moeda_codigo) {
            return res.status(400).json({ message: 'Nome, valor alvo e moeda são obrigatórios.' });
        }

        // 7. Adicione o campo na query UPDATE
        const [result] = await pool.query(
            'UPDATE metas SET nome = ?, valor_alvo = ?, data_alvo = ?, moeda_codigo = ? WHERE id_meta = ? AND id_usuario = ? AND id_perfil = ?', 
            [nome, valor_alvo, data_alvo || null, moeda_codigo, req.params.id, req.user.userId, req.user.perfilId]
        );

        if (result.affectedRows > 0) {
            res.status(200).json({ message: 'Meta atualizada com sucesso.' });
        } else {
            res.status(404).json({ message: 'Meta não encontrada ou não autorizada.' });
        }
    } catch (error) {
        console.error("Erro ao editar meta:", error);
        res.status(500).json({ message: "Erro interno do servidor" });
    }
});

// Rota para EXCLUIR uma meta
app.delete('/api/metas/:id', authenticateToken, async (req, res) => {
    try {
        const idMeta = req.params.id;
        const idUsuario = req.user.userId;

        const [result] = await pool.query(
            'DELETE FROM metas WHERE id_meta = ? AND id_usuario = ?',
            [idMeta, idUsuario]
        );

        if (result.affectedRows > 0) {
            res.status(200).json({ message: 'Meta excluída com sucesso.' });
        } else {
            res.status(404).json({ message: 'Meta não encontrada ou não autorizada.' });
        }
    } catch (error) {
        console.error("Erro ao excluir meta:", error);
        res.status(500).json({ message: "Erro interno do servidor" });
    }
});

// --- ROTAS PARA INVESTIMENTOS (ATIVOS) ---

// Rota para BUSCAR A POSIÇÃO CONSOLIDADA da carteira do usuário
app.get('/api/ativos/portfolio', authenticateToken, async (req, res) => {
    try {
        const idUsuario = req.user.userId;
        const idPerfil = req.user.perfilId;

        // Query complexa que junta ativos e operações para calcular os totais
        const query = `
            SELECT
                a.id_ativo,
                a.ticker,
                a.nome,
                a.tipo_ativo,
                COALESCE(SUM(CASE WHEN op.tipo_operacao = 'Compra' THEN op.quantidade ELSE -op.quantidade END), 0) as quantidade_total,
                COALESCE(SUM(CASE WHEN op.tipo_operacao = 'Compra' THEN op.quantidade * op.preco_unitario + op.custos ELSE 0 END), 0) as custo_total
            FROM
                ativos a
            LEFT JOIN
                operacoes_investimentos op ON a.id_ativo = op.id_ativo
            WHERE
                a.id_usuario = ? AND a.id_perfil = ?
            GROUP BY
                a.id_ativo, a.ticker, a.nome, a.tipo_ativo
            HAVING
                quantidade_total > 0 -- Opcional: mostra apenas ativos que o usuário ainda possui
            ORDER BY
                custo_total DESC;
        `;

        const [portfolio] = await pool.query(query, [idUsuario, idPerfil]);
        res.json(portfolio);

    } catch (error) {
        console.error("Erro ao buscar portfólio consolidado:", error);
        res.status(500).json({ message: "Erro interno do servidor" });
    }
});

// Rota para BUSCAR TODOS os ativos da carteira do usuário
app.get('/api/ativos', authenticateToken, async (req, res) => {
    try {
        const idUsuario = req.user.userId;
        // NENHUMA MUDANÇA NECESSÁRIA AQUI. "SELECT *" já inclui a nova coluna moeda_codigo.
        const [ativos] = await pool.query('SELECT * FROM ativos WHERE id_usuario = ? ORDER BY tipo_ativo, ticker ASC', [idUsuario]);
        res.json(ativos);
    } catch (error) {
        console.error("Erro ao buscar ativos:", error);
        res.status(500).json({ message: "Erro interno do servidor" });
    }
});

// Rota para ADICIONAR um novo ativo na carteira
app.post('/api/ativos', authenticateToken, async (req, res) => {
    try {
        // 1. Desestruture o novo campo
        const { ticker, nome, tipo_ativo, moeda_codigo } = req.body;
        const idUsuario = req.user.userId;

        // 2. Adicione à validação
        if (!ticker || !tipo_ativo || !moeda_codigo) {
            return res.status(400).json({ message: 'O ticker, tipo e moeda do ativo são obrigatórios.' });
        }

        // 3. Adicione ao INSERT
        const [result] = await pool.query(
            'INSERT INTO ativos (id_usuario, ticker, nome, tipo_ativo, moeda_codigo, id_perfil) VALUES (?, ?, ?, ?, ?, ?)', 
            [req.user.userId, ticker.toUpperCase(), nome, tipo_ativo, moeda_codigo, req.user.perfilId] 
        );

        res.status(201).json({ message: 'Ativo adicionado com sucesso!', id_ativo: result.insertId });

    } catch (error) {
        if (error.code === 'ER_DUP_ENTRY') {
            return res.status(409).json({ message: 'Este ticker já está cadastrado na sua carteira.' });
        }
        console.error("Erro ao adicionar ativo:", error);
        res.status(500).json({ message: "Erro interno do servidor" });
    }
});

// Rota para BUSCAR TODAS as operações de um ATIVO específico
app.get('/api/ativos/:id/operacoes', authenticateToken, async (req, res) => {
    try {
        const idAtivo = req.params.id;
        const idUsuario = req.user.userId;

        // NENHUMA MUDANÇA NECESSÁRIA. "SELECT op.*" já inclui as novas colunas.
        const [operacoes] = await pool.query(
            `SELECT op.* FROM operacoes_investimentos op
             JOIN ativos a ON op.id_ativo = a.id_ativo
             WHERE op.id_ativo = ? AND a.id_usuario = ?
             ORDER BY op.data_operacao DESC`,
            [idAtivo, idUsuario]
        );

        res.json(operacoes);
    } catch (error) {
        console.error("Erro ao buscar operações do ativo:", error);
        res.status(500).json({ message: "Erro interno do servidor" });
    }
});

// Rota para BUSCAR TODOS os dividendos de um ATIVO específico
app.get('/api/ativos/:id/dividendos', authenticateToken, async (req, res) => {
    try {
        const { id } = req.params;
        const id_usuario = req.user.userId;

        // A query verifica se o ativo pertence ao usuário logado como uma camada de segurança
        const [dividendos] = await pool.query(
            `SELECT d.* FROM dividendos d
             JOIN ativos a ON d.id_ativo = a.id_ativo
             WHERE d.id_ativo = ? AND a.id_usuario = ?
             ORDER BY d.data_pagamento DESC`,
            [id, id_usuario]
        );

        res.json(dividendos);

    } catch (error) {
        console.error("Erro ao buscar dividendos:", error.message);
        res.status(500).json({ message: 'Erro interno do servidor.' });
    }
});

// Rota para EDITAR um ativo existente (ex: corrigir o nome)
app.put('/api/ativos/:id', authenticateToken, async (req, res) => {
    try {
        // 4. Desestruture o novo campo
        const { nome, tipo_ativo, moeda_codigo } = req.body;
        const idAtivo = req.params.id;
        const idUsuario = req.user.userId;

        // 5. Adicione à validação
        if (!nome || !tipo_ativo || !moeda_codigo) {
            return res.status(400).json({ message: 'O nome, tipo e moeda do ativo são obrigatórios.' });
        }

        // 6. Adicione ao UPDATE
        const [result] = await pool.query(
            'UPDATE ativos SET nome = ?, tipo_ativo = ?, moeda_codigo = ? WHERE id_ativo = ? AND id_usuario = ? AND id_perfil = ?', 
            [nome, tipo_ativo, moeda_codigo, req.params.id, req.user.userId, req.user.perfilId]
        );

        if (result.affectedRows > 0) {
            res.status(200).json({ message: 'Ativo atualizado com sucesso.' });
        } else {
            res.status(404).json({ message: 'Ativo não encontrado ou não autorizado.' });
        }
    } catch (error) {
        console.error("Erro ao editar ativo:", error);
        res.status(500).json({ message: "Erro interno do servidor" });
    }
});

// Rota para EXCLUIR um ativo (e todas as suas operações, devido ao ON DELETE CASCADE)
app.delete('/api/ativos/:id', authenticateToken, async (req, res) => {
    try {
        const idAtivo = req.params.id;
        const idUsuario = req.user.userId;

        const [result] = await pool.query(
            'DELETE FROM ativos WHERE id_ativo = ? AND id_usuario = ?',
            [idAtivo, idUsuario]
        );

        if (result.affectedRows > 0) {
            res.status(200).json({ message: 'Ativo excluído com sucesso.' });
        } else {
            res.status(404).json({ message: 'Ativo não encontrado ou não autorizado.' });
        }
    } catch (error) {
        console.error("Erro ao excluir ativo:", error);
        res.status(500).json({ message: "Erro interno do servidor" });
    }
});

// --- ROTAS PARA OPERAÇÕES DE INVESTIMENTOS ---


// Rota para ADICIONAR uma nova operação (compra/venda)
app.post('/api/operacoes', authenticateToken, async (req, res) => {
    try {
        // 1. Desestruture os novos campos
        const { id_ativo, tipo_operacao, data_operacao, quantidade, preco_unitario, custos, moeda_codigo, taxa_cambio_usada } = req.body;
        
        // 2. Adicione moeda_codigo à validação
        if (!id_ativo || !tipo_operacao || !data_operacao || !quantidade || !preco_unitario || !moeda_codigo) {
            return res.status(400).json({ message: 'Todos os campos, incluindo moeda, são obrigatórios.' });
        }

        // 3. Adicione os novos campos ao INSERT
        const [result] = await pool.query(
            'INSERT INTO operacoes_investimentos (id_ativo, tipo_operacao, data_operacao, quantidade, preco_unitario, custos, moeda_codigo, taxa_cambio_usada) VALUES (?, ?, ?, ?, ?, ?, ?, ?)',
            [id_ativo, tipo_operacao, data_operacao, quantidade, preco_unitario, custos || 0, moeda_codigo, taxa_cambio_usada || 1]
        );

        res.status(201).json({ message: 'Operação registrada com sucesso!', id_operacao: result.insertId });

    } catch (error) {
        console.error("Erro ao adicionar operação:", error);
        res.status(500).json({ message: "Erro interno do servidor" });
    }
});

// --- ROTA PARA PERFORMANCE DO PORTFOLIO 
app.get('/api/portfolio/performance', authenticateToken, async (req, res) => {
    try {
        const idUsuario = req.user.userId;

        // 1. Busca a composição atual da carteira (ativos e quantidades)
        const portfolioQuery = `
            SELECT
                a.id_ativo, a.ticker, a.tipo_ativo, a.moeda_codigo,
                SUM(CASE WHEN op.tipo_operacao = 'Compra' THEN op.quantidade ELSE -op.quantidade END) as quantidade_total,
                SUM(CASE WHEN op.tipo_operacao = 'Compra' THEN op.quantidade * op.preco_unitario + op.custos ELSE 0 END) as custo_total
            FROM ativos a
            LEFT JOIN operacoes_investimentos op ON a.id_ativo = op.id_ativo
            WHERE a.id_usuario = ?
            GROUP BY a.id_ativo
            HAVING quantidade_total > 0;
        `;
        const [portfolio] = await pool.query(portfolioQuery, [idUsuario]);

        if (portfolio.length === 0) {
            return res.json({ custoTotal: 0, valorMercadoAtual: 0, rentabilidadeValor: 0, rentabilidadePercentual: 0 });
        }

        const tickersAcoes = portfolio.filter(a => a.tipo_ativo !== 'Criptomoeda').map(a => a.ticker).join(',');
        const idsCripto = portfolio.filter(a => a.tipo_ativo === 'Criptomoeda').map(a => a.ticker.toLowerCase()).join(',');

        let precosAtuais = {};

        if (tickersAcoes) {
            const brapiToken = '16mx42gc5NSbeGNMjeCiPC';
            const responseBrapi = await axios.get(`https://brapi.dev/api/quote/${tickersAcoes}?token=${brapiToken}`);
            responseBrapi.data.results.forEach(result => {
                precosAtuais[result.symbol] = result.regularMarketPrice;
            });
        }

        if (idsCripto) {
            const responseCoingecko = await axios.get(`https://api.coingecko.com/api/v3/simple/price?ids=${idsCripto}&vs_currencies=brl,usd`);
            for (const id in responseCoingecko.data) {
                precosAtuais[id.toUpperCase()] = responseCoingecko.data[id].brl;
            }
        }
        
        let valorMercadoTotal = 0;
        let custoTotalConsolidado = 0;

        portfolio.forEach(ativo => {
            const preco = precosAtuais[ativo.ticker];
            if (preco) {
                valorMercadoTotal += ativo.quantidade_total * preco;
            }
            custoTotalConsolidado += ativo.custo_total;
        });

        const rentabilidadeValor = valorMercadoTotal - custoTotalConsolidado;
        const rentabilidadePercentual = (custoTotalConsolidado > 0) ? (rentabilidadeValor / custoTotalConsolidado) * 100 : 0;

        // Resposta de sucesso enviada AQUI
        res.json({
            custoTotal: custoTotalConsolidado,
            valorMercadoAtual: valorMercadoTotal,
            rentabilidadeValor: rentabilidadeValor,
            rentabilidadePercentual: rentabilidadePercentual
        });

    } catch (error) {
        console.error("Erro detalhado ao buscar performance do portfólio:");
        if (error.response) {
            console.error("API Externa Respondeu com Dados:", error.response.data);
            console.error("API Externa Respondeu com Status:", error.response.status);
        } else if (error.request) {
            console.error("Requisição feita, mas sem resposta:", error.request);
        } else {
            console.error('Erro na configuração da requisição:', error.message);
        }
        console.error("Mensagem de erro original:", error.message);
        
        // CORREÇÃO: A resposta de erro agora está DENTRO do bloco catch
        res.status(500).json({ message: "Erro interno do servidor ao buscar dados externos." });
    }
    
});

// --- ROTAS PARA DIVIDENDOS ---

// Rota para ADICIONAR um novo dividendo
app.post('/api/dividendos', authenticateToken, async (req, res) => {
    try {
        const { id_ativo, data_pagamento, valor_total } = req.body;
        const id_usuario = req.user.userId;

        if (!id_ativo || !data_pagamento || !valor_total) {
            return res.status(400).json({ message: 'Ativo, data e valor são obrigatórios.' });
        }
        if (valor_total <= 0) {
            return res.status(400).json({ message: 'O valor do dividendo deve ser maior que zero.' });
        }

        const [result] = await pool.query(
            'INSERT INTO dividendos (id_ativo, id_usuario, data_pagamento, valor_total) VALUES (?, ?, ?, ?)',
            [id_ativo, id_usuario, data_pagamento, valor_total]
        );

        res.status(201).json({ message: 'Dividendo registrado com sucesso!', id_dividendo: result.insertId });

    } catch (error) {
        console.error("Erro ao registrar dividendo:", error.message);
        res.status(500).json({ message: 'Erro interno do servidor.' });
    }
});


// --- ROTA PARA EVOLUÇÃO DO PATRIMÔNIO LÍQUIDO (VERSÃO CORRIGIDA) ---
app.get('/api/patrimonio/historico', authenticateToken, async (req, res) => {
    try {
        const idUsuario = req.user.userId;
        const idPerfil = req.user.perfilId; // Pega o perfil ativo
        const mesesAtras = 6;

        if (!idPerfil) {
            return res.status(400).json({ message: "Nenhum perfil ativo na sessão." });
        }

        const query = `
            WITH RECURSIVE meses (mes) AS (
                SELECT DATE_FORMAT(CURDATE(), '%Y-%m-01')
                UNION ALL
                SELECT mes - INTERVAL 1 MONTH
                FROM meses
                WHERE mes > CURDATE() - INTERVAL ? MONTH
            ),
            saldos_mensais AS (
                SELECT
                    DATE_FORMAT(l.data_lancamento, '%Y-%m-01') as mes_lancamento,
                    SUM(CASE WHEN l.tipo = 'Receita' THEN l.valor ELSE -l.valor END) as fluxo_liquido
                FROM lancamentos l
                WHERE l.id_usuario = ? AND l.id_perfil = ? AND l.data_lancamento < CURDATE() + INTERVAL 1 DAY
                GROUP BY mes_lancamento
            )
            SELECT
                DATE_FORMAT(m.mes, '%Y-%m') as mes,
                -- --- CORREÇÃO AQUI ---
                -- A subquery agora filtra por c.id_perfil (contas) e não l.id_perfil
                (SELECT COALESCE(SUM(c.saldo_inicial), 0) FROM contas c WHERE c.id_usuario = ? AND c.id_perfil = ?) +
                -- --------------------
                (SELECT COALESCE(SUM(s.fluxo_liquido), 0) FROM saldos_mensais s WHERE s.mes_lancamento <= m.mes) as patrimonio
            FROM meses m
            ORDER BY mes ASC;
        `;

        const [historico] = await pool.query(query, [mesesAtras, idUsuario, idPerfil, idUsuario, idPerfil]);

        // O ideal seria adicionar o valor dos investimentos aqui também, mas vamos começar
        // apenas com as contas para simplificar. Podemos adicionar isso depois.

        res.json(historico);

    } catch (error) {
        console.error("Erro ao buscar histórico de patrimônio:", error.message);
        res.status(500).json({ message: "Erro interno do servidor" });
    }
});


// --- ROTA PARA SIMULAR PLANO DE QUITAÇÃO DE DÍVIDAS ---
app.post('/api/dividas/simular-plano', authenticateToken, async (req, res) => {
    
    console.log("Backend recebeu para simulação:", req.body);
    const idUsuario = req.user.userId;
    const { valorExtraMensal, estrategia } = req.body;

    if (!estrategia || !valorExtraMensal || valorExtraMensal < 0) {
        return res.status(400).json({ message: 'Estratégia e valor extra mensal são obrigatórios.' });
    }

    try {
        // 1. Busca todas as dívidas ativas do usuário
        const [dividas] = await pool.query(
            "SELECT id_conta, nome, saldo_inicial as saldo_devedor, taxa_juros FROM contas WHERE id_usuario = ? AND tipo_conta IN ('Financiamento', 'Empréstimo', 'Cartão de Crédito') AND saldo_inicial > 0",
            [idUsuario]
        );

        if (dividas.length === 0) {
            return res.json({ cronograma: [], mesesTotais: 0, totalPago: 0, jurosEconomizados: 0 });
        }

        // 2. Ordena as dívidas de acordo com a estratégia escolhida
        if (estrategia === 'Avalanche') {
            // Maior taxa de juros primeiro
            dividas.sort((a, b) => b.taxa_juros - a.taxa_juros);
        } else if (estrategia === 'Bola de Neve') {
            // Menor saldo devedor primeiro
            dividas.sort((a, b) => a.saldo_devedor - b.saldo_devedor);
        }

        // 3. Inicia a simulação
        let cronograma = [];
        let meses = 0;
        let pagamentoExtraDisponivel = parseFloat(valorExtraMensal);
        let dividasAtivas = JSON.parse(JSON.stringify(dividas)); // Cópia profunda para simulação

        while (dividasAtivas.some(d => d.saldo_devedor > 0) && meses < 360) { // Limite de 30 anos
            meses++;
            let pagamentoEsteMes = { mes: meses, pagamentos: [] };
            
            // Foca todo o pagamento extra na primeira dívida da lista (a prioritária)
            dividasAtivas[0].saldo_devedor -= pagamentoExtraDisponivel;

            pagamentoEsteMes.pagamentos.push({
                nome: dividasAtivas[0].nome,
                valorPago: pagamentoExtraDisponivel,
                saldoRestante: Math.max(0, dividasAtivas[0].saldo_devedor)
            });

            // Se uma dívida foi quitada, o valor pago a ela se torna parte da "bola de neve"
            if (dividasAtivas[0].saldo_devedor <= 0) {
                const pagamentoRemanescente = Math.abs(dividasAtivas[0].saldo_devedor);
                // No mundo real, aqui entraria o pagamento mínimo da próxima dívida.
                // Para simplificar, vamos assumir que o "pagamento mínimo" é o juro.
                // Esta é uma simplificação para V1. O valor extra se aplica à próxima.
                dividasAtivas.shift(); // Remove a dívida quitada
                if (dividasAtivas.length > 0) {
                    dividasAtivas[0].saldo_devedor -= pagamentoRemanescente;
                }
            }

            // Recalcula juros para o próximo mês (simplificado)
            dividasAtivas.forEach(d => {
                const jurosMensal = (d.taxa_juros / 100) / 12;
                d.saldo_devedor *= (1 + jurosMensal);
            });
            
            cronograma.push(pagamentoEsteMes);
        }

        res.json({ cronograma: cronograma, mesesTotais: meses });

    } catch (error) {
        console.error("Erro ao simular plano de quitação:", error.message);
        res.status(500).json({ message: "Erro interno do servidor" });
    }
});


function parseTextoDoExtrato(texto) {
    const transacoes = [];
    // A limpeza inicial remove aspas e normaliza quebras de linha.
    const textoLimpo = texto.replace(/[“”"]/g, '');
    const linhas = textoLimpo.split('\n').filter(linha => linha.trim() !== '');

    const regexData = /(\d{2})\s+de\s+(\w+)\s+de\s+(\d{4})/;
    // Voltamos para a RegEx que busca por NÚMEROS, pois é mais flexível.
    const regexTransacao = /^(.*?)\s+(-?[\d,.]+)\s+(-?[\d,.]+)\s*$/;

    const meses = {
        'janeiro': '01', 'fevereiro': '02', 'marco': '03', 'abril': '04', 'maio': '05', 'junho': '06',
        'julho': '07', 'agosto': '08', 'setembro': '09', 'outubro': '10', 'novembro': '11', 'dezembro': '12'
    };

    let dataAtual = null;

    for (const linha of linhas) {
        if (/SAC:|Ouvidoria:|Fale com a gente|solicitado em:/i.test(linha)) {
            continue;
        }

        const matchData = linha.match(regexData);
        if (matchData) {
            const dia = matchData[1];
            const mesNome = matchData[2].toLowerCase();
            const ano = matchData[3];
            const mesNumero = meses[mesNome];
            if (mesNumero) {
                dataAtual = `${dia}/${mesNumero}/${ano}`;
            }
            continue;
        }

        if (!dataAtual) continue;
        
        // A estratégia robusta: removemos o "R$" ANTES de tentar o match.
        const linhaSemMoeda = linha.replace(/R\$\s?/g, '');
        const matchTransacao = linhaSemMoeda.match(regexTransacao);

        if (matchTransacao) {
            let descricao = matchTransacao[1].trim();
            // O valor agora é capturado sem o "R$"
            let valorStr = matchTransacao[2].trim();
            
            if (descricao && !descricao.toLowerCase().includes('saldo do dia')) {
                processarTransacao(descricao, valorStr, dataAtual, transacoes);
            }
        }
    }
    return transacoes;
}

function processarTransacao(descricao, valorStr, dataAtual, transacoes) {
    try {
        let tipo;
        const descricaoNormalizada = descricao.toLowerCase().replace(/\s+/g, ' ');

        if (descricaoNormalizada.includes('pix enviado') || descricaoNormalizada.includes('compra no debito')) {
            tipo = 'Despesa';
        } else if (descricaoNormalizada.includes('pix recebido') || descricaoNormalizada.includes('estorno')) {
            tipo = 'Receita';
        } else {
            // O valor que chega aqui (valorStr) já não tem "R$"
            tipo = valorStr.startsWith('-') ? 'Despesa' : 'Receita';
        }
        
        // A lógica de limpeza do valor agora é mais simples e correta
        const valorNumericoStr = valorStr.replace(/\./g, '').replace(',', '.');
        const valor = parseFloat(valorNumericoStr);

        if (isNaN(valor)) return;

        transacoes.push({
            dataStr: dataAtual,
            descricaoStr: descricao,
            categoriaStr: "",
            // Usamos toFixed(2) para garantir a formatação com duas casas decimais
            valorStr: Math.abs(valor).toFixed(2),
            tipoStr: tipo
        });
    } catch(e) {
        console.error("Erro ao processar transação montada:", descricao);
    }
}

// Crie esta função auxiliar para simular o ambiente de um navegador para a pdf.js
class NodeCanvasFactory {
  create(width, height) {
    const canvas = createCanvas(width, height);
    const context = canvas.getContext("2d");
    return {
      canvas,
      context,
    };
  }
  reset(canvasAndContext, width, height) {
    canvasAndContext.canvas.width = width;
    canvasAndContext.canvas.height = height;
  }
  destroy(canvasAndContext) {
    canvasAndContext.canvas.width = 0;
    canvasAndContext.canvas.height = 0;
    canvasAndContext.canvas = null;
    canvasAndContext.context = null;
  }
}

// A rota usa o middleware 'upload.single('extrato')' para processar um ficheiro
// que virá do frontend no campo 'extrato'.
app.post('/api/extratos/ocr', authenticateToken, upload.single('extrato'), async (req, res) => {
    try {
        console.log("Backend: Recebido ficheiro para processamento OCR.");
        if (!req.file) {
            return res.status(400).json({ message: 'Nenhum ficheiro PDF foi enviado.' });
        }

        const worker = await createWorker('por');
        let textoCompleto = '';

        // 1. Carrega o PDF a partir do buffer recebido
        const data = new Uint8Array(req.file.buffer);
        const pdfDoc = await pdfjsLib.getDocument(data).promise;

        // 2. Itera sobre cada página do PDF
        for (let i = 1; i <= pdfDoc.numPages; i++) {
            const page = await pdfDoc.getPage(i);
            const viewport = page.getViewport({ scale: 2.0 }); // Aumenta a escala para melhor qualidade do OCR
            const canvasFactory = new NodeCanvasFactory();
            const canvasAndContext = canvasFactory.create(viewport.width, viewport.height);
            
            const renderContext = {
                canvasContext: canvasAndContext.context,
                viewport: viewport,
                canvasFactory: canvasFactory,
            };

            // 3. "Desenha" a página do PDF em um canvas na memória
            await page.render(renderContext).promise;

            // 4. Converte o canvas para uma imagem PNG em buffer
            const imageBuffer = canvasAndContext.canvas.toBuffer();

            // 5. Envia a IMAGEM para o Tesseract ler
            console.log(`Processando OCR da página ${i}...`);
            const { data: { text } } = await worker.recognize(imageBuffer);
            textoCompleto += text + '\n'; // Adiciona o texto da página ao resultado final
        }

        await worker.terminate();
        console.log("Backend: Texto extraído de todas as páginas com sucesso.");

        // 6. Agora, com o texto completo, chame o seu parser que já criamos
        const transacoesEstruturadas = parseTextoDoExtrato(textoCompleto);
        console.log(`Backend: ${transacoesEstruturadas.length} transações encontradas no texto.`);
        
        res.json({ transacoes: transacoesEstruturadas });

    } catch (error) {
        console.error("Erro no processamento OCR:", error);
        // Garante que o worker seja encerrado mesmo em caso de erro
        if (worker) await worker.terminate().catch(e => console.error("Erro ao encerrar worker:", e));
        res.status(500).json({ message: "Erro interno do servidor ao processar o PDF." });
    }
});

// Inicia o servidor
app.listen(port, () => {
  console.log(`Servidor escutando em http://localhost:${port}`);
});
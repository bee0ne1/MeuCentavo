const express = require('express');
const mysql = require('mysql2/promise'); // Usamos a versão com "Promises" para um código mais limpo
const bcrypt = require('bcrypt');
const { body, validationResult } = require('express-validator');

const app = express();
const port = 3000;

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

const jwt = require('jsonwebtoken'); // Importa a nova biblioteca

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


// Rota para LOGAR um usuário existente
app.post(
    '/api/usuarios/login',
    // Validações básicas
    body('username').notEmpty().withMessage('O nome de usuário é obrigatório.'),
    body('password').notEmpty().withMessage('A senha é obrigatória.'),

    async (req, res) => {
        const errors = validationResult(req);
        if (!errors.isEmpty()) {
            return res.status(400).json({ errors: errors.array() });
        }

        try {
            const { username, password } = req.body;

            // 1. Encontra o usuário no banco de dados pelo nome
            const [users] = await pool.query('SELECT * FROM usuario WHERE user_usuario = ?', [username]);

            // Se não encontrou nenhum usuário com aquele nome, o login falha
            if (users.length === 0) {
                return res.status(401).json({ message: 'Credenciais inválidas.' }); // 401 Unauthorized
            }

            const user = users[0];

            // 2. Compara a senha fornecida com o hash salvo no banco
            // bcrypt.compare é a função segura para fazer isso
            const isPasswordCorrect = await bcrypt.compare(password, user.user_password);

            if (!isPasswordCorrect) {
                // Se as senhas (hashes) não baterem, o login falha
                return res.status(401).json({ message: 'Credenciais inválidas.' }); // 401 Unauthorized
            }

            // 3. Se a senha está correta, o LOGIN FOI UM SUCESSO!
            // Agora, criamos o "passe de acesso" (JWT Token)
            const payload = { userId: user.user_id, username: user.user_usuario };
            const secretKey = 'sua_chave_super_secreta_pode_ser_qualquer_coisa'; // Guarde isso em um lugar seguro!
            const token = jwt.sign(payload, secretKey, { expiresIn: '1h' }); // Token expira em 1 hora

            // 4. Envia o token de volta para o cliente
            res.json({
                message: 'Login bem-sucedido!',
                token: token,
                user: { // <-- Objeto que o C++ espera
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

//------ROTAS DE LANÇAMENTO---------

// Rota para BUSCAR TODOS os lançamentos do usuário logado
app.get('/api/lancamentos', authenticateToken, async (req, res) => {
    try {
        const usuarioId = req.user.userId;

         // Usamos LEFT JOIN para juntar as tabelas e pegar os nomes da conta e da categoria
        const [lancamentos] = await pool.query(
            `SELECT
                l.*,
                c.nome as nome_conta,
                cat.nome as nome_categoria
             FROM lancamentos l
             LEFT JOIN contas c ON l.id_conta = c.id_conta
             LEFT JOIN categorias cat ON l.id_categoria = cat.id_categoria
             WHERE l.id_usuario = ?
             ORDER BY l.data_lancamento DESC, l.id DESC`,
            [usuarioId]
        );

        res.json(lancamentos);

    } catch (error) {
        console.error("Erro ao buscar lançamentos:", error);
        res.status(500).json({ message: 'Erro interno do servidor.' });
    }
});


// Rota para ADICIONAR um novo lançamento (VERSÃO ATUALIZADA)
app.post('/api/lancamentos/adicionar', authenticateToken, async (req, res) => {
    try {
        console.log("Backend recebeu o corpo da requisição:", req.body);

        // Agora também extraímos id_conta e id_categoria
        const { descricao, valor, data_lancamento, tipo, id_conta, id_categoria } = req.body;
        const id_usuario = req.user.userId;

        // Validação para os novos campos
        if (!descricao || !valor || !data_lancamento || !tipo || !id_conta || !id_categoria) {
            return res.status(400).json({ message: 'Todos os campos, incluindo conta e categoria, são obrigatórios.' });
        }

        // Adicionamos os novos campos à consulta INSERT
        const [result] = await pool.query(
            'INSERT INTO lancamentos (descricao, valor, data_lancamento, tipo, id_usuario, id_conta, id_categoria) VALUES (?, ?, ?, ?, ?, ?, ?)',
            [descricao, valor, data_lancamento, tipo, id_usuario, id_conta, id_categoria]
        );

        res.status(201).json({ message: 'Lançamento adicionado com sucesso!', insertId: result.insertId });

    } catch (error) {
        console.error("Erro ao adicionar lançamento:", error);
        res.status(500).json({ message: 'Erro interno do servidor.' });
    }
});

// Rota para BUSCAR os lançamentos mais recentes de um usuário
app.get('/api/lancamentos/recentes', authenticateToken, async (req, res) => {
    try {
        const usuarioId = req.user.userId;
        // Pega o limite da query string, ou usa 5 como padrão.
        const limite = parseInt(req.query.limite) || 5;

        const [lancamentos] = await pool.query(
            'SELECT * FROM lancamentos WHERE id_usuario = ? ORDER BY data_lancamento DESC, id DESC LIMIT ?',
            [usuarioId, limite]
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

        // Query que soma os valores, agrupados por tipo, apenas para o mês e ano atuais.
        const [rows] = await pool.query(
            `SELECT tipo, SUM(valor) as total
             FROM lancamentos
             WHERE id_usuario = ? AND MONTH(data_lancamento) = MONTH(CURRENT_DATE()) AND YEAR(data_lancamento) = YEAR(CURRENT_DATE())
             GROUP BY tipo`,
            [usuarioId]
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

// Rota para EDITAR (Atualizar) um lançamento existente
app.put('/api/lancamentos/:id', authenticateToken, async (req, res) => {
    try {
        const idLancamento = req.params.id;
        const idUsuario = req.user.userId;
        const { descricao, valor, data_lancamento, tipo, id_conta, id_categoria } = req.body;

        // Validação
        if (!descricao || !valor || !data_lancamento || !tipo || !id_conta || !id_categoria) {
            return res.status(400).json({ message: 'Todos os campos são obrigatórios.' });
        }

        // A condição 'AND id_usuario = ?' é uma segurança para garantir que um utilizador
        // só pode editar os seus próprios lançamentos.
        const [result] = await pool.query(
            `UPDATE lancamentos SET descricao = ?, valor = ?, data_lancamento = ?, tipo = ?, id_conta = ?, id_categoria = ?
             WHERE id = ? AND id_usuario = ?`,
            [descricao, valor, data_lancamento, tipo, id_conta, id_categoria, idLancamento, idUsuario]
        );

        if (result.affectedRows > 0) {
            res.status(200).json({ message: 'Lançamento atualizado com sucesso.' });
        } else {
            res.status(404).json({ message: 'Lançamento não encontrado ou não autorizado.' });
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

        const [result] = await pool.query(
            'DELETE FROM lancamentos WHERE id = ? AND id_usuario = ?',
            [idLancamento, idUsuario]
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

// --- ROTAS PARA CONTAS E CATEGORIAS ---

// Rota para BUSCAR TODAS as categorias do usuário logado
app.get('/api/categorias', authenticateToken, async (req, res) => {
    try {
        const idUsuario = req.user.userId;
        const [categorias] = await pool.query('SELECT * FROM categorias WHERE id_usuario = ?', [idUsuario]);
        res.json(categorias);
    } catch (error) {
        console.error("Erro ao buscar categorias:", error);
        res.status(500).json({ message: "Erro interno do servidor" });
    }
});

// Rota para ADICIONAR uma nova categoria para o usuário logado
app.post('/api/categorias', authenticateToken, async (req, res) => {
    try {
        const { nome, tipo } = req.body; // 'tipo' será "Receita" ou "Despesa"
        const idUsuario = req.user.userId;

        // Validação
        if (!nome || !tipo) {
            return res.status(400).json({ message: 'O nome e o tipo da categoria são obrigatórios.' });
        }
        if (tipo !== 'Receita' && tipo !== 'Despesa') {
            return res.status(400).json({ message: 'O tipo da categoria deve ser "Receita" ou "Despesa".' });
        }

        // Insere a nova categoria no banco de dados
        const [result] = await pool.query(
            'INSERT INTO categorias (nome, tipo, id_usuario) VALUES (?, ?, ?)',
            [nome, tipo, idUsuario]
        );

        // Retorna a categoria recém-criada
        res.status(201).json({
            id_categoria: result.insertId,
            nome: nome,
            tipo: tipo,
            id_usuario: idUsuario
        });

    } catch (error) {
        console.error("Erro ao adicionar categoria:", error);
        res.status(500).json({ message: "Erro interno do servidor" });
    }
});

// Rota para EDITAR (Atualizar) uma categoria existente
app.put('/api/categorias/:id', authenticateToken, async (req, res) => {
    try {
        const { nome } = req.body;
        const idCategoria = req.params.id;
        const idUsuario = req.user.userId;

        if (!nome) {
            return res.status(400).json({ message: 'O novo nome é obrigatório.' });
        }

        const [result] = await pool.query(
            'UPDATE categorias SET nome = ? WHERE id_categoria = ? AND id_usuario = ?',
            [nome, idCategoria, idUsuario]
        );

        if (result.affectedRows > 0) {
            res.status(200).json({ message: 'Categoria atualizada com sucesso.' });
        } else {
            res.status(404).json({ message: 'Categoria não encontrada ou não autorizada.' });
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
        // Busca todas as contas que pertencem ao usuário, ordenadas por nome
        const [contas] = await pool.query(
            'SELECT * FROM contas WHERE id_usuario = ? ORDER BY nome ASC', 
            [idUsuario]
        );
        res.json(contas);
    } catch (error) {
        console.error("Erro ao buscar contas:", error);
        res.status(500).json({ message: "Erro interno do servidor ao buscar contas." });
    }
});

// Rota para ADICIONAR uma nova conta
app.post('/api/contas', authenticateToken, async (req, res) => {
    try {
        const { nome, tipo_conta, saldo_inicial } = req.body;
        const idUsuario = req.user.userId;

        // Validação
        if (!nome || !tipo_conta) {
            return res.status(400).json({ message: 'O nome e o tipo da conta são obrigatórios.' });
        }

        const [result] = await pool.query(
            'INSERT INTO contas (nome, tipo_conta, saldo_inicial, id_usuario) VALUES (?, ?, ?, ?)',
            [nome, tipo_conta, saldo_inicial || 0.00, idUsuario]
        );

        res.status(201).json({
            id_conta: result.insertId,
            nome,
            tipo_conta,
            saldo_inicial: saldo_inicial || 0.00,
            id_usuario: idUsuario
        });
    } catch (error) {
        console.error("Erro ao adicionar conta:", error);
        res.status(500).json({ message: "Erro interno do servidor ao adicionar conta." });
    }
});

// Rota para EDITAR (Atualizar) uma conta existente
app.put('/api/contas/:id', authenticateToken, async (req, res) => {
    try {
        const { nome, tipo_conta, saldo_inicial } = req.body;
        const idConta = req.params.id;
        const idUsuario = req.user.userId;

        if (!nome || !tipo_conta || saldo_inicial === undefined) {
            return res.status(400).json({ message: 'Todos os campos (nome, tipo, saldo) são obrigatórios.' });
        }

        // A condição 'AND id_usuario = ?' é uma camada de segurança CRÍTICA.
        // Ela garante que um utilizador só pode editar as suas próprias contas.
        const [result] = await pool.query(
            'UPDATE contas SET nome = ?, tipo_conta = ?, saldo_inicial = ? WHERE id_conta = ? AND id_usuario = ?',
            [nome, tipo_conta, saldo_inicial, idConta, idUsuario]
        );

        if (result.affectedRows > 0) {
            res.status(200).json({ message: 'Conta atualizada com sucesso.' });
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

// Inicia o servidor
app.listen(port, () => {
  console.log(`Servidor escutando em http://localhost:${port}`);
});
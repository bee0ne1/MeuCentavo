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
  queueLimit: 0
});

// --- Início das Rotas da API ---

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
            res.status(201).json({ message: 'Usuário registrado com sucesso!', userId: result.insertId }); // 201 Created

        } catch (error) {
            console.error("Erro no registro:", error);
            res.status(500).json({ message: 'Erro interno do servidor.' });
        }
    }
);

const jwt = require('jsonwebtoken'); // Importa a nova biblioteca


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
            res.json({ message: 'Login bem-sucedido!', token: token });

        } catch (error) {
            console.error("Erro no login:", error);
            res.status(500).json({ message: 'Erro interno do servidor.' });
        }
    }
);

// Inicia o servidor
app.listen(port, () => {
  console.log(`Servidor escutando em http://localhost:${port}`);
});
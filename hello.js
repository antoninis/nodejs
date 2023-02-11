const express = require("express");
const app = express();

const users = require('bindings')('checkusers')
let usersList = users.getUsers().split(" ");

const path = require('path');
const host = 'localhost';
const port = 3000;
app.listen(port, host, () => {
    console.log(`Server is running on http://${host}:${port}`)
})

const bodyParser = require("body-parser");
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'start.html'));
})

app.post('/', (req, res) => {
    let username = req.body.username;
    if (req.body.username && usersList.includes(username))
        res.send(`<h2>Пользователь ${username} есть</h2><form action="/"><input type="submit" value="Назад"></form>`);
    else
        res.send(`<h2>Пользователя ${username} нет</h2><form action="/"><input type="submit" value="Назад"></form>`);
})
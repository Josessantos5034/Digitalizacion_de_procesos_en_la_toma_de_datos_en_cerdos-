const TelegramBot = require('node-telegram-bot-api');
const token = '1763212757:AAFCdM0oLLv2VUCkgwWGw6A2g5jJbNnJKy8';
const bot = new TelegramBot(token, {
  polling: true
});
var Idmichat = 923905754;
var SerialPort = require ('serialport');
var MiPuerto = new SerialPort('COM3', {
baudRate: 9600,
autoOpen : true
});
bot.on('message', (msg) => {
  const chatId = msg.chat.id;
  console.log("El ID del chat" + chatId);
  var Mensaje = msg.text;
  if (Mensaje == "encender"){
    console.log("encendiendo el led");
    bot.sendMessage(chatId, 'ON');
    MiPuerto.write("H");
    }
    else if (Mensaje == "apagar"){
      console.log("apagando el led");
      bot.sendMessage(chatId, 'OFF');
        MiPuerto.write("L");
    }
});

MiPuerto.setEncoding('utf8');
MiPuerto.on('data', function(data) {
  console.log("Lo que entro es" + data);
  if (data[0] == 'H'){
    console.log("Boton Precionado");
    bot.sendMessage(Idmichat,"Se preciono el boton");
  }
});

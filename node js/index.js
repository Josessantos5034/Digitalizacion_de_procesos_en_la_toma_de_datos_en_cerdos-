const TelegramBot = require('node-telegram-bot-api');
const token = '1763212757:AAFCdM0oLLv2VUCkgwWGw6A2g5jJbNnJKy8';
const bot = new TelegramBot(token, {
  polling: true
});
var Idmichat = 923905754;

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

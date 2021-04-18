const TelegramBot = require('node-telegram-bot-api');
var mqtt = require('mqtt');
const token = '1763212757:AAFCdM0oLLv2VUCkgwWGw6A2g5jJbNnJKy8';
const bot = new TelegramBot(token, {
  polling: true

});
var Idmichat = 923905754;

var client  = mqtt.connect('mqtt://cerdos-prueba:pEcontDiDMEvV6rT@cerdos-prueba.cloud.shiftr.io');

bot.on('message', (msg) => {
  const chatId = msg.chat.id;
  console.log("El ID del chat" + chatId);
  var Mensaje = msg.text.toString().toLocaleLowerCase();
  if (Mensaje.indexOf("encender") >=0){
    console.log("encendiendo el led");
    bot.sendMessage(chatId, 'ON');
    client.publish('temp','1');
    }
    else if(Mensaje.indexOf("apagar") >=0){
      console.log("apagando el led");
      bot.sendMessage(chatId, 'OFF');
      client.publish('temp','0');
    }
});

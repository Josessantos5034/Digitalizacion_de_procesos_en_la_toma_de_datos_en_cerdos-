const TelegramBot = require('node-telegram-bot-api');
//var mqtt = require('mqtt');/
var Constantes = require('./Token');
const bot = new TelegramBot(Constantes,token, {
  polling: true

});
var Idmichat = 923905754;
///ES EL URL DEL TOKEN, EL SOLO SE GENERA DEPUES DE CREAR EL TOKEN/

//var client  = mqtt.connect('mqtt://cerdos-prueba:pEcontDiDMEvV6rT@cerdos-prueba.cloud.shiftr.io');/
var SerialPort = require('serialport');
var MiPuerto = new SerialPort('COM4');
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

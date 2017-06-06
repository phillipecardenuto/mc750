var url = 'wss://io.adafruit.com:443/mqtt/';
var username = 'R0m3r0';
var aio_key  = 'b7b62e5209d84092b25e4ae48598ea29';

var caminho = "css/img/";
var imagesArray = ["tristeza1.png", "tristeza1.jpg", "tristeza2.png"];

var client = mqtt.connect(url, {
    username: username,
    password: aio_key
});

client.on('connect', function() {
    console.log("MQTT Conectado!");
    client.subscribe(username + "/feeds/vibration");
    client.subscribe(username + "/feeds/image");

});

client.on('error', function(e) {
    console.log(e);
});

function sendFeed(feed, valor) {
    client.publish(username + "/feeds/" + feed, valor);
    console.log("Enviado: " + username + "/feeds/" + feed + ": " + valor);
}
client.on('message', function(topic, message) {
    console.log("Recebido: " + topic.toString() + ": " + message.toString());
    if (topic.toString() == username + "/feeds/vibration") {
        var vibration = parseInt(message);
        var element = document.getElementById("monalisa");
        if (vibration == 1) {
            element.classList.add("ativo");
        } else {
            element.classList.remove("ativo");
        }
    }else if (topic.toString() == username + "/feeds/image") {
         var imagem = parseInt(message);
         var numimg = parseInt(Math.random() * (3 - 0) + 0);
         var numsound = parseInt(Math.random() * (3 - 0) + 0);

        var element = document.getElementById("img");
        var caminhoimg = "css/img/tristeza/";
        var caminhosound = "css/sounds/tristeza/sound";
        var audio = new Audio();
        if (imagem == 1) {
            element.src = caminhoimg +  imagesArray[numimg];
            audio.src = caminhosound+numsound+".mp3";
            audio.play();
        } else if(imagem==2){
            element.src = "css/img/12.gif";
        }else if(imagem==3){
            element.src = "css/img/felicidade.jpg";
        }else if(imagem==4){
            element.src = "css/img/amor.jpg";
        }else if(imagem==5){
            element.src = "css/img/raiva.jpg";
        }else if(imagem==6){
            element.src = "css/img/nojo.jpg";
        }
    }



});

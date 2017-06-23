var url = 'wss://io.adafruit.com:443/mqtt/';
var username = 'R0m3r0';
var aio_key  = 'b7b62e5209d84092b25e4ae48598ea29';
var audio = new Audio();
var caminho = "css/img/";
var ArrayImgTristeza = ["tristeza1.jpg", "tristeza2.gif", "tristeza3.jpg","tristeza4.gif", "tristeza5.jpg", "tristeza6.gif",
                        "tristeza7.jpg", "tristeza8.gif", "tristeza9.jpg","tristeza10.gif"];

var ArraySomTristeza = ["tristeza1.mp3", "tristeza2.mp3", "tristeza3.mp3", "tristeza4.mp3", "tristeza5.mp3"];

var ArrayImgAlegria = ["alegria1.jpg", "alegria2.gif", "alegria3.jpg","alegria4.gif", "alegria5.jpg", "alegria6.gif",
                        "alegria7.jpg", "alegria8.gif", "alegria9.jpg","alegria10.gif"];

var ArraySomAlegria = ["alegria1.mp3", "alegria2.mp3"];

var ArrayImgAmor = ["amor1.jpg", "amor2.gif", "amor3.jpg","amor4.gif", "amor5.jpg", "amor6.gif",
                        "amor7.jpg", "amor8.gif", "amor9.jpg","amor10.gif"];

var ArraySomAmor = ["amor1.mp3", "amor2.mp3"];

var ArrayImgDesgosto = ["desgosto1.jpg", "desgosto2.gif", "desgosto3.jpg","desgosto4.gif", "desgosto5.jpg", "desgosto6.gif",
                        "desgosto7.jpg", "desgosto8.gif", "desgosto9.jpg","desgosto10.gif"];

var ArraySomDesgosto = ["desgosto1.mp3", "desgosto2.mp3"];

var ArrayImgFelicia = ["felicia1.jpg", "felicia2.gif", "felicia3.jpg","felicia4.gif", "felicia5.jpg", "felicia6.gif",
                        "felicia7.jpg", "felicia8.gif", "felicia9.jpg","felicia10.gif"];

var ArraySomFelicia = ["felicia1.mp3", "felicia2.mp3"];

var ArrayImgRaiva = ["raiva1.jpg", "raiva2.gif", "raiva3.jpg","raiva4.gif", "raiva5.jpg", "raiva6.gif",
                        "raiva7.jpg", "raiva8.gif", "raiva9.jpg","raiva10.gif"];

var ArraySomRaiva = ["raiva1.mp3", "raiva2.mp3"];



                        
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

// Recebendo e processando sinal da ADAIO
client.on('message', function(topic, message) {
    console.log("Recebido: " + topic.toString() + ": " + message.toString());
    if (topic.toString() == username + "/feeds/vibration") {
        var vibration = parseInt(message);
        var element = document.getElementById("romero");
        
        if (vibration == 1) {
            element.classList.add("ativo");
        } else {
            element.classList.remove("ativo");
        }
    }else if (topic.toString() == username + "/feeds/image") {
        var imagem = parseInt(message);
        var numimg = parseInt(Math.random() * (9 - 0) + 0);
        var numsound = parseInt(Math.random() * (2 - 0) + 0);
        var element = document.getElementById("img");
        var sentimento;
        if (imagem == 1) {
            sentimento = "tristeza/";
            numsound = parseInt(Math.random() * (5 - 0) + 0);
            audio.pause();
            element.src = caminho + sentimento +  ArrayImgTristeza[numimg];
            audio.src = caminho + sentimento + ArraySomTristeza[numsound];
            audio.play();
        } else if(imagem==2){
            sentimento = "felicia/";
            audio.pause();
            element.src = caminho + sentimento +  ArrayImgFelicia[numimg];
            audio.src = caminho + sentimento + ArraySomFelicia[numsound];
            audio.play();
        }else if(imagem==3){
            sentimento = "alegria/";
            audio.pause();
            element.src = caminho + sentimento +  ArrayImgAlegria[numimg];
            audio.src = caminho + sentimento + ArraySomAlegria[numsound];
            audio.play();
        }else if(imagem==4){
            sentimento = "amor/";
            audio.pause();
            element.src = caminho + sentimento +  ArrayImgAmor[numimg];
            audio.src = caminho + sentimento + ArraySomAmor[numsound];
            audio.play();
        }else if(imagem==5){
            sentimento = "raiva/";
            audio.pause();
            element.src = caminho + sentimento +  ArrayImgRaiva[numimg];
            audio.src = caminho + sentimento + ArraySomRaiva[numsound];
            audio.play();
        }else if(imagem==6){
            sentimento = "desgosto/";
            audio.pause();
            element.src = caminho + sentimento +  ArrayImgDesgosto[numimg];
            audio.src = caminho + sentimento + ArraySomDesgosto[numsound];
            audio.play();
        }
    }
});

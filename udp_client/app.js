var dgram = require('dgram');
var Random = require('random-js');
// create a Mersenne Twister-19937 that is auto-seeded based on time and other random values
var engine = Random.engines.mt19937().autoSeed();
// create a distribution that will consistently produce integers within inclusive range [0, 99].
var distributionTime = Random.integer(0, 60);
var distribution = Random.integer(0,0xFFFFFFFF);

function sendPacket(){
	var value=distribution(engine);
	console.log('sending value=',value);
	var message = new Buffer(4);
	message.writeUInt32LE(value,0);
	var client = dgram.createSocket("udp4");
	client.send(message, 0, message.length, 1153, "127.0.0.1", function(err) {
	  client.close();
	});
}

function main(){
	var time=distributionTime(engine);
	console.log('will call in ',time,' sec.');
	setTimeout(function(){
		sendPacket();
		main();
	},time*1000);
}

main();


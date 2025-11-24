const NodeExpress = require("express");
const NodeSocket = require("socket.io");
const NodeWebsocket = require("websocket");
const NodeNet = require("net");

const NodeApp = NodeExpress();

var sockets = [];

const server = NodeNet.createServer((socket) => {
	console.log("client connected");

	sockets.push(socket);

	socket.on("data", (data) => {
		console.log("recv data: ", data);

		socket.write(data);
	});

	socket.on("end", () => {
		console.log("end");

		var idx, temp = [];
		for(idx = 0; idx < sockets.length; idx++) {
			if(sockets[idx] === socket) {
				sockets = [...temp];
			}
			else {
				temp.push(sockets[idx]);
			}
		}
	});
});

console.log("===============1");

const port = 8080;
server.listen(port, () => {
	console.log("listen port: ", port);
});

const server2 = NodeNet.createServer((socket) => {
	console.log("client2 connected");

	sockets.push(socket);

	socket.on("data", (data) => {
		console.log("recv data2: ", data);

		sockets.forEach((sock, idx) => {
			sock.write(data);
		});
	});

	socket.on("end", () => {
		console.log("end2");

		var idx, temp = [];
		for(idx = 0; idx < sockets.length; idx++) {
			if(sockets[idx] === socket) {
				sockets = [...temp];
			}
			else {
				temp.push(sockets[idx]);
			}
		}
	});
});

console.log("===============2");

const port2 = 8081;
server2.listen(port2, () => {
	console.log("listen port2: ", port2);
});


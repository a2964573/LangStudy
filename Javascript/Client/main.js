const NodeNet = require("net");
const NodeIo = require("socket.io");
const NodeWs = require("websocket");

const option = {
	host: "localhost",
	port: "8080"
};

const client = NodeNet.connect(option, function() {
    this.on("data", (data) => {
      console.log("From Server: " + data.toString());
      this.end();
    });

    this.on("end", () => {
      console.log('Client disconnected');
    });

    this.on("error", (err) => {
      console.log('Socket Error: ', JSON.stringify(err));
    });

    this.on("timeout", () => {
      console.log('Socket Timed Out');
    });

    this.on("close", () => {
      console.log('Socket Closed');
    });

  return client;
});


const server = NodeNet.createServer((socket) => {
    console.log("client connected");

    socket.on("data", (data) => {
        console.log("recv data: ", data);

        socket.write(data);
    });

    socket.on("end", () => {
        console.log("end");
    });
});

console.log("===============1");

const port = 8082;
server.listen(port, () => {
    console.log("listen port: ", port);
});


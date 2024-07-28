const Http = require('http');
const Fs = require('fs');
const WEB_PORT = 80;

const getFilePath = (path) => {
    switch(path) {
        case "/":
            return "../Client/index.html";
        case "/login":
            return "../Client/Pages/Login.html";
        case "/content":
            return "../Client/Pages/Content.html";
        case "/favicon.ico":
            return null;
    }
};

const WebServer = Http.createServer((req, res) => {
    res.writeHead(200, { "Content-Type": "text/html" });

    const PATH = req.url;
    console.log(`[DBG] createServer PATH : [${PATH}]`);

    const filePath = getFilePath(PATH);
    console.log(`[DBG] createServer filePath[${filePath}]`);

    if(!filePath) {
        console.log(`[ERR] createServer Not Found File Path`);
        res.writeHead(404);
        res.end("File Not Found");
        return;
    }


    Fs.readFile(filePath, (err, data) => {
        if (err) {
            res.writeHead(404);
            res.end(JSON.stringify(err));
            return;
        }

        res.end(data);
    });
});

WebServer.listen(WEB_PORT, (req, res) => {
    console.log(`===================================`);
    console.log("Web server listening on port " + WEB_PORT);
    console.log(`===================================`);
});

// ↑ Web Server
///////////////////////////////////////////////////////////////////////////////////
// ↓ Node Server

const NodeExpress = require('express');
const NodeBodyParser = require('body-parser');
const NodeApp = NodeExpress();
const NODE_PORT = 3000;

NodeApp.use(NodeBodyParser.json());
NodeApp.use(NodeBodyParser.urlencoded({ extended: true }));

NodeApp.use("/", (req, res, next) => {
    console.log(`[DBG] NodeServer API call [${req.url}]`);
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Headers', 'Origin, X-Requested-With, Content-Type, Accept');
    next();
});

NodeApp.use("/api", require('./service/routes'));

NodeApp.listen(NODE_PORT, (req, res) => {
    console.log(`===================================`);
    console.log("Node server listening on port " + NODE_PORT);
    console.log(`===================================`);
});

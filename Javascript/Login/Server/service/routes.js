const NodeExpress = require('express');
const router = NodeExpress.Router();

router.post('/login', (req, res) => {
    console.log(`[DBG] NodeServer router call[Login] [${req.url}]`);

    if(req.body.id == "test" && req.body.pw == "test1234") {
        console.log(`[DBG] Login SUCCESS!!`);
        res.send("Y");
    } else {
        console.log(`[DBG] Login FAIL`);
        res.send("N");
    }
});


module.exports = router;
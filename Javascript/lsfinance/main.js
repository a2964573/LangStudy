const NodeNet = require("net");
const NodeIO = require("socket.io");
const NodeAxios = require("axios");

const Config = require("./environment/config");

async function main() {
	const headers = {
//		"content-type": "application/x-www-form-urlencoded"
		"content-type": "application/json; charset=utf-8",
		"authorization": "Bearer " + Config.access_tocken,
		"tr_cd": "CSPAT00601",
		"tr_cont": "N",
		"tr_cont_key": "",
		"mac_address": "",
	};

	const params = {
//		"grant_type": "client_credentials",
//		"appkey": Config.app_key,
//		"appsecretkey": Config.app_secret,
//		"scope":"oob"
	};

	const baseURL = "https://openapi.ls-sec.co.kr:8080";
//	const url = "oauth2/token";
	const url = "/stock/order"
	const method = "POST";

	const body = {
		"CSPAT00601InBlock1": {
			"IsuNo": "A005930",
			"OrdQty": 1,
			"OrdPrc": 96800,
			"BnsTpCode": "2",
			"OrdprcPtnCode": "00",
			"MgntrnCode": "000",
			"LoanDt": "",
			"OrdCndiTpCode": "0",
			"MbrNo": "KRX",
		}
	};

	try {
		const response = await NodeAxios.post(url, body, { headers, baseURL, params, method });
		console.log("sended success.");
		console.log(response.data);
	}
	catch(error) {
		if(error.code === "ECONNABORTED") {
			console.error("timeout: ", error.message);
		}
		else {
			console.error("error: ", error.response ? error.response.data : error.message);
		}
	}
}

main();


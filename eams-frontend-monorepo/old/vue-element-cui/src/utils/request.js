import dataJs from "@/data/data.js";
/**
 * 发起http请求，请自行实现
 */
export default function ({ url, method, params }) {
	console.log("模拟请求参数", { url, method, params });
	return new Promise(function (resolve, reject) {
		//做一些异步请求
		console.log(dataJs[url]);
		setTimeout(function () {
			resolve(dataJs[url]);
		}, 1000);
	});
}

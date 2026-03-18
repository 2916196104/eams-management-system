import request from "@/utils/request";
import apis from "./apis";
export function queryEnumData() {
	return request({
		url: "/common/base/enumList",
		method: "get",
	});
}
export function loadRegionList(pid) {
	return request({
		url: apis.regionList,
		method: "get",
		params: { pid },
	});
}

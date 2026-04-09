import { useHttp, DataUpType, type RequestCallback } from "@/plugins/http";
import type { LoginDTO, Oauth2TokenDTO } from "./type";
import { useUserStore } from "@/stores/user";

// 定义一个功能模块基础url，方便替换
const currBaseUrl = "/login";

/**
 * 登录接口
 * @param data 登录数据
 * @param success 登录成功回调
 * @param fail 登录失败回调
 */
export const login = async (data: LoginDTO, success: RequestCallback, fail: RequestCallback) => {
	const us = useUserStore();
	const http = useHttp();
	try {
		// 发送登录请求
		const res = await http.post<Oauth2TokenDTO>(currBaseUrl + "/auth-login", data, {
			upType: DataUpType.json,
		});
		// 记录Token到本地
		if (res.data) {
			us.setToken(res.data);
			// 执行成功回调
			success(res);
			return;
		}
		// 执行失败回调
		fail(res);
	} catch (err) {
		// 执行失败回调
		fail(err);
	}
};

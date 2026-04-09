import { useHttp, type RequestCallback } from "@/plugins/http";
import type { LoginDTO, Oauth2TokenDTO } from "./type";
import { useUserStore } from "@/stores/user";

const currBaseUrl = "/login";

export const login = async (data: LoginDTO, success: RequestCallback, fail: RequestCallback) => {
	const us = useUserStore();
	const http = useHttp();
	try {
		const res = await http.post<Oauth2TokenDTO>(currBaseUrl + "/auth-login", data);
		if (res.data) {
			us.setToken(res.data);
			success(res);
			return;
		}
		fail(res);
	} catch (err) {
		fail(err);
	}
};

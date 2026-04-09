/*
 * @Author: weisheng
 * @Date: 2025-04-17 15:58:11
 * @LastEditTime: 2025-06-15 21:47:22
 * @LastEditors: weisheng
 * @Description: Alova response and error handlers
 * @FilePath: /wot-starter/src/api/core/handlers.ts
 */
import type { Method } from "alova";
import router from "@/router";

// Custom error class for API errors
export class ApiError extends Error {
	code: number;
	data?: any;

	constructor(message: string, code: number, data?: any) {
		super(message);
		this.name = "ApiError";
		this.code = code;
		this.data = data;
	}
}

// Define a type for the expected API response structure
interface ApiResponse {
	code: number;
	msg?: string;
	data?: any;
	success?: boolean;
	total?: number;
	more?: boolean;
}

// Handle successful responses
export async function handleAlovaResponse(
	response: UniApp.RequestSuccessCallbackResult | UniApp.UploadFileSuccessCallbackResult | UniApp.DownloadSuccessData,
) {
	// Extract status code and data from UniApp response
	const { statusCode, data } = response as UniApp.RequestSuccessCallbackResult;

	// 处理401/403错误（如果不是在handleAlovaResponse中处理的）
	if (statusCode === 401 || statusCode === 403) {
		// 如果是未授权错误，清除用户信息并跳转到登录页
		uni.showToast({ title: "登录已过期，请重新登录！", icon: "none", duration: 500 });
		const timer = setTimeout(() => {
			clearTimeout(timer);
			router.replaceAll({ name: "login" });
		}, 500);

		throw new ApiError("登录已过期，请重新登录！", statusCode, data);
	}

	// Handle HTTP error status codes
	if (statusCode >= 400) {
		uni.showToast({ title: `Request failed with status: ${statusCode}`, icon: "none" });
		throw new ApiError(`Request failed with status: ${statusCode}`, statusCode, data);
	}

	// The data is already parsed by UniApp adapter
	const json = data as ApiResponse;
	// Log response in development
	if (import.meta.env.MODE === "development") {
		console.log("[Alova Response]", json);
	}

	// Return data for successful responses
	return json;
}

// Handle request errors
export function handleAlovaError(error: any, method: Method) {
	// Log error in development
	if (import.meta.env.MODE === "development") {
		console.error("[Alova Error]", error, method);
	}

	// 处理401/403错误（如果不是在handleAlovaResponse中处理的）
	if (error instanceof ApiError && (error.code === 401 || error.code === 403)) {
		// 如果是未授权错误，清除用户信息并跳转到登录页
		uni.showToast({ title: "登录已过期，请重新登录！", icon: "none", duration: 500 });
		const timer = setTimeout(() => {
			clearTimeout(timer);
			router.replaceAll({ name: "login" });
		}, 500);
		throw new ApiError("登录已过期，请重新登录！", error.code, error.data);
	}

	// Handle different types of errors
	if (error.name === "NetworkError") {
		uni.showToast({ title: "网络错误，请检查您的网络连接", icon: "none" });
	} else if (error.name === "TimeoutError") {
		uni.showToast({ title: "请求超时，请重试", icon: "none" });
	} else if (error instanceof ApiError) {
		uni.showToast({ title: error.message || "请求失败", icon: "none" });
	} else {
		uni.showToast({ title: "发生意外错误", icon: "none" });
	}

	throw error;
}

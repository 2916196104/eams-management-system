import AdapterUniapp from "@alova/adapter-uniapp";
import { createAlova } from "alova";
import vueHook from "alova/vue";
// import mockAdapter from '../mock/mockAdapter'
import { handleAlovaError, handleAlovaResponse } from "./handlers";

export const alovaInstance = createAlova({
	baseURL: import.meta.env.VITE_API_BASE_URL || "https://petstore3.swagger.io/api/v3",
	...AdapterUniapp({
		// mockRequest: mockAdapter,
	}),
	statesHook: vueHook,
	beforeRequest: (method) => {
		// Add content type for POST/PUT/PATCH requests
		if (["POST", "PUT", "PATCH"].includes(method.type)) {
			method.config.headers["Content-Type"] = "application/json";
		}



		// Add token to request headers
		const token = uni.getStorageSync('token');
		const tokenHead = uni.getStorageSync('tokenHead');
		if (token && tokenHead) {
			method.config.headers["Authorization"] = `${tokenHead} ${token}`;
		}

		// Log request in development
		if (import.meta.env.MODE === "development") {
			console.log(`[Alova Request] ${method.type} ${method.url}`, method.data || method.config.params);
			console.log(`[API Base URL] ${import.meta.env.VITE_API_BASE_URL}`);
			console.log(`[Environment] ${import.meta.env.VITE_ENV_NAME}`);
		}
	},

	// Response handlers
	responded: {
		// Success handler
		onSuccess: handleAlovaResponse,

		// Error handler
		onError: handleAlovaError,

		// Complete handler - runs after success or error
		onComplete: async () => {
			// Any cleanup or logging can be done here
		},
	},

	// We'll use the middleware in the hooks
	// middleware is not directly supported in createAlova options

	// Default request timeout (10 seconds)
	timeout: 60000,
	// 设置为null即可全局关闭全部请求缓存
	cacheFor: null,
});

export default alovaInstance;

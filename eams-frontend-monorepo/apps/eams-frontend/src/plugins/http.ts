import { type App, getCurrentInstance, inject } from "vue";
import type { AxiosError } from "axios";
import { stringify } from "qs";
import HttpClient, { closeLoading, DataUpType, showLoading } from "@/apis/http";
import type { Router } from "vue-router";
import { useUserStore } from "@/stores/user";
import { ElMessage } from "element-plus";

/** 插件标识符 */
const PLUGIN_SYMBOL = Symbol("http");

/** 全局HTTP实例 */
let globalHttp: HttpClient | null = null;

/** 数据状态码 */
const dataCode = {
	/** 暂未登录或TOKEN已经过期 */
	UNAUTHORIZED: 401,
	/** 没有相关权限 */
	FORBIDDEN: 403,
	/** 访问页面未找到 */
	NOT_FOUND: 404,
	/** 服务器错误 */
	SERVER_ERROR: 9994,
	/** 上传参数异常 */
	PARAMS_INVALID: 9995,
	/** ContentType错误 */
	CONTENT_TYPE_ERR: 9996,
	/** 功能尚未实现 */
	API_UN_IMPL: 9997,
	/** 服务器繁忙 */
	SERVER_BUSY: 9998,
	/** 操作失败 */
	FAIL: 9999,
	/** 操作成功 */
	SUCCESS: 10000,
};

/** 插件配置项 */
interface HttpPluginOptions {
	/** 路由对象 */
	router: Router;
}

/**
 * 组合式函数
 * @returns 插件实例
 */
export function useHttp(): HttpClient {
	// 尝试获取当前组件实例
	const instance = getCurrentInstance();
	if (instance) {
		// 在组件上下文中，使用注入
		const plugin = inject(PLUGIN_SYMBOL) as HttpClient;
		if (plugin) return plugin;
	}

	// 不在组件上下文中，使用全局实例
	if (globalHttp) {
		return globalHttp;
	}

	// 没有获取到插件实例，抛出异常
	throw new Error("Http plugin is not installed. Please use app.use(http) first.");
}

/** 默认导出对象 */
export default {
	/**
	 * 插件安装函数
	 * @param app 应用实例
	 * @param options 参数选项
	 */
	install: (app: App, options: HttpPluginOptions) => {
		const store = useUserStore();
		const router = options.router;
		// 创建插件实例
		const http = new HttpClient(
			{},
			{
				requestInterceptor: (config) => {
					// 提交的时候携带登录凭证
					const token = store.getToken;
					if (token) {
						config.headers["Authorization"] = "Bearer " + token;
					}
					// 处理提交方式参数序列化操作
					const ut = config.upType;
					if (ut === DataUpType.json) {
						config.headers["Content-Type"] = "application/json;charset=UTF-8";
					} else if (ut === DataUpType.file) {
						config.headers["Content-Type"] = "multipart/form-data";
					} else if (ut === DataUpType.stream) {
						config.headers["Content-Type"] = "application/octet-stream";
					} else {
						config.headers["Content-Type"] = "application/x-www-form-urlencoded;charset=UTF-8";
						if (config.data) {
							config.data = stringify(config.data, { arrayFormat: "repeat" });
						}
					}
					//显示网络加载提示
					if (config.showLoading) {
						showLoading();
					}
					return config;
				},
				requestErrorInterceptor: (error) => {
					return Promise.reject(error);
				},
				responseInterceptor: async (response) => {
					// 关闭网络加载提示
					closeLoading();
					// 根据状态码处理数据
					if ("code" in response.data) {
						const data = response.data;
						switch (data.code) {
							case dataCode.SUCCESS:
								return Promise.resolve(response);
							case dataCode.FORBIDDEN:
								ElMessage.error("权限不够，请联系管理员");
								return Promise.resolve(response);
							case dataCode.UNAUTHORIZED:
								//判断是否是超时
								if (typeof data.data === "string" && data.data.indexOf("Jwt expired at") >= 0) {
									//刷新凭证
									await store.reloadToken();
									//设置为未加载
									store.setLoaded(false);
									//跳转到主页
									router.push("/home");
								} else {
									//没有登录或登录已失效
									router.push("/");
									//重置数据
									store.resetSaveData();
								}
								return Promise.resolve(response);
							case dataCode.NOT_FOUND:
								ElMessage.warning(data.message || "404访问页面不存在");
								return Promise.resolve(response);
							case dataCode.CONTENT_TYPE_ERR:
							case dataCode.PARAMS_INVALID:
								ElMessage.warning(data.message || "请求参数或请求头错误");
								return Promise.resolve(response);
							default:
								return Promise.reject(response);
						}
					}
					// 没有code存在的情况有可能是文件响应数据
					return Promise.resolve(response);
				},
				responseErrorInterceptor(error) {
					// 关闭网络加载提示
					closeLoading();
					console.error(error);
					// 网络错误处理
					if (!(error as AxiosError).response) {
						if ((error as any).code === "ECONNABORTED" || (error as AxiosError).message?.includes("timeout")) {
							return Promise.reject(new Error("请求超时，请稍后重试"));
						}
						return Promise.reject(new Error("网络错误，请检查网络连接"));
					}

					// HTTP状态码错误处理
					const status = (error as AxiosError).response?.status;
					const commonErrors: Record<number, string> = {
						400: "请求参数错误",
						401: "未授权，请重新登录",
						403: "权限不足",
						404: "请求的资源不存在",
						408: "请求超时",
						500: "服务器内部错误",
						502: "网关错误",
						503: "服务暂不可用",
						504: "网关超时",
					};
					const message = commonErrors[status as number] || `请求失败（状态码：${status}）`;
					return Promise.reject(new Error(message));
				},
			},
		);
		// 将插件实例提供给应用
		app.provide(PLUGIN_SYMBOL, http);
		// 保存到全局变量
		globalHttp = http;
		console.log("Http plugin installed.");
	},
};

/**
 * 导出api/http封装的方法和属性方便统一使用
 */
export { HttpClient, closeLoading, DataUpType, showLoading };
export type { RequestCallback } from "@/apis/http";

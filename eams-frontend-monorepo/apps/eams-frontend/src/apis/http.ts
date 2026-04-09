import Axios, {
	type AxiosInstance,
	type AxiosRequestConfig,
	type CustomParamsSerializer,
	type AxiosResponse,
	type InternalAxiosRequestConfig,
	type Method,
	type AxiosError,
} from "axios";
import { stringify } from "qs";
import { ElLoading } from "element-plus";

/** 扩展Axios配置类型，添加自定义属性 */
export interface CustomAxiosRequestConfig extends AxiosRequestConfig {
	/** 上传数据类型 */
	upType?: number;
	/** 是否显示加载提示 */
	showLoading?: boolean;
}

/** 默认基础配置 */
const defaultConfig: AxiosRequestConfig = {
	/** 接口基础地址 */
	baseURL: import.meta.env.VITE_API_URL,
	/** 请求超时时间 */
	timeout: import.meta.env.VITE_API_TIMEOUT,
	/** params参数使用qs序列化 */
	paramsSerializer: {
		serialize: stringify as CustomParamsSerializer,
	},
};

/** 拦截器配置 */
interface InterceptorsConfig {
	/** 请求拦截器 */
	requestInterceptor?: (
		config: InternalAxiosRequestConfig & CustomAxiosRequestConfig,
	) => InternalAxiosRequestConfig & CustomAxiosRequestConfig;
	/** 请求错误拦截器 */
	requestErrorInterceptor?: (error: AxiosError) => Promise<any>;
	/** 响应拦截器 */
	responseInterceptor?: (response: AxiosResponse<JsonVO<any>>) => any;
	/** 响应错误拦截器 */
	responseErrorInterceptor?: (error: AxiosError) => Promise<any>;
}

/** 后端响应数据类型定义 */
export interface JsonVO<T> {
	/** 状态码 */
	code: number;
	/** 提示信息 */
	message: string;
	/** 数据对象 */
	data?: T;
}

/**
 * 二次封装Axios，简化Axios使用，支持泛型，支持多实例使用模式等
 */
export default class HttpClient {
	/** axios实例对象 */
	private instance: AxiosInstance;

	/**
	 * 构造初始化配置
	 * @param customConfig 自定义Axios配置
	 * @param interceptors 自定义拦截器配置
	 */
	constructor(customConfig?: AxiosRequestConfig, interceptors?: InterceptorsConfig) {
		this.instance = Axios.create({ ...defaultConfig, ...customConfig });
		this.initInterceptors(interceptors);
	}

	/** 初始化拦截器 */
	private initInterceptors(interceptors?: InterceptorsConfig) {
		// 请求拦截器
		this.instance.interceptors.request.use(interceptors?.requestInterceptor, interceptors?.requestErrorInterceptor);
		// 响应拦截器
		this.instance.interceptors.response.use(interceptors?.responseInterceptor, interceptors?.responseErrorInterceptor);
	}

	/** 获取Axios实例 */
	public getInstance(): AxiosInstance {
		return this.instance;
	}

	/**
	 * 通用请求方法
	 * @param method 请求方式
	 * @param url 请求地址
	 * @param config 请求配置
	 * @returns 响应数据,如果要同步接收数据，需要搭配await使用，否则会返回Promise对象
	 */
	public async request<T = any>(method: Method, url: string, config?: CustomAxiosRequestConfig): Promise<JsonVO<T>> {
		try {
			const response = await this.instance.request<JsonVO<T>>({ ...config, method, url });
			return Promise.resolve(response.data);
		} catch (error) {
			console.warn("request ex:", error);
			return Promise.reject(error);
		}
	}

	/**
	 * GET请求
	 * @param url 请求地址
	 * @param params 请求参数
	 * @param config 请求配置
	 * @returns 响应数据
	 */
	public get<T = any>(url: string, params?: any, config?: CustomAxiosRequestConfig): Promise<JsonVO<T>> {
		return this.request<T>("get", url, { upType: DataUpType.form, ...config, params });
	}

	/**
	 * GET请求，如果请求结果是文件需要使用此方法
	 * @param url 请求地址
	 * @param params 请求参数
	 * @param config 请求配置
	 * @returns 请求发送后的Promise对象
	 */
	public getFile(url: string, params?: any, config?: CustomAxiosRequestConfig): Promise<any> {
		return this.instance.request({ ...config, method: "get", url, params });
	}

	/**
	 * POST请求,数据提交格式为JSON，如果要使用表单方式上传数据需要指定配置upType:DataUpType.form
	 * @param url 请求地址
	 * @param data 请求数据
	 * @param config 请求配置
	 * @returns 响应数据
	 */
	public post<T = any>(url: string, data?: any, config?: CustomAxiosRequestConfig): Promise<JsonVO<T>> {
		return this.request<T>("post", url, { upType: DataUpType.json, ...config, data });
	}

	/**
	 * PUT请求,数据提交格式为JSON，如果要使用表单方式上传数据需要指定配置upType:DataUpType.form
	 * @param url 请求地址
	 * @param data 请求数据
	 * @param config 请求配置
	 * @returns 响应数据
	 */
	public put<T = any>(url: string, data?: any, config?: CustomAxiosRequestConfig): Promise<JsonVO<T>> {
		return this.request<T>("put", url, { upType: DataUpType.json, ...config, data });
	}

	/**
	 * DELETE请求,数据提交格式为JSON，如果要使用表单方式上传数据需要指定配置upType:DataUpType.form
	 * @param url 请求地址
	 * @param data 请求数据
	 * @param config 请求配置
	 * @returns 响应数据
	 */
	public delete<T = any>(url: string, data?: any, config?: CustomAxiosRequestConfig): Promise<JsonVO<T>> {
		return this.request<T>("delete", url, { upType: DataUpType.json, ...config, data });
	}

	/**
	 * 发送带文件上传的请求，该方法会完成js数据对象转换成FormData对象操作
	 * 请求方式以post方式发送
	 * @param url 请求地址
	 * @param data 包括file数据的js数据对象
	 * @param config 请求配置
	 * @returns 响应数据
	 */
	public postWithFile<T = any>(url: string, data: any, config?: CustomAxiosRequestConfig): Promise<JsonVO<T>> {
		// 将data转换成FormData对象
		const formData = new FormData();
		for (const key in data) {
			formData.append(key, data[key]);
		}
		// 发送请求
		return this.request<T>("post", url, { ...config, data: formData, upType: DataUpType.file });
	}

	/**
	 * 以二进制的方式上传文件
	 * @param url 上传地址
	 * @param file 文件域选择的文件对象
	 * @param success 上传成功回调
	 * @param fail 上传失败回调
	 * @param config 请求配置
	 */
	public postFileStream<T = any>(
		url: string,
		file: any,
		success: RequestCallback,
		fail: RequestCallback,
		config?: CustomAxiosRequestConfig,
	) {
		// 读取文件
		const reader = new FileReader();
		reader.readAsArrayBuffer(file);
		reader.onloadend = () => {
			// 读取文件失败
			if (reader.error) {
				fail("文件读取失败");
				return;
			}
			// 上传文件
			this.request<T>("post", url, {
				...config,
				data: reader.result,
				upType: DataUpType.stream,
			})
				.then((res) => {
					success(res);
				})
				.catch((err) => {
					fail(err);
				});
		};
	}
}

/** 数据上传数据类型 */
export const DataUpType = {
	/** 表单类型 */
	form: 0,
	/** json类型 */
	json: 1,
	/** 文件类型 */
	file: 2,
	/** 文件流类型 */
	stream: 3,
};

/** 请求回调函数 */
export type RequestCallback = (res: any) => void;

/** 记录加载提示打开次数 */
let openLoadingCount = 0;
/** 网络加载框实例 */
let loading: any;

/** 显示网络加载效果 */
export function showLoading() {
	// 创建loading框
	if (!loading) {
		const svg = `
        <path class="path" d="
          M 30 15
          L 28 17
          M 25.61 25.61
          A 15 15, 0, 0, 1, 15 30
          A 15 15, 0, 1, 1, 27.99 7.5
          L 15 15
        " style="stroke-width: 4px; fill: rgba(0, 0, 0, 0)"/>`;
		loading = ElLoading.service({
			lock: true,
			text: "网络连接中",
			background: "rgba(255, 255, 255, 0.5)",
			svg: svg,
			svgViewBox: "-10, -10, 50, 50",
			beforeClose: function () {
				openLoadingCount--;
				if (openLoadingCount > 0) return false;
				return true;
			},
			closed: function () {
				openLoadingCount = 0;
				loading = null;
			},
		});
	}
	// 打开次数+1
	openLoadingCount++;
}

/** 关闭网络加载效果 */
export function closeLoading() {
	if (loading) {
		loading.close();
	}
}

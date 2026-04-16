/// <reference types="vite/client" />

// .env 环境变量声明
interface ImportMetaEnv {
	/** 应用标题 */
	readonly VITE_APP_TITLE: string;
	/** 后端接口请求超时毫秒数 */
	readonly VITE_API_TIMEOUT: number;
	/** 后端接口请求地址 */
	readonly VITE_API_BASE_URL: string;
	/** 环境名称 */
	readonly VITE_ENV_NAME: string;
}

import { defineStore } from "pinia";
import type { Dict } from "@/apis/common/type";
import { useHttp } from "@/plugins/http";

/**
 * 存放通用数据，如字典数据
 */
export const useCommonStore = defineStore("common", {
	state: () => ({
		/** 字典数据 */
		dicts: {} as Record<string, Dict>,
	}),
	getters: {
		/** 通过类型编码获取字典数据 */
		getDicts: (state) => {
			return (code: string) => state.dicts[code];
		},
	},
	actions: {
		/**
		 * 加载指定编码字典数据
		 * @param code 字典编码
		 * @param force 是否强制刷新
		 */
		async loadDict(code: string, force: boolean = false) {
			// 已经加载过数据就不在加载
			if (this.dicts[code] && !force) {
				return;
			}
			// 访问网络获取字典数据
			const data = await useHttp().get<Dict>("/dict", { code });
			// 数据存储到状态中
			if (data.data) this.dicts[code] = data.data;
		},
		/**
		 * 移除指定编码的字典
		 * @param code 字典编码
		 */
		remDict(code: string) {
			delete this.dicts[code];
		},
		/** 重置数据 */
		reset() {
			this.dicts = {};
		},
	},
});

/**
 * 执行替换逻辑
 * @param dict 语言包
 * @param template 替换模板
 * @param replacements 替换参数
 * @returns 最终替换结果
 */
function doReplace(dict: any, template: string, replacements: any) {
	// 参数空处理
	replacements = replacements || {};
	// 翻译
	template = dict[template] || template;
	// 替换
	return template.replace(/{([^}]+)}/g, function (_, key) {
		return replacements[key] || "{" + key + "}";
	});
}

// 根据自行需要，调整语言包中的内容
import zn from "./language/zn";
import ja from "./language/ja";

/**
 * 导出翻译模块
 */
export default {
	/** 中文翻译模块 */
	zn: {
		translate: [
			"value",
			function (template: string, replacements: any) {
				return doReplace(zn, template, replacements);
			},
		],
	},
	/** 日语翻译模块*/
	ja: {
		translate: [
			"value",
			function (template: string, replacements: any) {
				return doReplace(ja, template, replacements);
			},
		],
	},
};

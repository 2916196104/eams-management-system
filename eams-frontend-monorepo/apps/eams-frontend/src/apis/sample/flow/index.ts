import { useHttp, type RequestCallback } from "@/plugins/http";
import type { PageDTO } from "../../type";
import type {
	DeployProcessDefinitionDTO,
	ProcessDefinitionAddDTO,
	ProcessDefinitionModifyDTO,
	ProcessDefinitionQuery,
	ProcessDefinitionVO,
} from "./type";

// 用于示例流程定义常量定义
const flowReqOption = {
	baseURL: "http://127.0.0.1:8080",
	showLoading: true,
};
// 流程定义元数据接口地址
const flowMeataBaseUrl = "/camunda/process-definition";
// 流程引擎操作接口地址
const flowEngineBaseUrl = "/camunda";

/**
 * 分页查询流程定义数据
 * @param data 查询数据条件
 * @param success 成功回调
 * @param fail 失败回调
 */
export const listallFlow = async (data: ProcessDefinitionQuery, success: RequestCallback, fail: RequestCallback) => {
	try {
		const http = useHttp();
		// 发送请求
		const res = await http.get<PageDTO<ProcessDefinitionVO>>(flowMeataBaseUrl, data, flowReqOption);
		// 处理请求结果
		if (res.data) {
			// 执行成功回调
			success(res.data);
			return;
		}
		// 执行失败回调
		fail(res);
	} catch (err) {
		// 执行失败回调
		fail(err);
	}
};

/**
 * 获取流程定义详情
 * @param id 流程定义ID
 */
export const getFlowDefine = function (id: string) {
	const http = useHttp();
	return http.get<ProcessDefinitionVO>(flowMeataBaseUrl + "/" + id, {}, flowReqOption);
};

/**
 * 新增流程定义
 * @param data 新增流程定义数据
 */
export const addFlowDefine = function (data: ProcessDefinitionAddDTO) {
	const http = useHttp();
	return http.post<ProcessDefinitionVO>(flowMeataBaseUrl, data, flowReqOption);
};

/**
 * 修改流程定义
 * @param data 修改流程定义数据
 */
export const modifyFlowDefine = function (data: ProcessDefinitionModifyDTO) {
	const http = useHttp();
	return http.put<ProcessDefinitionVO>(flowMeataBaseUrl, data, flowReqOption);
};

/**
 * 删除流程定义
 * @param id 删除流程定义ID
 */
export const deleteFlowDefine = function (id: string) {
	const http = useHttp();
	return http.delete<ProcessDefinitionVO>(flowMeataBaseUrl + "/" + id, {}, flowReqOption);
};

/**
 * 发布流程定义
 * @param data 发布流程定义数据
 */
export const deployProcess = function (data: DeployProcessDefinitionDTO) {
	const http = useHttp();
	return http.post<ProcessDefinitionVO>(flowEngineBaseUrl + "/deploy", data, flowReqOption);
};

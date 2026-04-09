import type { PageQuery } from "../../type";

/**
 * 添加流程定义参数模型
 */
export interface ProcessDefinitionAddDTO extends Record<string, any> {
	/** 流程唯一标识(业务中使用的key) */
	processKey: string;
	/** 流程名称 */
	processName: string;
	/** 流程版本号 */
	processVersion: number;
	/** 流程状态 */
	processStatus: number;
	/** 流程描述 */
	description?: string;
	/** 删除状态 */
	deleted: number;
	/** BPMN XML内容 */
	xml?: string;
	/** BPMN XML对应MongoDB中的存储ID */
	xmlMongoId?: string;
}

/**
 * 修改流程定义参数模型
 */
export interface ProcessDefinitionModifyDTO extends ProcessDefinitionAddDTO {
	/** 唯一标识 */
	id: string;
}

/**
 * 流程定义查询参数模型
 */
export interface ProcessDefinitionQuery extends PageQuery {
	/** 流程定义名称 */
	processName?: string;
}

/**
 * 流程定义模型
 */
export interface ProcessDefinitionVO extends ProcessDefinitionModifyDTO {
	/** 创建者 */
	createBy?: string;
	/** 创建时间 */
	createTime?: string;
	/** 修改者 */
	updateBy?: string;
	/** 修改时间 */
	updateTime?: string;
}

/**
 * 部署流程定义参数模型
 */
export interface DeployProcessDefinitionDTO extends Record<string, any> {
	/** 流程唯一标识(业务中使用的key) */
	processKey: string;
	/** 流程版本号 */
	processVersion: number;
}

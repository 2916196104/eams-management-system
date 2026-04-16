#pragma once


#ifndef __GRADEMANAGE_H__
#define __GRADEMANAGE_H__
#include "domain/vo/BaseJsonVO.h"
#include "oatpp/web/server/api/ApiController.hpp"
#include "../../domain/vo/GradeTable/GradeManageVO.h"
#include "../../domain/query/GradeTable/GradeManageQuery.h"
#include "../../domain/dto/GradeTable/GradeManageDTO.h"
#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("Grade.tags.t1")
//成绩管理控制器

namespace web = oatpp::web;
class GradeManage : public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(GradeManage);
public:		//定义接口

	// 3.1 定义获取成绩列表接口描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("Grade.query-by-item.summary"), queryPageScore, GradeManageQuery, GradeManagePageJsonVO::Wrapper, API_TAG);
	// 3.2 定义获取成绩列表接口处理
	API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET, "c3-org/grademanage/get-grade-list", queryPageScore, QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(query, GradeManageQuery, queryParams);
	API_HANDLER_RESP_VO(execQueryPageScore(query)););

	// 3.1 定义保存成绩接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("Grade.save.summary"), saveScore, Uint64JsonVO::Wrapper, API_TAG);
	// 3.2 定义保存成绩接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "c3-org/grademanage/save-grade", saveScore, BODY_DTO(GradeManageDTO::Wrapper, dto), execSave(dto, authObject->getPayload()));

	// 3.1 定义删除成绩接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("Grade.delete.summary"), removeScore, ListJsonVO<String>::Wrapper, API_TAG);
	// 3.2 定义删除成绩接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_DEL, "c3-org/grademanage/del-grade", removeScore, BODY_DTO(List<String>, ids), execRemove(ids));

	// 3.1 定义导入成绩接口描述
	API_DEF_ENDPOINT_INFO_FILE_AUTH(ZH_WORDS_GETTER("Grade.import.summary"), importScore, GradeManageDTO::Wrapper, StringJsonVO::Wrapper, API_TAG);
	// 3.2 定义导入成绩接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "c3-org/grademanage/import-grade", importScore, REQUEST(std::shared_ptr<IncomingRequest>, request), execImportScore(request, authObject->getPayload()));

private:	//定义接口执行函数
	//3.3 定义获取成绩列表执行函数
	GradeManagePageJsonVO::Wrapper execQueryPageScore(const GradeManageQuery::Wrapper& query);
	//3.3 定义保存成绩执行函数
	Uint64JsonVO::Wrapper execSave(const GradeManageDTO::Wrapper& dto, const PayloadDTO& payload);
	//3.3 定义删除成绩执行函数
	ListJsonVO<String>::Wrapper execRemove(const List<String>& ids);
	//3.3 定义导入成绩执行函数
	StringJsonVO::Wrapper execImportScore(const std::shared_ptr<IncomingRequest>& request, const PayloadDTO& payload);
};

#include OATPP_CODEGEN_END(ApiController)
#undef API_TAG
#endif
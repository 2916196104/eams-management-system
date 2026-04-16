#pragma once

#ifndef __RECORD_COMMENT_H__
#define __RECORD_COMMENT_H__

#include "oatpp/web/server/api/ApiController.hpp"
#include "domain/GlobalInclude.h"

#include "domain/query/timetable/TimetableQuery.h"
#include "domain/vo/timetable/TimetableVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("evaluate.flag")

class Record_comment : public oatpp::web::server::api::ApiController
{

	API_ACCESS_DECLARE(Record_comment);
public:		//定义接口

	// 2. 定义 获取课次点评列表（条件+分页）
	ENDPOINT_INFO(queryEvaluation) {

		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("evaluate.title1"));
		
		API_DEF_ADD_AUTH();

		API_DEF_ADD_RSP_JSON_WRAPPER(EvaluatePageJsonVO);
		API_DEF_ADD_TAG(API_TAG);
		API_DEF_ADD_PAGE_PARAMS();
		API_DEF_ADD_QUERY_PARAMS(Int32, "lesson_id", ZH_WORDS_GETTER("evaluate.field.lesson_id"), 8364, false);

	}
	ENDPOINT(API_M_GET, "course/record-comment/cs-comment-list", queryEvaluation, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
		// 解析查询参数为Query领域模型
		API_HANDLER_QUERY_PARAM(userQuery, EvaluationQuery, queryParams);
		// 呼叫执行函数响应结果
		API_HANDLER_RESP_VO(execQueryEvaluation(userQuery));
	}

	// 3. 定义 点评指定学员
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("evaluate.title2"), modifyEvaluation, EvaluateRspJsonVO::Wrapper, API_TAG);
	// 3.2 定义修改接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "course/record-comment/comment-stu", modifyEvaluation, BODY_DTO(EvaluationDTO::Wrapper, dto), execModifyEvaluate(dto, authObject->getPayload()));

private:	//定义接口执行函数
	EvaluatePageJsonVO::Wrapper execQueryEvaluation(const EvaluationQuery::Wrapper& query);

	EvaluateRspJsonVO::Wrapper execModifyEvaluate(const EvaluationDTO::Wrapper& dto, const PayloadDTO& payload);

};


#undef API_TAG


#include OATPP_CODEGEN_END(ApiController)

#endif
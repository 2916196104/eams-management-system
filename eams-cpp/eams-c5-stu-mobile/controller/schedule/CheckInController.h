#pragma once
#ifndef _CHECK_IN_CONTROLLER_H
#define  _CHECK_IN_CONTROLLER_H
#include "domain/vo/BaseJsonVO.h"
#include "domain/query/PageQuery.h"
#include"ApiHelper.h"
#include"ServerInfo.h"
#include "Macros.h"
#include"../../domain/vo/schedule/CheckInVO.h"
#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("CheckIn.tag")
class CheckInController :public oatpp::web::server::api::ApiController {
	API_ACCESS_DECLARE(CheckInController);
public:
	ENDPOINT_INFO(CheckIn) {
		info->summary = ZH_WORDS_GETTER("CheckIn.summary");
		API_DEF_ADD_AUTH();
		API_DEF_ADD_TAG(API_TAG);
		API_DEF_ADD_RSP_JSON(CheckInJsonVO::Wrapper);
		API_DEF_ADD_QUERY_PARAMS(Int32, "studentId", ZH_WORDS_GETTER("CheckIn.field.studentId"), 1, true);
		API_DEF_ADD_QUERY_PARAMS(Int32, "courseId", ZH_WORDS_GETTER("CheckIn.field.courseId"), 1, true);
		API_DEF_ADD_QUERY_PARAMS(String, "signTime", ZH_WORDS_GETTER("CheckIn.field.signTime"), "2025-11-23:15:35:20", true);
	}
	ENDPOINT(API_M_POST, "/schedule", CheckIn, QUERIES(QueryParams, params), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_QUERY_PARAM(query, PageQuery, params);
		API_HANDLER_RESP_VO(executeCheckIn(query));
	}
private:
	StringJsonVO::Wrapper executeCheckIn(const PageQuery::Wrapper& query);
};
#include OATPP_CODEGEN_END(ApiController)


#endif 



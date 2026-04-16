#pragma once

#ifndef _LESSON_CONTROLLER_ 
#define _LESSON_CONTROLLER_ 

#include "domain/vo/BaseJsonVO.h"
#include "ApiHelper.h"
#include "ServerInfo.h"
#include"domain/dto/staff/LessonDTO.h"
// 1 定义API控制器使用宏
#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("staff.tag")

/*
 * 授课记录控制器
 */
class LessonController : public oatpp::web::server::api::ApiController // 1 继承控制器
{
  // 2 定义控制器访问入口
  API_ACCESS_DECLARE(LessonController);
  // 3 定义接口
public:
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("staff.get-lesson-record.summary"), getLessonRecord, LessonQuery,StringJsonVO::Wrapper, ZH_WORDS_GETTER("staff.tag"));

	ENDPOINT(API_M_GET, "/c2-org/staff/lesson/list", getLessonRecord, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_QUERY_PARAM(lessonQuery, LessonQuery, queryParams);
		API_HANDLER_RESP_VO(executeGetLessonRecord(lessonQuery));
	}
private: // 定义接口执行函数
	StringJsonVO::Wrapper executeGetLessonRecord(const LessonQuery::Wrapper& lessonQuery);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController) //<- End Codegen
#endif // !_POSITION_CONTROLLER_

#pragma once
#ifndef _LESSON_CONTROLLER_
#define _LESSON_CONTROLLER_

#include "domain/vo/BaseJsonVO.h"
#include "domain/query/lesson/LessonQuery.h"
#include "domain/vo/lesson/LessonVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("lesson.tags.main")

class LessonController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(LessonController);

public:
	// 获取课表列表 (GET)
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("lesson.list.summary"), listLesson, LessonQuery, LessonPageJsonVO::Wrapper, API_TAG);
	API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/app/sCenter/lesson/list", listLesson, LessonQuery, execListLesson(query, authObject->getPayload()));

	// 学生签到 (POST) - 改用 PATH 参数定义
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("lesson.sign.summary"),
		signLesson,
		StringJsonVO::Wrapper,
		API_TAG,
		API_DEF_ADD_PATH_PARAMS(Int64, "lessonId", ZH_WORDS_GETTER("lesson.field.id"), 1, true);
	);

	API_HANDLER_ENDPOINT_AUTH(
		API_M_POST,
		"/app/sCenter/lesson/sign/{lessonId}",
		signLesson,
		PATH(Int64, lessonId), // 从 URL 路径中提取 lessonId
		execSignLesson(lessonId, authObject->getPayload())
	);

private:
	LessonPageJsonVO::Wrapper execListLesson(const LessonQuery::Wrapper& query, const PayloadDTO& payload);
	StringJsonVO::Wrapper execSignLesson(const Int64& lessonId, const PayloadDTO& payload);
};

#undef API_TAG

#include OATPP_CODEGEN_END(ApiController)
#endif // _LESSON_CONTROLLER_
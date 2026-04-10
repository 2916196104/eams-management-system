#pragma once



#ifndef _LESSONCOMMENT_CONTROLLER_
#define _LESSONCOMMENT_CONTROLLER_

#include "ApiHelper.h"
#include "ServerInfo.h"
#include "Macros.h"
#include "domain/query/PageQuery.h"
#include "domain/dto/home/LessonComment/LessonCommentDTO.h"
#include "domain/vo/home/LessonComment/LessonCommentVO.h"
#include "domain/query/home/LessonComment/LessonCommentQuery.h"

#include OATPP_CODEGEN_BEGIN(ApiController)
class LessonCommentController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(LessonCommentController);
public:
	ENDPOINT_INFO(LessonComment)
	{
		info->summary = ZH_WORDS_GETTER("LessonComment.query-all.summary");
		API_DEF_ADD_AUTH();

		API_DEF_ADD_RSP_JSON(LessonCommentPageJsonVO::Wrapper);
		API_DEF_ADD_RSP_JSON_WRAPPER(LessonCommentPageJsonVO);

		API_DEF_ADD_TAG(ZH_WORDS_GETTER("LessonComment.tag"));

		API_DEF_ADD_PAGE_PARAMS();
		API_DEF_ADD_QUERY_PARAMS(Int64, "student_id", ZH_WORDS_GETTER("LessonComment.field.student_id"), 1, true);
	}

	ENDPOINT(API_M_GET, "/c5home/lessoncomment", LessonComment, QUERIES(QueryParams, params), API_HANDLER_AUTH_PARAME)
	{
		API_HANDLER_QUERY_PARAM(query, LessonCommentQuery, params);
		API_HANDLER_RESP_VO(executeQueryLessonComment(query));
	}

private:
	LessonCommentPageJsonVO::Wrapper executeQueryLessonComment(const LessonCommentQuery::Wrapper& query);
};



#include OATPP_CODEGEN_END(ApiController)


#endif
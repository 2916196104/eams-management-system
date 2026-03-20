#include "stdafx.h"
#include "LessonCommentController.h"
#include "../../../service/home/LessonComment/LessonCommentService.h"


LessonCommentPageJsonVO::Wrapper LessonCommentController::executeQueryLessonComment(const LessonCommentQuery::Wrapper& query)
{
	auto result = LessonCommentService().listAll(query);
	auto jvo = LessonCommentPageJsonVO::createShared();
	jvo->success(result);
	return jvo;
}
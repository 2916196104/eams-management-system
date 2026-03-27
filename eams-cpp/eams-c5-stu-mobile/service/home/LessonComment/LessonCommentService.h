#pragma once

#include "domain/vo/home/LessonComment/LessonCommentVO.h"
#include "domain/dto/home/LessonComment/LessonCommentDTO.h"
#include "domain/query/home/LessonComment/LessonCommentQuery.h"


class LessonCommentService
{
public:
	LessonCommentPageDTO::Wrapper listAll(const LessonCommentQuery::Wrapper& query);
};
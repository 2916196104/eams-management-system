#pragma once




#ifndef _LESSONCOMMENT_DAO_
#define _LESSONCOMMENT_DAO_
#include "BaseDAO.h"
#include "domain/do/home/LessonComment/LessonCommentDO.h"
#include "domain/query/home/LessonComment/LessonCommentQuery.h"

class LessonCommentDAO: public BaseDAO
{
private:
	inline std::string queryConditionBuilder(const LessonCommentQuery::Wrapper& query, SqlParams& params);

public:
	uint64_t count(const LessonCommentQuery::Wrapper& query);
	// 分页查询数据
	std::list<LessonCommentDO> selectWithPage(const LessonCommentQuery::Wrapper& query);
};

#endif
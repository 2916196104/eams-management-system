#pragma once

#include "domain/query/HomeWork/homeworklist/HomeworkListQuery.h"
#include "domain/dto/Homework/homeworklist/HomeworkListDTO.h"
#include "domain/vo/HomeWork/homeworklist/HomeworkListVO.h"

class HomeworkListService
{
public:
	// 分页查询所有数据
	HomeworkListPageDTO::Wrapper listAll(const HomeworkListQuery::Wrapper& query);
};
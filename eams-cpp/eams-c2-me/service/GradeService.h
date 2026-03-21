#pragma once
#include "./domain/query/GradeQuery.h"
#include "./domain/dto/student/GradeDTO.h"

/**
 * 用户业务逻辑类
 */
class GradeService
{

public:
	// 查询所有可选年级
	GradePageDTO::Wrapper listAllGrade(const GradeQuery::Wrapper& query);

};
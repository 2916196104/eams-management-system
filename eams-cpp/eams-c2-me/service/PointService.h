#pragma once


#include "./domain/query/PointQuery.h"
#include "./domain/dto/student/PointDTO.h"

/**
 * 用户业务逻辑类
 */
class PointService
{

public:
	// 查询所有学分
	PointPageDTO::Wrapper listAll(const PointQuery::Wrapper& query);

};




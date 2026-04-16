#pragma once


#include "../eams-c7-workbench/domain/vo/StudentRecord/StlistVO.h"
#include "../eams-c7-workbench/domain/query/StudentRecord/StlistQuery.h"
#include "../eams-c7-workbench/domain/dto/StudentRecord/StlistDTO.h"

class StlistService
{
public:
	// 分页查询所有数据
	StlistPageDTO::Wrapper listAll(const StlistQuery::Wrapper& query);

};
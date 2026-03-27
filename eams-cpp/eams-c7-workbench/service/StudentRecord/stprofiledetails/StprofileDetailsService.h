#pragma once



#include "../eams-c7-workbench/domain/query/StudentRecord/StlistQuery.h"
#include "../eams-c7-workbench/domain/vo/StudentRecord/StprofileDetailsVO.h"
#include "../eams-c7-workbench/domain/query/StudentRecord/StprofileDetailsQuery.h"
#include "../eams-c7-workbench/domain/dto/StudentRecord/StprofileDetailsDTO.h"

class StprofileDetailsService
{
public:
	// 分页查询所有数据
	StprofileDetailsPageDTO::Wrapper listAll(const StlistQuery::Wrapper& query);

};
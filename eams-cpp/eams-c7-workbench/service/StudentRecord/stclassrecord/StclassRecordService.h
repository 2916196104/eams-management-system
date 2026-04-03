#pragma once



#include "../eams-c7-workbench/domain/query/StudentRecord/StlistQuery.h"
#include "../eams-c7-workbench/domain/vo/StudentRecord/StclassRecordVO.h"
#include "../eams-c7-workbench/domain/query/StudentRecord/StclassRecordQuery.h"
#include "../eams-c7-workbench/domain/dto/StudentRecord/StclassRecordDTO.h"

class StclassRecordService
{
public:
	// 分页查询所有数据
	StclassRecordPageDTO::Wrapper listAll(const StlistQuery::Wrapper& query);
};
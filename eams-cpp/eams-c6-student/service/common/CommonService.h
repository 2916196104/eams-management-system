#pragma once




#ifndef _SAMPLE_SERVICE_
#define _SAMPLE_SERVICE_
//#include "domain/vo/sample/SampleVO.h"
//#include "domain/query/sample/SampleQuery.h"
#include "../../domain/dto/common/CommonDTO.h"





/**
 * 调整积分服务层
 */
class AdjustPointsService
{
public:
	// 修改数据
	bool updateData(const ModifyPointsDTO::Wrapper& dto);
};





/**
 * 添加跟进记录服务层
 */
class AddFollowUpRecordService
{
public:
	// 修改数据
	bool updateData(const AddFollowUpRecordDTO::Wrapper& dto);
};












#endif // !_SAMPLE_SERVICE_



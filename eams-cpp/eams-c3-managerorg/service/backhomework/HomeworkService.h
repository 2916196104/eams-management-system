#pragma once

#ifndef _HOMEWORK_SERVICE_
#define _HOMEWORK_SERVICE_
#include "../../domain/vo/backhomework/backhomeworkVO.h"
#include "../../domain/query/backhomework/backhomeworkQuery.h"
#include "../../domain/dto/backhomework/backhomeworkDTO.h"
#include "../../domain/do/homework/HomeworkDO.h"
#include "../../domain/do/homework/HomeworkRecordDO.h"
#include "../../dao/homework/HomeworkRecordDao.h"


/**
 * 示例服务实现，演示基础的示例服务实现
 */
class HomeworkService
{
public:
	// 获取作业列表，分页查询
	GetHomeworkListPageDTO::Wrapper gethomeworklist(const GetHomeworkListQuery::Wrapper& query);
	// 获取作业详情
	GetHomeworkDetailDTO::Wrapper gethomeworkdetail(int64_t id);
	// 保存作业
	bool saveHomework(const SaveHomeworkDTO::Wrapper& dto);
};

#endif 


#pragma once

#ifndef _TIMEABLE_SERVICE_
#define _TIMEABLE_SERVICE_
// 替换为Homework相关VO/Query/DTO头文件（路径按项目实际结构调整）
#include "domain/vo/schedule/TimeablekVO.h"
#include "domain/query/schedule/TimeableQuery.h"
#include "domain/dto/schedule/TimeableDTO.h"

// 服务类名改为HomeworkService，贴合作业业务语义
class ScheduleTimeableService
{
public:
    // 方法返回值和参数均替换为Homework相关DTO/Query，匹配作业表分页查询逻辑
    ScheduleTimeablePageDTO::Wrapper listAll(const ScheduleTimeableQuery::Wrapper& query);
};

#endif // !_TIMEABLE_SERVICE_
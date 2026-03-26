#pragma once

#ifndef _HOMEWORK_SERVICE_
#define _HOMEWORK_SERVICE_
// 替换为Homework相关VO/Query/DTO头文件（路径按项目实际结构调整）
#include "domain/vo/home/homework/HomeworkVO.h"
#include "domain/query/home/homework/HomeworkQuery.h"
#include "domain/dto/home/homework/HomeworkDTO.h"

// 服务类名改为HomeworkService，贴合作业业务语义
class HomeworkService
{
public:
    // 方法返回值和参数均替换为Homework相关DTO/Query，匹配作业表分页查询逻辑
    HomeworkPageDTO::Wrapper listAll(const HomeworkQuery::Wrapper& query);
};

#endif // !_HOMEWORK_SERVICE_
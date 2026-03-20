#pragma once

#ifndef _HOMEWORK_DAO_
#define _HOMEWORK_DAO_
#include "BaseDAO.h"
// 引入homework表对应的DO和Query头文件（路径需根据实际项目调整）
#include "../../../domain/do/home/homework/HomeworkDO.h"
#include "../../../domain/query/home/homework/HomeworkQuery.h"

// DAO类名改为HomeworkDAO，继承BaseDAO保持不变
class HomeworkDAO : public BaseDAO
{
private:
    // 内部条件构建方法：参数替换为HomeworkQuery，适配作业表查询条件
    inline std::string queryConditionBuilder(const HomeworkQuery::Wrapper& query, SqlParams& params);
public:
    // 统计作业数据条数：参数替换为HomeworkQuery
    uint64_t count(const HomeworkQuery::Wrapper& query);
    // 分页查询作业数据：参数为HomeworkQuery，返回值为HomeworkDO列表
    std::list<HomeworkDO> selectWithPage(const HomeworkQuery::Wrapper& query);
};

#endif // !_HOMEWORK_DAO_
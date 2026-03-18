#pragma once

#ifndef _CLASS_STUDENT_DAO_
#define _CLASS_STUDENT_DAO_
#include "BaseDAO.h"
// 替换DO和Query的头文件路径，适配ClassStudent命名
#include "../../../domain/do/home/class/ClassStudentDO.h"
#include "../../../domain/query/home/class/ClassStudentQuery.h"

// DAO类名改为ClassStudentDAO，继承BaseDAO不变
class ClassStudentDAO : public BaseDAO
{
private:
    // 内部方法名不变，参数替换为ClassStudentQuery
    inline std::string queryConditionBuilder(const ClassStudentQuery::Wrapper& query, SqlParams& params);
public:
    // 统计数据条数：参数替换为ClassStudentQuery
    uint64_t count(const ClassStudentQuery::Wrapper& query);
    // 分页查询数据：参数和返回值均替换为ClassStudent相关
    std::list<ClassStudentDO> selectWithPage(const ClassStudentQuery::Wrapper& query);
};

#endif // !_CLASS_STUDENT_DAO_
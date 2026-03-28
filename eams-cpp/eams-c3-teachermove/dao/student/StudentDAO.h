#pragma once
#pragma once
#ifndef _STUDENT_DAO_
#define _STUDENT_DAO_

#include "BaseDAO.h"
#include "../../domain/do/student/StudentDO.h"
#include "../../domain/query/student/StudentQuery.h"

/**
 * 示例表数据库操作实现
 */
class StudentDAO : public BaseDAO
{
private:
    //************************************
    // Method:      queryConditionBuilder
    // FullName:    StudentDAO::queryConditionBuilder
    // Access:      private 
    // Returns:     std::string 返回条件SQL语句，即WHERE部分的语句
    // Parameter:   const StudentQuery::Wrapper& query 查询数据对象
    // Parameter:   SqlParams& params 存放查询数据的参数对象
    // Description: 查询条件构建器，根据StudentQuery对象动态构建查询条件相关参数
    //************************************
    inline std::string queryConditionBuilder(
        const StudentQuery::Wrapper& query, SqlParams& params);

public:
    // 统计数据条数
    uint64_t count(const StudentQuery::Wrapper& query);

    // 分页查询数据
    std::list<StudentDO> selectWithPage(const StudentQuery::Wrapper& query);

    // 通过姓名查询数据
    // std::list<StudentDO> selectByName(const string& name);

    // 通过ID查询数据
    StudentDO selectById(std::string id);

    // 插入数据
    uint64_t insert(const StudentDO& data);

    // 批量插入数据
    uint64_t insertBatch(const std::list<StudentDO>& datas);

    // 更新数据
    uint64_t update(const StudentDO& data);

    // 通过ID删除数据
    uint64_t deleteById(const std::string& id);
};

#endif // !_SAMPLE_DAO_
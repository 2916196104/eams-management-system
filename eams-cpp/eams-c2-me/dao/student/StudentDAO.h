#pragma once
#ifndef _STUDENTDAO_H_
#define _STUDENTDAO_H_

#include "BaseDAO.h"
#include "domain/do/student/StudentDO.h"
#include "domain/dto/student/StudentDTO.h"
#include "domain/query/student/StudentQuery.h"
#include <cstdint>

class StudentDAO :public BaseDAO
{
public:
    // 统计学员总数（分页用）
    uint64_t count(const StudentQuery::Wrapper& query);
    // 分页查询学员列表
    std::list<PtrStudentDO> selectAll(const StudentQuery::Wrapper& query);
    // 根据ID检查学员是否存在（切换学员用）
    bool findById(uint64_t id);
    // 根据ID软删除学员（deleted=1）
    bool deleteById(uint64_t id);
    // 按ID查询单个学员（预留）
    PtrStudentDO selectById(const string& id);
};

#endif
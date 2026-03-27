#pragma once
#ifndef _SAMPLE_MAPPER_
#define _SAMPLE_MAPPER_

#include "Mapper.h"
#include "../../domain/do/student/StudentDO.h"

/**
 * student表字段匹配映射
 */
class StudentMapper : public Mapper<StudentDO>
{
public:
    StudentDO mapper(ResultSet* resultSet) const override
    {
        StudentDO data;
        // 按照 SELECT 字段顺序映射
        data.setName(resultSet->getString(1));     // 第1列：s.name
        data.setMobile(resultSet->getString(2));   // 第2列：u.mobile
        data.setGender(resultSet->getInt(3));        // 第3列：s.gender
        return data;
    }
};

/**
 * 创建智能指针对象
 */
class PtrStudentMapper : public Mapper<PtrStudentDO>
{
public:
    PtrStudentDO mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<StudentDO>();
        data->setName(resultSet->getString(1));     // 第1列：s.name
        data->setMobile(resultSet->getString(2));   // 第2列：u.mobile
        data->setGender(resultSet->getInt(3));        // 第3列：s.gender
        return data;
    }
};

#endif // !_SAMPLE_MAPPER_
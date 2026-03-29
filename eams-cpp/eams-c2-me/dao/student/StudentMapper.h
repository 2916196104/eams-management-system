#pragma once
#ifndef _STUDENTMAPPER_H_
#define _STUDENTMAPPER_H_

#include "Mapper.h"
#include "domain/do/Student/StudentDO.h"
#include <string>  // 确保 stoull 可用

// 定义mapper方便StudentDAO使用
class StudentMapper : public Mapper<PtrStudentDO>
{
public:
    PtrStudentDO mapper(ResultSet* resultSet) const override
    {
        PtrStudentDO stuDO = make_shared<StudentDO>();
        // 只映射接口需要的字段：数据库字段名 → DO 的 set 方法
        // 1. id：数据库字符串 → 转换为 uint64_t
        stuDO->setId(std::stoull(resultSet->getString("id")));
        stuDO->setName(resultSet->getString("name"));
        // 2. gender：数据库 int → 转换为 char
        stuDO->setGender(static_cast<char>(resultSet->getInt("gender")));
        // 3. stage：数据库 int → 转换为 char
        stuDO->setStage(static_cast<char>(resultSet->getInt("stage")));
        stuDO->setBirthday(resultSet->getString("birthday"));
        stuDO->setHeadImg(resultSet->getString("head_img"));
        // 4. credit：数据库 int → 转换为 char
        stuDO->setCredit(static_cast<char>(resultSet->getInt("credit")));
        return stuDO;
    }
};

#endif
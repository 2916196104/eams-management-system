#pragma once
#ifndef _STUDENTMAPPER_H_
#define _STUDENTMAPPER_H_

#include "Mapper.h"
#include "domain/do/Student/StudentDO.h"
#include <string>

class StudentMapper : public Mapper<PtrStudentDO>
{
public:
    PtrStudentDO mapper(ResultSet* resultSet) const override
    {
        PtrStudentDO stuDO = make_shared<StudentDO>();
        // 数据库字段 → DO 完全匹配新类型
        stuDO->setId(std::stoull(resultSet->getString("id")));  // uint64_t
        stuDO->setName(resultSet->getString("name"));
        stuDO->setGender(resultSet->getInt("gender"));         // int 直接赋值
        stuDO->setStage(resultSet->getInt("stage"));           // int 直接赋值
        stuDO->setBirthday(resultSet->getString("birthday"));
        stuDO->setHeadImg(resultSet->getString("head_img"));
        stuDO->setCredit(resultSet->getInt("credit"));         // int 直接赋值
        return stuDO;
    }
};

#endif
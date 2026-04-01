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
        // 严格匹配 StudentDO 类型，int 直接赋值，无强转
        stuDO->setId(std::stoull(resultSet->getString("id")));
        stuDO->setUserId(std::stoull(resultSet->getString("user_id")));
        stuDO->setFamilyRel(resultSet->getInt("family_rel"));
        stuDO->setAsDefault(resultSet->getInt("as_default"));
        stuDO->setSchoolId(std::stoull(resultSet->getString("school_id")));
        stuDO->setName(resultSet->getString("name"));
        stuDO->setDeleted(resultSet->getInt("deleted"));
        stuDO->setStage(resultSet->getInt("stage"));
        stuDO->setGender(resultSet->getInt("gender"));
        stuDO->setBirthday(resultSet->getString("birthday"));
        stuDO->setHeadImg(resultSet->getString("head_img"));
        stuDO->setCredit(resultSet->getInt("credit"));

        return stuDO;
    }
};
#endif
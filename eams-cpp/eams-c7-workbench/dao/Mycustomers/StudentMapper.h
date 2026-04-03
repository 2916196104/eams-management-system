#pragma once
#ifndef _StudentMapper_
#define _StudentMapper_

#include "Mapper.h"
#include "domain/do/Mycustomers/StudentDo.h"

// 学员映射
class StudentMapper : public Mapper<StudentDO>
{
public:
    StudentDO mapper(ResultSet* resultSet) const override
    {
        StudentDO data;
        data.setId(resultSet->getInt64(1));
        data.setUserId(resultSet->getInt64(2));
        data.setFamilyRel(resultSet->getInt(3));
        data.setAsDefault(resultSet->getInt(4));
        data.setSchoolId(resultSet->getInt64(5));
        data.setName(resultSet->getString(6));
        data.setDeleted(resultSet->getInt(7));
        data.setStage(resultSet->getInt(8));
        data.setGender(resultSet->getInt(9));
        data.setBirthday(resultSet->getString(10));
        data.setHeadImg(resultSet->getString(11));
        data.setJoinWay(resultSet->getInt64(12));
        data.setRemark(resultSet->getString(13));
        data.setGraduationDate(resultSet->getString(14));
        data.setGraduationReason(resultSet->getString(15));
        data.setAddTime(resultSet->getString(16));
        data.setCounselor(resultSet->getInt64(17));
        data.setCreator(resultSet->getInt64(18));
        data.setEditor(resultSet->getInt64(19));
        data.setEditTime(resultSet->getString(20));
        data.setIdcard(resultSet->getString(21));
        data.setRedpointGrade(resultSet->getString(22));
        data.setRedpointEvaluate(resultSet->getString(23));
        data.setGrade(resultSet->getInt(24));
        data.setJoinDate(resultSet->getString(25));
        data.setWxAccessId(resultSet->getInt64(26));
        data.setCredit(resultSet->getInt(27));
        data.setOrgId(resultSet->getInt64(28));
        data.setGradeId(resultSet->getInt(29));

        data.setMobile(resultSet->getString(30));
        data.setAge(resultSet->getInt(31));

        return data;
    }
};

// 学员智能指针映射
class PtrStudentMapper : public Mapper<PtrStudentDO>
{
public:
    PtrStudentDO mapper(ResultSet* resultSet) const override
    {
        auto data = make_shared<StudentDO>();
        data->setId(resultSet->getInt64(1));
        data->setUserId(resultSet->getInt64(2));
        data->setFamilyRel(resultSet->getInt(3));
        data->setAsDefault(resultSet->getInt(4));
        data->setSchoolId(resultSet->getInt64(5));
        data->setName(resultSet->getString(6));
        data->setDeleted(resultSet->getInt(7));
        data->setStage(resultSet->getInt(8));
        data->setGender(resultSet->getInt(9));
        data->setBirthday(resultSet->getString(10));
        data->setHeadImg(resultSet->getString(11));
        data->setJoinWay(resultSet->getInt64(12));
        data->setRemark(resultSet->getString(13));
        data->setGraduationDate(resultSet->getString(14));
        data->setGraduationReason(resultSet->getString(15));
        data->setAddTime(resultSet->getString(16));
        data->setCounselor(resultSet->getInt64(17));
        data->setCreator(resultSet->getInt64(18));
        data->setEditor(resultSet->getInt64(19));
        data->setEditTime(resultSet->getString(20));
        data->setIdcard(resultSet->getString(21));
        data->setRedpointGrade(resultSet->getString(22));
        data->setRedpointEvaluate(resultSet->getString(23));
        data->setGrade(resultSet->getInt(24));
        data->setJoinDate(resultSet->getString(25));
        data->setWxAccessId(resultSet->getInt64(26));
        data->setCredit(resultSet->getInt(27));
        data->setOrgId(resultSet->getInt64(28));
        data->setGradeId(resultSet->getInt(29));

        data->setMobile(resultSet->getString(30));
        data->setAge(resultSet->getInt(31));

        return data;
    }
};

#endif // !_StudentMapper_
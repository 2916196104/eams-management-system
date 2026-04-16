#pragma once
#ifndef _StudentCourseMapper_
#define _StudentCourseMapper_

#include "Mapper.h"
#include "../../domain/do/Mycustomers/StudentCourseDo.h"

// 学员课程映射 
class StudentCourseMapper : public Mapper<StudentCourseDO>
{
public:
    StudentCourseDO mapper(ResultSet* resultSet) const override
    {
        StudentCourseDO data;
        data.setId(resultSet->getInt64(1));
        data.setStudentId(resultSet->getInt64(2));
        data.setCourseId(resultSet->getInt64(3));
        data.setSubjectId(resultSet->getInt64(4));
        data.setStartDate(resultSet->getString(5));
        data.setExpireDate(resultSet->getString(6));
        data.setRemark(resultSet->getString(7));
        data.setCountLessonTotal(resultSet->getInt(8));
        data.setCountLessonComplete(resultSet->getInt(9));
        data.setCountLessonRefund(resultSet->getInt(10));
        data.setCourseAmount(resultSet->getDouble(11));
        data.setDiscountAmount(resultSet->getDouble(12));
        data.setAmount(resultSet->getDouble(13));
        data.setPaidAmount(resultSet->getDouble(14));
        data.setPayOff(resultSet->getInt(15));
        data.setOperator(resultSet->getInt64(16));
        data.setCreator(resultSet->getInt64(17));
        data.setAddTime(resultSet->getString(18));
        data.setEditor(resultSet->getInt64(19));
        data.setEditTime(resultSet->getString(20));
        data.setDeleted(resultSet->getBoolean(21));
        data.setVerifyState(resultSet->getInt(22));
        data.setWarningTimes(resultSet->getInt(23));
        data.setPriority(resultSet->getInt(24));
        data.setUnitPrice(resultSet->getDouble(25));
        data.setFromTrial(resultSet->getInt(26));
        data.setOrgId(resultSet->getInt64(27));

        data.setCourseName(resultSet->getString(28));
        return data;
    }
};

// 学员课程指针映射
class PtrStudentCourseMapper : public Mapper<PtrStudentCourseDO>
{
public:
    PtrStudentCourseDO mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<StudentCourseDO>();
        data->setId(resultSet->getInt64(1));
        data->setStudentId(resultSet->getInt64(2));
        data->setCourseId(resultSet->getInt64(3));
        data->setSubjectId(resultSet->getInt64(4));
        data->setStartDate(resultSet->getString(5));
        data->setExpireDate(resultSet->getString(6));
        data->setRemark(resultSet->getString(7));
        data->setCountLessonTotal(resultSet->getInt(8));
        data->setCountLessonComplete(resultSet->getInt(9));
        data->setCountLessonRefund(resultSet->getInt(10));
        data->setCourseAmount(resultSet->getDouble(11));
        data->setDiscountAmount(resultSet->getDouble(12));
        data->setAmount(resultSet->getDouble(13));
        data->setPaidAmount(resultSet->getDouble(14));
        data->setPayOff(resultSet->getInt(15));
        data->setOperator(resultSet->getInt64(16));
        data->setCreator(resultSet->getInt64(17));
        data->setAddTime(resultSet->getString(18));
        data->setEditor(resultSet->getInt64(19));
        data->setEditTime(resultSet->getString(20));
        data->setDeleted(resultSet->getBoolean(21));
        data->setVerifyState(resultSet->getInt(22));
        data->setWarningTimes(resultSet->getInt(23));
        data->setPriority(resultSet->getInt(24));
        data->setUnitPrice(resultSet->getDouble(25));
        data->setFromTrial(resultSet->getInt(26));
        data->setOrgId(resultSet->getInt64(27));

        data->setCourseName(resultSet->getString(28));
        return data;
    }
};

#endif // !_StudentCourseMapper_
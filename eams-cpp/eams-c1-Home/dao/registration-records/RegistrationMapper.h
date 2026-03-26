/*
 @Author: abinng
 @Date: 2026/03/23 18:41:58
 @File: RegistrationMapper.h
*/
#pragma once
#ifndef _REGISTRATION_MAPPER_H_
#define _REGISTRATION_MAPPER_H_ 

#include "Mapper.h"
#include "domain/do/registration-records/RegistrationDO.h"

class RegistrationMapper : public Mapper<PtrRegistrationViewDO> {
public:
    PtrRegistrationViewDO mapper(ResultSet* resultSet) const override
    {
        PtrRegistrationViewDO registration = std::make_shared<RegistrationViewDO>();
        registration->setId(resultSet->getUInt64("id"));
        registration->setStudentId(resultSet->getUInt64("student_id"));
        registration->setStudentName(resultSet->getString("student_name"));
        registration->setCourseId(resultSet->getUInt64("course_id"));
        registration->setCourseName(resultSet->getString("course_name"));
        registration->setSubjectId(resultSet->getUInt64("subject_id"));
        registration->setSubjectName(resultSet->getString("subject_name"));
        registration->setAddTime(resultSet->getString("add_time"));
        registration->setExpireDate(resultSet->getString("expire_date"));
        registration->setAmount(resultSet->getDouble("amount"));
        registration->setPaidAmount(resultSet->getDouble("paid_amount"));
        registration->setCountLessonTotal(resultSet->getInt("count_lesson_total"));
        registration->setCountLessonComplete(resultSet->getInt("count_lesson_complete"));
        registration->setLessonType(resultSet->getInt("lesson_type"));
        registration->setVerifyState(resultSet->getInt("verify_state"));
        return registration;
    }
};


#endif // !_REGISTRATION_MAPPER_H_
#pragma once
#ifndef _CLASS_STUDENT_MAPPER_H_
#define _CLASS_STUDENT_MAPPER_H_

#include <Mapper.h>
#include <domain/do/class_student/ClassStudentDO.h>
#include <memory>

using PtrClassStudentDO = std::shared_ptr<ClassStudentDO>;

class ClassStudentMapper : public Mapper<PtrClassStudentDO>
{
public:
    PtrClassStudentDO mapper(ResultSet* resultSet) const override
    {
        // 1. 创建 DO 对象
        PtrClassStudentDO doObj = std::make_shared<ClassStudentDO>();

        // 2. 从 resultSet 提取数据库的列数据，塞进 DO 对象里
        doObj->setId(resultSet->getUInt64("id"));
        doObj->setClassId(resultSet->getInt64("class_id"));
        doObj->setStudentId(resultSet->getInt64("student_id"));
        doObj->setAddTime(resultSet->getString("add_time"));
        doObj->setCreator(resultSet->getInt64("creator"));
        doObj->setReason(resultSet->getInt("reason"));
        doObj->setDeleted(resultSet->getInt("deleted"));
        doObj->setRemark(resultSet->getString("remark"));
        doObj->setConsumeCourseId(resultSet->getInt64("consume_course_id"));

        // 3. 返回装配好的对象
        return doObj;
    }
};

#endif
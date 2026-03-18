#pragma once

#ifndef _CLASS_STUDENT_MAPPER_
#define _CLASS_STUDENT_MAPPER_
#include "Mapper.h"
#include "../../../domain/do/home/class/ClassStudentDO.h"  // 路径改为ClassStudentDO

// 类名从 ClassMapper 改为 ClassStudentMapper，泛型同步替换为 ClassStudentDO
class ClassStudentMapper : public Mapper<ClassStudentDO>
{
public:
    // 返回值和参数内的DO类均替换为 ClassStudentDO
    ClassStudentDO mapper(ResultSet* resultSet) const override
    {
        ClassStudentDO data;  // 实例化对象改为 ClassStudentDO
        // 字段映射逻辑完全保留，仅对象类型变更
        data.setId(resultSet->getUInt64(1));                // 1. 主键id (uint64_t)
        data.setClassId(resultSet->getUInt64(2));           // 2. 班级ID class_id (uint64_t)
        data.setStudentId(resultSet->getUInt64(3));         // 3. 学生ID student_id (uint64_t)
        data.setAddTime(resultSet->getString(4));           // 4. 添加时间 add_time (string)
        data.setCreator(resultSet->getUInt64(5));           // 5. 创建人 creator (uint64_t)
        data.setReason(resultSet->getInt(6));               // 6. 加入原因 reason (int)
        data.setDeleted(resultSet->getInt(7));              // 7. 删除标记 deleted (int)
        data.setRemark(resultSet->getString(8));            // 8. 备注 remark (string)
        data.setConsumeCourseId(resultSet->getUInt64(9));   // 9. 默认消费课程ID consume_course_id (uint64_t)

        return data;
    }
};

#endif // !_CLASS_STUDENT_MAPPER_
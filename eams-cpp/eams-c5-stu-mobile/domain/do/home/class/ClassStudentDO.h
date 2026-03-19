#pragma once

#ifndef _CLASS_STUDENT_DO_
#define _CLASS_STUDENT_DO_
#include "../../DoInclude.h"

// 类名统一为 ClassStudentDO
class ClassStudentDO : public BaseDO
{
    // ===================== 1. 定义属性 + 自动生成get/set方法 =====================
    // 主键ID
    MYSQL_SYNTHESIZE(uint64_t, id, Id);
    // 班级ID
    MYSQL_SYNTHESIZE(uint64_t, classId, ClassId);
    // 学生ID
    MYSQL_SYNTHESIZE(uint64_t, studentId, StudentId);
    // 添加时间
    MYSQL_SYNTHESIZE(string, addTime, AddTime);
    // 创建人
    MYSQL_SYNTHESIZE(uint64_t, creator, Creator);
    // 加入原因（tinyint）
    MYSQL_SYNTHESIZE(int, reason, Reason);
    // 删除标记（0-未删，1-已删）
    MYSQL_SYNTHESIZE(int, deleted, Deleted);
    // 备注信息
    MYSQL_SYNTHESIZE(string, remark, Remark);
    // 默认消费课程ID
    MYSQL_SYNTHESIZE(uint64_t, consumeCourseId, ConsumeCourseId);

public:
    // ===================== 2. 构造函数：绑定表名 + 字段映射 =====================
    // 类名改为 ClassStudentDO，表名仍为 class_student（与数据库一致）
    ClassStudentDO() : BaseDO("class_student")
    {
        // 主键字段映射（字段名，类型标识，类属性）
        MYSQL_ADD_FIELD_PK("id", "i", id);

        // 普通字段映射（严格对应数据库字段和类属性）
        MYSQL_ADD_FIELD("class_id", "i", classId);
        MYSQL_ADD_FIELD("student_id", "i", studentId);
        MYSQL_ADD_FIELD("add_time", "s", addTime);
        MYSQL_ADD_FIELD("creator", "i", creator);
        MYSQL_ADD_FIELD("reason", "i", reason);
        MYSQL_ADD_FIELD("deleted", "i", deleted);
        MYSQL_ADD_FIELD("remark", "s", remark);
        MYSQL_ADD_FIELD("consume_course_id", "i", consumeCourseId);
    }
};

// ===================== 3. 智能指针别名统一为 PtrClassStudentDO =====================
typedef std::shared_ptr<ClassStudentDO> PtrClassStudentDO;

#endif // !_CLASS_STUDENT_DO_
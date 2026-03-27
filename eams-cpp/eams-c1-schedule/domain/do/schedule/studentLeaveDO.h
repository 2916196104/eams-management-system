#pragma once
#ifndef _STUDENT_LEAVE_DO_H_
#define _STUDENT_LEAVE_DO_H_

#include "../DoInclude.h"

/**
 * @brief 学员请假表映射DO
 * 对应数据库表：student_leave
 */
class StudentLeaveDO : public BaseDO {
        MYSQL_SYNTHESIZE(uint64_t, id, Id)                     // 主键
        MYSQL_SYNTHESIZE(string, addTime, AddTime)             // 请假时间
        MYSQL_SYNTHESIZE(uint64_t, studentId, StudentId)       // 学生外键
        MYSQL_SYNTHESIZE(uint64_t, lessonId, LessonId)         // 请假课程外键
        MYSQL_SYNTHESIZE(string, reason, Reason)               // 请假原因
        MYSQL_SYNTHESIZE(int, state, State)                    // 请假状态
        MYSQL_SYNTHESIZE(uint64_t, verifyStaff, VerifyStaff)   // 审核/操作人
        MYSQL_SYNTHESIZE(string, verifyTime, VerifyTime)       // 审核/操作时间
        MYSQL_SYNTHESIZE(uint64_t, counselor, Counselor)       // 学生的顾问
        MYSQL_SYNTHESIZE(uint64_t, schoolId, SchoolId)         // 学生所属学校ID

public:
    StudentLeaveDO() : BaseDO("student_leave") {
        // 主键
        MYSQL_ADD_FIELD_PK("id", "ull", id);

        // 核心外键字段
        MYSQL_ADD_FIELD("student_id", "ull", studentId);
        MYSQL_ADD_FIELD("lesson_id", "ull", lessonId);
        MYSQL_ADD_FIELD("school_id", "ull", schoolId);

        // 业务信息字段 (允许为NULL的业务字段)
        MYSQL_ADD_FIELD_NULLABLE("add_time", "dt", addTime, true);
        MYSQL_ADD_FIELD_NULLABLE("reason", "s", reason, true);
        MYSQL_ADD_FIELD_NULLABLE("state", "i", state, true);
        MYSQL_ADD_FIELD_NULLABLE("verify_staff", "ull", verifyStaff, true);
        MYSQL_ADD_FIELD_NULLABLE("verify_time", "dt", verifyTime, true);
        MYSQL_ADD_FIELD_NULLABLE("counselor", "ull", counselor, true);
    }
};

// 定义智能指针别名
typedef std::shared_ptr<StudentLeaveDO> PtrStudentLeaveDO;

#endif // !_STUDENT_LEAVE_DO_H_
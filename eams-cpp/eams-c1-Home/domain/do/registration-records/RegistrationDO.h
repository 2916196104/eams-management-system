/*
 @Author: abinng
 @Date: 2026/03/23 18:43:01
 @File: RegistrationDO.h
*/
#pragma once
#ifndef _REGISTRATION_DO_H_
#define _REGISTRATION_DO_H_

#include "SqlHelper.h"
#include "RegistrationDO.h"
#include "../../do/DoInclude.h"
/**
 * 课时学员表数据模型
 */
class StudentCourseDO : public BaseDO {
    // 主键
    MYSQL_SYNTHESIZE(uint64_t, id, Id);
    // 学生id
    MYSQL_SYNTHESIZE(uint64_t, studentId, StudentId);
    // 课程id
    MYSQL_SYNTHESIZE(uint64_t, courseId, CourseId);
    // 科目id
    MYSQL_SYNTHESIZE(uint64_t, subjectId, SubjectId);
    // 报名时间
    MYSQL_SYNTHESIZE(string, addTime, AddTime);
    // 过期时间
    MYSQL_SYNTHESIZE(string, expireDate, ExpireDate);
    // 课程金额
    MYSQL_SYNTHESIZE(double, amount, Amount);
    // 实付金额
    MYSQL_SYNTHESIZE(double, paidAmount, PaidAmount);
    // 总课次
    MYSQL_SYNTHESIZE(int32_t, countLessonTotal, CountLessonTotal);
    // 已上课次
    MYSQL_SYNTHESIZE(int32_t, countLessonComplete, CountLessonComplete);
    // 审核状态
    MYSQL_SYNTHESIZE(int8_t, verifyState, VerifyState);

public:
    StudentCourseDO() : BaseDO("student_course")
    {
        MYSQL_ADD_FIELD_PK("id", "ull", id);
        MYSQL_ADD_FIELD_NULLABLE("student_id", "ull", studentId, false);
        MYSQL_ADD_FIELD_NULLABLE("course_id", "ull", courseId, false);
        MYSQL_ADD_FIELD_NULLABLE("subject_id", "ull", subjectId, false);
        MYSQL_ADD_FIELD_NULLABLE("add_time", "s", addTime, true);
        MYSQL_ADD_FIELD_NULLABLE("expire_date", "s", expireDate, true);
        MYSQL_ADD_FIELD_NULLABLE("amount", "d", amount, true);
        MYSQL_ADD_FIELD_NULLABLE("paid_amount", "d", paidAmount, true);
        MYSQL_ADD_FIELD_NULLABLE("count_lesson_total", "i", countLessonTotal, false);
        MYSQL_ADD_FIELD_NULLABLE("count_lesson_complete", "i", countLessonComplete, false);
        MYSQL_ADD_FIELD_NULLABLE("verify_state", "i", verifyState, false);
    }
};
// 给LessonStudentDO智能指针设定一个别名方便使用
typedef std::shared_ptr<StudentCourseDO> PtrStudentCourseDO;
/**
 * 点评记录视图对象，关联一些外表的字段
 */
class RegistrationViewDO : public StudentCourseDO {
    // 学生姓名---student 表的 name 字段
     MYSQL_SYNTHESIZE(string, studentName, StudentName);
    // 课程名称---course 表的 name 字段
     MYSQL_SYNTHESIZE(string, courseName, CourseName);
    // 科目名称---subject 表的 name 字段
     MYSQL_SYNTHESIZE(string, subjectName, SubjectName);
    // 报名类型---course 表的 lesson_type 字段
     MYSQL_SYNTHESIZE(int8_t, lessonType, LessonType);
};
// 给RegistrationViewDO智能指针设定一个别名方便使用
typedef std::shared_ptr<RegistrationViewDO> PtrRegistrationViewDO;

#endif // !_REGISTRATION_DO_H_
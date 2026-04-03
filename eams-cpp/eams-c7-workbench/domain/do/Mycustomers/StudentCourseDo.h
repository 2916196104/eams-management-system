#pragma once
#ifndef _STUDENT_COURSE_DO_
#define _STUDENT_COURSE_DO_

#include "../DoInclude.h"
#include "../lib-mysql/include/SqlHelper.h"
/**
 * student_course 表对应的数据库实体类
 */
class StudentCourseDO : public BaseDO
{
    // 主键ID
    MYSQL_SYNTHESIZE(long long, id, Id);
    // 学生ID
    MYSQL_SYNTHESIZE(long long, studentId, StudentId);
    // 课程ID
    MYSQL_SYNTHESIZE(long long, courseId, CourseId);
    // 科目ID
    MYSQL_SYNTHESIZE(long long, subjectId, SubjectId);
    // 开始时间
    MYSQL_SYNTHESIZE(std::string, startDate, StartDate);
    // 过期日期
    MYSQL_SYNTHESIZE(std::string, expireDate, ExpireDate);
    // 备注
    MYSQL_SYNTHESIZE(std::string, remark, Remark);
    // 购买总课次
    MYSQL_SYNTHESIZE(int, countLessonTotal, CountLessonTotal);
    // 已上课次
    MYSQL_SYNTHESIZE(int, countLessonComplete, CountLessonComplete);
    // 退款次数
    MYSQL_SYNTHESIZE(int, countLessonRefund, CountLessonRefund);
    // 套餐金额
    MYSQL_SYNTHESIZE(double, courseAmount, CourseAmount);
    // 优惠金额
    MYSQL_SYNTHESIZE(double, discountAmount, DiscountAmount);
    // 成交/合约金额
    MYSQL_SYNTHESIZE(double, amount, Amount);
    // 实付金额
    MYSQL_SYNTHESIZE(double, paidAmount, PaidAmount);
    // 是否付清 0否1是
    MYSQL_SYNTHESIZE(int, payOff, PayOff);
    // 经手人
    MYSQL_SYNTHESIZE(long long, operator_, Operator);
    // 创建人
    MYSQL_SYNTHESIZE(long long, creator, Creator);
    // 创建时间
    MYSQL_SYNTHESIZE(std::string, addTime, AddTime);
    // 编辑人
    MYSQL_SYNTHESIZE(long long, editor, Editor);
    // 编辑时间
    MYSQL_SYNTHESIZE(std::string, editTime, EditTime);
    // 逻辑删除
    MYSQL_SYNTHESIZE(bool, deleted, Deleted);
    // 审核状态
    MYSQL_SYNTHESIZE(int, verifyState, VerifyState);
    // 不足提醒次数
    MYSQL_SYNTHESIZE(int, warningTimes, WarningTimes);
    // 消课优先级
    MYSQL_SYNTHESIZE(int, priority, Priority);
    // 单价
    MYSQL_SYNTHESIZE(double, unitPrice, UnitPrice);
    // 是否来自体验
    MYSQL_SYNTHESIZE(int, fromTrial, FromTrial);
    // 组织ID
    MYSQL_SYNTHESIZE(long long, orgId, OrgId);

    MYSQL_SYNTHESIZE(string, courseName, CourseName); 

public:
    StudentCourseDO() : BaseDO("student_course")
    {
        // 主键
        MYSQL_ADD_FIELD_PK("id", "ll", id);

        MYSQL_ADD_FIELD("student_id", "ll", studentId);
        MYSQL_ADD_FIELD("course_id", "ll", courseId);
        MYSQL_ADD_FIELD("subject_id", "ll", subjectId);
        MYSQL_ADD_FIELD("start_date", "dt", startDate);
        MYSQL_ADD_FIELD("expire_date", "dt", expireDate);
        MYSQL_ADD_FIELD("remark", "s", remark);

        MYSQL_ADD_FIELD("count_lesson_total", "i", countLessonTotal);
        MYSQL_ADD_FIELD("count_lesson_complete", "i", countLessonComplete);
        MYSQL_ADD_FIELD("count_lesson_refund", "i", countLessonRefund);

        MYSQL_ADD_FIELD("course_amount", "lf", courseAmount);
        MYSQL_ADD_FIELD("discount_amount", "lf", discountAmount);
        MYSQL_ADD_FIELD("amount", "lf", amount);
        MYSQL_ADD_FIELD("paid_amount", "lf", paidAmount);

        MYSQL_ADD_FIELD("pay_off", "i", payOff);
        MYSQL_ADD_FIELD("operator", "ll", operator_);
        MYSQL_ADD_FIELD("creator", "ll", creator);
        MYSQL_ADD_FIELD("add_time", "dt", addTime);
        MYSQL_ADD_FIELD("editor", "ll", editor);
        MYSQL_ADD_FIELD("edit_time", "dt", editTime);
        MYSQL_ADD_FIELD("deleted", "b", deleted);
        MYSQL_ADD_FIELD("verify_state", "i", verifyState);
        MYSQL_ADD_FIELD("warning_times", "i", warningTimes);
        MYSQL_ADD_FIELD("priority", "i", priority);
        MYSQL_ADD_FIELD("unit_price", "lf", unitPrice);
        MYSQL_ADD_FIELD("from_trial", "i", fromTrial);
        MYSQL_ADD_FIELD("org_id", "ll", orgId);
        MYSQL_ADD_FIELD("course_name", "s", courseName);
    }
};

// 智能指针别名
typedef std::shared_ptr<StudentCourseDO> PtrStudentCourseDO;

#endif
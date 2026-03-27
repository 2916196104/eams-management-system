#pragma once
#ifndef _APPOINTMENT_DO_H_
#define _APPOINTMENT_DO_H_

#include "../DoInclude.h"

/**
 * @brief 预约记录表映射DO
 * 对应数据库表：appointment
 */
class AppointmentDO : public BaseDO {
        MYSQL_SYNTHESIZE(uint64_t, id, Id)                           // 主键
        MYSQL_SYNTHESIZE(uint64_t, lessonId, LessonId)               // 试听课次
        MYSQL_SYNTHESIZE(uint64_t, studentId, StudentId)             // 学员id
        MYSQL_SYNTHESIZE(string, addTime, AddTime)                   // 预约时间
        MYSQL_SYNTHESIZE(string, remark, Remark)                     // 备注
        MYSQL_SYNTHESIZE(int, verifyState, VerifyState)              // 审核状态
        MYSQL_SYNTHESIZE(string, verifyTime, VerifyTime)             // 审核时间
        MYSQL_SYNTHESIZE(uint64_t, verifyStaff, VerifyStaff)         // 审核人
        MYSQL_SYNTHESIZE(string, verifyRemark, VerifyRemark)         // 审核内容
        MYSQL_SYNTHESIZE(uint64_t, courseId, CourseId)               // 所属课程
        MYSQL_SYNTHESIZE(uint64_t, schoolId, SchoolId)               // 学校id
        MYSQL_SYNTHESIZE(uint64_t, counselor, Counselor)             // 学生的顾问
        MYSQL_SYNTHESIZE(uint64_t, trialId, TrialId)                 // 体验卡id
        MYSQL_SYNTHESIZE(uint64_t, trialRecordId, TrialRecordId)     // 消费体验卡领取记录id

public:
    // 构造函数：传入真实的数据库表名
    AppointmentDO() : BaseDO("appointment") {
        // 绑定主键
        MYSQL_ADD_FIELD_PK("id", "ull", id);

        // 绑定必须有值的字段
        MYSQL_ADD_FIELD("lesson_id", "ull", lessonId);
        MYSQL_ADD_FIELD("student_id", "ull", studentId);
        MYSQL_ADD_FIELD("course_id", "ull", courseId);
        MYSQL_ADD_FIELD("school_id", "ull", schoolId);

        // 绑定允许为空的字段 
   
        MYSQL_ADD_FIELD_NULLABLE("add_time", "dt", addTime, true);
        MYSQL_ADD_FIELD_NULLABLE("remark", "s", remark, true);
        MYSQL_ADD_FIELD_NULLABLE("verify_state", "i", verifyState, true);
        MYSQL_ADD_FIELD_NULLABLE("verify_time", "dt", verifyTime, true);
        MYSQL_ADD_FIELD_NULLABLE("verify_staff", "ull", verifyStaff, true);
        MYSQL_ADD_FIELD_NULLABLE("verify_remark", "s", verifyRemark, true);
        MYSQL_ADD_FIELD_NULLABLE("counselor", "ull", counselor, true);
        MYSQL_ADD_FIELD_NULLABLE("trial_id", "ull", trialId, true);
        MYSQL_ADD_FIELD_NULLABLE("trial_record_id", "ull", trialRecordId, true);
    }
};

// 定义一个智能指针别名方便Service层使用
typedef std::shared_ptr<AppointmentDO> PtrAppointmentDO;

#endif // !_APPOINTMENT_DO_H_
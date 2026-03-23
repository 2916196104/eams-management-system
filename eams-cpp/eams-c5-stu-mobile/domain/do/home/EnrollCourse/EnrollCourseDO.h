#pragma once


#ifndef _ENROLLCOURSE_DO_
#define _ENROLLCOURSE_DO_
#include "../../DoInclude.h"

class EnrollCourseDO : public BaseDO
{
    
    MYSQL_SYNTHESIZE(uint64_t, id, Id);

    
    MYSQL_SYNTHESIZE(uint64_t, studentId, StudentId);
    MYSQL_SYNTHESIZE(uint64_t, courseId, CourseId);
    MYSQL_SYNTHESIZE(uint64_t, subjectId, SubjectId);

   
    MYSQL_SYNTHESIZE(string, startDate, StartDate);
    MYSQL_SYNTHESIZE(string, expireDate, ExpireDate);
    MYSQL_SYNTHESIZE(string, remark, Remark);

    
    MYSQL_SYNTHESIZE(int, countLessonTotal, CountLessonTotal);
    MYSQL_SYNTHESIZE(int, countLessonComplete, CountLessonComplete);
    MYSQL_SYNTHESIZE(int, countLessonRefund, CountLessonRefund);

 
    MYSQL_SYNTHESIZE(float, courseAmount, CourseAmount);
    MYSQL_SYNTHESIZE(float, discountAmount, DiscountAmount);
    MYSQL_SYNTHESIZE(float, amount, Amount);
    MYSQL_SYNTHESIZE(float, paidAmount, PaidAmount);

    MYSQL_SYNTHESIZE(int, payOff, PayOff);
    MYSQL_SYNTHESIZE(uint64_t, operater, Operater);
    MYSQL_SYNTHESIZE(uint64_t, creator, Creator);
    MYSQL_SYNTHESIZE(string, addTime, AddTime);
    MYSQL_SYNTHESIZE(uint64_t, editor, Editor);
    MYSQL_SYNTHESIZE(string, editTime, EditTime);
    

    
    MYSQL_SYNTHESIZE(int, deleted, Deleted);
    MYSQL_SYNTHESIZE(int, verifyState, VerifyState);
    MYSQL_SYNTHESIZE(int, warningTimes, WarningTimes); 
    MYSQL_SYNTHESIZE(int, priority, Priority);
    MYSQL_SYNTHESIZE(float, unitPrice, UnitPrice);
    MYSQL_SYNTHESIZE(int, fromTrial, FromTrial);

  
    
    MYSQL_SYNTHESIZE(uint64_t, orgId, OrgId);


    MYSQL_SYNTHESIZE(string, coursename, CourseName);
    MYSQL_SYNTHESIZE(string, subjectname, SubjectName);


public:
    EnrollCourseDO() : BaseDO("student_course")
    {
        
        MYSQL_ADD_FIELD_PK("id", "ull", id);

       
        MYSQL_ADD_FIELD("student_id", "ull", studentId);
        MYSQL_ADD_FIELD("course_id", "ull", courseId);
        MYSQL_ADD_FIELD("subject_id", "ull", subjectId);

        MYSQL_ADD_FIELD("start_date", "s", startDate);
        MYSQL_ADD_FIELD("expire_date", "s", expireDate);
        MYSQL_ADD_FIELD("remark", "s", remark);

        MYSQL_ADD_FIELD("count_lesson_total", "i", countLessonTotal);
        MYSQL_ADD_FIELD("count_lesson_complete", "i", countLessonComplete);
        MYSQL_ADD_FIELD("count_lesson_refund", "i", countLessonRefund);

       
        MYSQL_ADD_FIELD("course_amount", "f", courseAmount);
        MYSQL_ADD_FIELD("discount_amount", "f", discountAmount);
        MYSQL_ADD_FIELD("amount", "f", amount);
        MYSQL_ADD_FIELD("paid_amount", "f", paidAmount);
        MYSQL_ADD_FIELD("unit_price", "f", unitPrice);

        MYSQL_ADD_FIELD("pay_off", "i", payOff);
        MYSQL_ADD_FIELD("deleted", "i", deleted);
        MYSQL_ADD_FIELD("verify_state", "i", verifyState);
        MYSQL_ADD_FIELD("warning_times", "i", warningTimes);
        MYSQL_ADD_FIELD("priority", "i", priority);
        MYSQL_ADD_FIELD("from_trial", "i", fromTrial);

        MYSQL_ADD_FIELD("operater", "ull", operater);
        MYSQL_ADD_FIELD("creator", "ull", creator);
        MYSQL_ADD_FIELD("add_time", "s", addTime);
        MYSQL_ADD_FIELD("editor", "ull", editor);
        MYSQL_ADD_FIELD("edit_time", "s", editTime);
        MYSQL_ADD_FIELD("org_id", "ull", orgId);

        MYSQL_ADD_FIELD("course_name", "s", coursename);
        MYSQL_ADD_FIELD("subject_name", "s", subjectname);
    }


};





typedef std::shared_ptr<EnrollCourseDO> PtrEnrollCourseDO;
#endif
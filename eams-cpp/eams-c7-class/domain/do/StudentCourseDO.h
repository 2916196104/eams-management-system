#pragma once
#ifndef _STUDENT_COURSE_DO_H_
#define _STUDENT_COURSE_DO_H_

#include "../GlobalInclude.h"
#include "BaseDO.h"
#include <string>

using oatpp::UInt64;
using oatpp::Int32;
using oatpp::String;
using oatpp::Boolean;

/**
 * 报名签约表领域对象（简易版，仅用于编译）
 * TODO: 等正式版完成后替换
 */
class StudentCourseDO : public BaseDO {
public:
    StudentCourseDO() : BaseDO("student_course") {
        addColField(new DOField("id", "ll", std::bind(&StudentCourseDO::getIdPtr, this), false, true));
        addColField(new DOField("student_id", "ll", std::bind(&StudentCourseDO::getStudentIdPtr, this), false, false));
        addColField(new DOField("course_id", "ll", std::bind(&StudentCourseDO::getCourseIdPtr, this), false, false));
        addColField(new DOField("subject_id", "ll", std::bind(&StudentCourseDO::getSubjectIdPtr, this), true, false));
        addColField(new DOField("start_date", "s", std::bind(&StudentCourseDO::getStartDatePtr, this), true, false));
        addColField(new DOField("expire_date", "s", std::bind(&StudentCourseDO::getExpireDatePtr, this), true, false));
        addColField(new DOField("remark", "s", std::bind(&StudentCourseDO::getRemarkPtr, this), true, false));
        addColField(new DOField("count_lesson_total", "i", std::bind(&StudentCourseDO::getCountLessonTotalPtr, this), false, false));
        addColField(new DOField("count_lesson_complete", "i", std::bind(&StudentCourseDO::getCountLessonCompletePtr, this), false, false));
        addColField(new DOField("count_lesson_refund", "i", std::bind(&StudentCourseDO::getCountLessonRefundPtr, this), false, false));
        addColField(new DOField("add_time", "s", std::bind(&StudentCourseDO::getAddTimePtr, this), true, false));
        addColField(new DOField("priority", "i", std::bind(&StudentCourseDO::getPriorityPtr, this), true, false));
        addColField(new DOField("deleted", "i", std::bind(&StudentCourseDO::getDeletedPtr, this), false, false));
        // 扩展字段
        addColField(new DOField("course_name", "s", std::bind(&StudentCourseDO::getCourseNamePtr, this), true, false));
        addColField(new DOField("subject_name", "s", std::bind(&StudentCourseDO::getSubjectNamePtr, this), true, false));
        addColField(new DOField("student_name", "s", std::bind(&StudentCourseDO::getStudentNamePtr, this), true, false));
    }

    // ==================== 字段定义 ====================
    UInt64 id = 1;
    UInt64 studentId = 1;
    UInt64 courseId = 1;
    UInt64 subjectId = 1;
    String startDate;
    String expireDate;
    String remark;
    Int32 countLessonTotal = 0;
    Int32 countLessonComplete = 0;
    Int32 countLessonRefund = 0;
    String addTime;
    Int32 priority = 0;
    Boolean deleted = false;

    // 扩展字段
    String courseName;
    String subjectName;
    String studentName;

    // ==================== Getter 指针方法 ====================
    void* getIdPtr() { return &id; }
    void* getStudentIdPtr() { return &studentId; }
    void* getCourseIdPtr() { return &courseId; }
    void* getSubjectIdPtr() { return &subjectId; }
    void* getStartDatePtr() { return &startDate; }
    void* getExpireDatePtr() { return &expireDate; }
    void* getRemarkPtr() { return &remark; }
    void* getCountLessonTotalPtr() { return &countLessonTotal; }
    void* getCountLessonCompletePtr() { return &countLessonComplete; }
    void* getCountLessonRefundPtr() { return &countLessonRefund; }
    void* getAddTimePtr() { return &addTime; }
    void* getPriorityPtr() { return &priority; }
    void* getDeletedPtr() { return &deleted; }
    void* getCourseNamePtr() { return &courseName; }
    void* getSubjectNamePtr() { return &subjectName; }
    void* getStudentNamePtr() { return &studentName; }

    // ==================== Getter/Setter ====================
    void setId(UInt64 val) { id = val; }
    UInt64 getId() const { return id; }

    void setStudentId(UInt64 val) { studentId = val; }
    UInt64 getStudentId() const { return studentId; }

    void setCourseId(UInt64 val) { courseId = val; }
    UInt64 getCourseId() const { return courseId; }

    void setSubjectId(UInt64 val) { subjectId = val; }
    UInt64 getSubjectId() const { return subjectId; }

    void setStartDate(const String& val) { startDate = val; }
    String getStartDate() const { return startDate; }

    void setExpireDate(const String& val) { expireDate = val; }
    String getExpireDate() const { return expireDate; }

    void setRemark(const String& val) { remark = val; }
    String getRemark() const { return remark; }

    void setCountLessonTotal(Int32 val) { countLessonTotal = val; }
    Int32 getCountLessonTotal() const { return countLessonTotal; }

    void setCountLessonComplete(Int32 val) { countLessonComplete = val; }
    Int32 getCountLessonComplete() const { return countLessonComplete; }

    void setCountLessonRefund(Int32 val) { countLessonRefund = val; }
    Int32 getCountLessonRefund() const { return countLessonRefund; }

    void setAddTime(const String& val) { addTime = val; }
    String getAddTime() const { return addTime; }

    void setPriority(Int32 val) { priority = val; }
    Int32 getPriority() const { return priority; }

    void setDeleted(Boolean val) { deleted = val; }
    Boolean getDeleted() const { return deleted; }

    void setCourseName(const String& val) { courseName = val; }
    String getCourseName() const { return courseName; }

    void setSubjectName(const String& val) { subjectName = val; }
    String getSubjectName() const { return subjectName; }

    void setStudentName(const String& val) { studentName = val; }
    String getStudentName() const { return studentName; }

    // ==================== 便捷方法 ====================
    Int32 getRemainingLessonCount() const {
        return countLessonTotal - countLessonComplete - countLessonRefund;
    }

    String getProgressText() const {
        return String(std::to_string(countLessonComplete) + "/" + std::to_string(countLessonTotal));
    }

    String getRemainingText() const {
        return String("剩余：" + std::to_string(getRemainingLessonCount()) + "次");
    }

    String getExpireText() const {
        return String("有效期" + expireDate);
    }
};

// 智能指针类型定义
using PtrStudentCourseDO = std::shared_ptr<StudentCourseDO>;

#endif // !_STUDENT_COURSE_DO_H_
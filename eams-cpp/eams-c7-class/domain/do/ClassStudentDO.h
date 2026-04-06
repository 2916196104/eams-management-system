#pragma once

#ifndef _CLASS_STUDENT_DO_H_
#define _CLASS_STUDENT_DO_H_

#include "../GlobalInclude.h"
#include "BaseDO.h"
#include <string>

using oatpp::UInt64;
using oatpp::Int32;
using oatpp::String;
using oatpp::Boolean;

/**
 * 班级学员关联表领域对象
 * 对应表名: class_student
 */
class ClassStudentDO : public BaseDO {
public:
    // 构造函数，传入表名
    ClassStudentDO() : BaseDO("class_student") {
        // 注册字段（顺序：字段名，类型占位符，getter，是否可为空，是否主键）
        addColField(new DOField("id", "ll", std::bind(&ClassStudentDO::getIdPtr, this), false, true));
        addColField(new DOField("class_id", "ll", std::bind(&ClassStudentDO::getClassIdPtr, this), false, false));
        addColField(new DOField("student_id", "ll", std::bind(&ClassStudentDO::getStudentIdPtr, this), false, false));
        addColField(new DOField("add_time", "s", std::bind(&ClassStudentDO::getAddTimePtr, this), true, false));
        addColField(new DOField("creator", "ll", std::bind(&ClassStudentDO::getCreatorPtr, this), true, false));
        addColField(new DOField("reason", "i", std::bind(&ClassStudentDO::getReasonPtr, this), true, false));
        addColField(new DOField("deleted", "i", std::bind(&ClassStudentDO::getDeletedPtr, this), false, false));
        addColField(new DOField("remark", "s", std::bind(&ClassStudentDO::getRemarkPtr, this), true, false));
        addColField(new DOField("consume_course_id", "ll", std::bind(&ClassStudentDO::getConsumeCourseIdPtr, this), false, false));
    }

    // ==================== 字段定义 ====================
    UInt64 id = UInt64(1);
    UInt64 classId = UInt64(1);
    UInt64 studentId = UInt64(1);
    String addTime;
    UInt64 creator = UInt64(1);
    Int32 reason = 0;
    Boolean deleted = false;
    String remark;
    UInt64 consumeCourseId = UInt64(1);

    // ==================== Getter 指针方法（供 DOField 使用） ====================
    void* getIdPtr() { return &id; }
    void* getClassIdPtr() { return &classId; }
    void* getStudentIdPtr() { return &studentId; }
    void* getAddTimePtr() { return &addTime; }
    void* getCreatorPtr() { return &creator; }
    void* getReasonPtr() { return &reason; }
    void* getDeletedPtr() { return &deleted; }
    void* getRemarkPtr() { return &remark; }
    void* getConsumeCourseIdPtr() { return &consumeCourseId; }

    // ==================== Getter/Setter ====================
    void setId(UInt64 val) { id = val; }
    UInt64 getId() const { return id; }

    void setClassId(UInt64 val) { classId = val; }
    UInt64 getClassId() const { return classId; }

    void setStudentId(UInt64 val) { studentId = val; }
    UInt64 getStudentId() const { return studentId; }

    void setAddTime(const String& val) { addTime = val; }
    String getAddTime() const { return addTime; }

    void setCreator(UInt64 val) { creator = val; }
    UInt64 getCreator() const { return creator; }

    void setReason(Int32 val) { reason = val; }
    Int32 getReason() const { return reason; }

    void setDeleted(Boolean val) { deleted = val; }
    Boolean getDeleted() const { return deleted; }

    void setRemark(const String& val) { remark = val; }
    String getRemark() const { return remark; }

    void setConsumeCourseId(UInt64 val) { consumeCourseId = val; }
    UInt64 getConsumeCourseId() const { return consumeCourseId; }

    // ==================== 领域行为方法 ====================
    bool isActive() const { return !deleted; }

    String getReasonText() const {
        switch (reason) {
        case 1: return "报名加入";
        case 2: return "转班加入";
        case 3: return "试听转入";
        default: return "未知";
        }
    }

    bool hasConsumeCourse() const { return consumeCourseId > 0; }
    void markDeleted() { deleted = true; }
};

// 智能指针类型定义
using PtrClassStudentDO = std::shared_ptr<ClassStudentDO>;

#endif // !_CLASS_STUDENT_DO_H_
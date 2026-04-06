#pragma once
#ifndef _STUDENT_DO_H_
#define _STUDENT_DO_H_

#include "../GlobalInclude.h"
#include "BaseDO.h"
#include <string>

using oatpp::UInt64;
using oatpp::Int32;
using oatpp::String;
using oatpp::Boolean;

/**
 * 学生表领域对象（简易版，仅用于编译）
 * TODO: 等正式版完成后替换
 */
class StudentDO : public BaseDO {
public:
    // 构造函数，传入表名
    StudentDO() : BaseDO("student") {
        // 注册字段（顺序：字段名，类型占位符，getter，是否可为空，是否主键）
        addColField(new DOField("id", "ll", std::bind(&StudentDO::getIdPtr, this), false, true));
        addColField(new DOField("name", "s", std::bind(&StudentDO::getNamePtr, this), false, false));
        addColField(new DOField("gender", "i", std::bind(&StudentDO::getGenderPtr, this), true, false));
        addColField(new DOField("birthday", "s", std::bind(&StudentDO::getBirthdayPtr, this), true, false));
        addColField(new DOField("head_img", "s", std::bind(&StudentDO::getHeadImgPtr, this), true, false));
        addColField(new DOField("stage", "i", std::bind(&StudentDO::getStagePtr, this), true, false));
        addColField(new DOField("remark", "s", std::bind(&StudentDO::getRemarkPtr, this), true, false));
        addColField(new DOField("join_date", "s", std::bind(&StudentDO::getJoinDatePtr, this), true, false));
        addColField(new DOField("add_time", "s", std::bind(&StudentDO::getAddTimePtr, this), true, false));
        addColField(new DOField("counselor", "ll", std::bind(&StudentDO::getCounselorPtr, this), true, false));
        addColField(new DOField("grade_id", "i", std::bind(&StudentDO::getGradeIdPtr, this), true, false));
        addColField(new DOField("credit", "i", std::bind(&StudentDO::getCreditPtr, this), true, false));
        addColField(new DOField("deleted", "i", std::bind(&StudentDO::getDeletedPtr, this), false, false));
        // 扩展字段（不映射数据库，仅用于关联查询结果）
        addColField(new DOField("class_student_id", "ll", std::bind(&StudentDO::getClassStudentIdPtr, this), true, false));
        addColField(new DOField("consume_course_id", "ll", std::bind(&StudentDO::getConsumeCourseIdPtr, this), true, false));
        addColField(new DOField("mobile", "s", std::bind(&StudentDO::getMobilePtr, this), true, false));
        addColField(new DOField("counselor_name", "s", std::bind(&StudentDO::getCounselorNamePtr, this), true, false));
    }

    // ==================== 字段定义 ====================
    UInt64 id = 1;
    String name;
    Int32 gender = 0;
    String birthday;
    String headImg;
    Int32 stage = 0;
    String remark;
    String joinDate;
    String addTime;
    UInt64 counselor = 1;
    Int32 gradeId = 0;
    Int32 credit = 0;
    Boolean deleted = false;

    // 扩展字段
    UInt64 classStudentId = 1;
    UInt64 consumeCourseId = 1;
    String mobile;
    String counselorName;

    // ==================== Getter 指针方法（供 DOField 使用） ====================
    void* getIdPtr() { return &id; }
    void* getNamePtr() { return &name; }
    void* getGenderPtr() { return &gender; }
    void* getBirthdayPtr() { return &birthday; }
    void* getHeadImgPtr() { return &headImg; }
    void* getStagePtr() { return &stage; }
    void* getRemarkPtr() { return &remark; }
    void* getJoinDatePtr() { return &joinDate; }
    void* getAddTimePtr() { return &addTime; }
    void* getCounselorPtr() { return &counselor; }
    void* getGradeIdPtr() { return &gradeId; }
    void* getCreditPtr() { return &credit; }
    void* getDeletedPtr() { return &deleted; }
    void* getClassStudentIdPtr() { return &classStudentId; }
    void* getConsumeCourseIdPtr() { return &consumeCourseId; }
    void* getMobilePtr() { return &mobile; }
    void* getCounselorNamePtr() { return &counselorName; }

    // ==================== Getter/Setter ====================
    void setId(UInt64 val) { id = val; }
    UInt64 getId() const { return id; }

    void setName(const String& val) { name = val; }
    String getName() const { return name; }

    void setGender(Int32 val) { gender = val; }
    Int32 getGender() const { return gender; }

    void setBirthday(const String& val) { birthday = val; }
    String getBirthday() const { return birthday; }

    void setHeadImg(const String& val) { headImg = val; }
    String getHeadImg() const { return headImg; }

    void setStage(Int32 val) { stage = val; }
    Int32 getStage() const { return stage; }

    void setRemark(const String& val) { remark = val; }
    String getRemark() const { return remark; }

    void setJoinDate(const String& val) { joinDate = val; }
    String getJoinDate() const { return joinDate; }

    void setAddTime(const String& val) { addTime = val; }
    String getAddTime() const { return addTime; }

    void setCounselor(UInt64 val) { counselor = val; }
    UInt64 getCounselor() const { return counselor; }

    void setGradeId(Int32 val) { gradeId = val; }
    Int32 getGradeId() const { return gradeId; }

    void setCredit(Int32 val) { credit = val; }
    Int32 getCredit() const { return credit; }

    void setDeleted(Boolean val) { deleted = val; }
    Boolean getDeleted() const { return deleted; }

    void setClassStudentId(UInt64 val) { classStudentId = val; }
    UInt64 getClassStudentId() const { return classStudentId; }

    void setConsumeCourseId(UInt64 val) { consumeCourseId = val; }
    UInt64 getConsumeCourseId() const { return consumeCourseId; }

    void setMobile(const String& val) { mobile = val; }
    String getMobile() const { return mobile; }

    void setCounselorName(const String& val) { counselorName = val; }
    String getCounselorName() const { return counselorName; }
};

// 智能指针类型定义
using PtrStudentDO = std::shared_ptr<StudentDO>;

#endif // !_STUDENT_DO_H_
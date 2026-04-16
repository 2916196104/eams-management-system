#pragma once
#ifndef _COURSE_DO_H_
#define _COURSE_DO_H_

#include "../GlobalInclude.h"
#include "BaseDO.h"
#include <string>

using oatpp::UInt64;
using oatpp::Int32;
using oatpp::String;
using oatpp::Boolean;
using oatpp::Float64;

/**
 * 课程套餐表领域对象
 * 对应表名: course
 */
class CourseDO : public BaseDO {
public:
    CourseDO() : BaseDO("course") {
        addColField(new DOField("id", "ll", std::bind(&CourseDO::getIdPtr, this), false, true));
        addColField(new DOField("name", "s", std::bind(&CourseDO::getNamePtr, this), false, false));
        addColField(new DOField("subject_id", "ll", std::bind(&CourseDO::getSubjectIdPtr, this), true, false));
        addColField(new DOField("lesson_count", "i", std::bind(&CourseDO::getLessonCountPtr, this), true, false));
        addColField(new DOField("price", "d", std::bind(&CourseDO::getPricePtr, this), true, false));
        addColField(new DOField("deleted", "i", std::bind(&CourseDO::getDeletedPtr, this), false, false));
    }

    // 字段定义
    UInt64 id;
    String name;
    UInt64 subjectId;
    Int32 lessonCount = 0;
    Float64 price = 0.0;
    Boolean deleted = false;

    // Getter 指针方法
    void* getIdPtr() { return &id; }
    void* getNamePtr() { return &name; }
    void* getSubjectIdPtr() { return &subjectId; }
    void* getLessonCountPtr() { return &lessonCount; }
    void* getPricePtr() { return &price; }
    void* getDeletedPtr() { return &deleted; }

    // Getter/Setter
    void setId(UInt64 val) { id = val; }
    UInt64 getId() const { return id; }

    void setName(const String& val) { name = val; }
    String getName() const { return name; }

    void setSubjectId(UInt64 val) { subjectId = val; }
    UInt64 getSubjectId() const { return subjectId; }

    void setLessonCount(Int32 val) { lessonCount = val; }
    Int32 getLessonCount() const { return lessonCount; }

    void setPrice(Float64 val) { price = val; }
    Float64 getPrice() const { return price; }

    void setDeleted(Boolean val) { deleted = val; }
    Boolean getDeleted() const { return deleted; }

    // 领域行为
    bool isValid() const { return !deleted; }
    void markDeleted() { deleted = true; }
};

// 智能指针类型定义
using PtrCourseDO = std::shared_ptr<CourseDO>;

#endif // !_COURSE_DO_H_
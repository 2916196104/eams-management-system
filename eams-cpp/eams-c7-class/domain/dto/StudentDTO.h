#pragma once

#ifndef _STUDENT_DTO_H_
#define _STUDENT_DTO_H_

#include "../GlobalInclude.h"
#include "domain/dto/PageDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 班级学员列表项DTO
 * 对应接口: 获取班级学员列表（分页）
 * 只显示: 学员姓名、剩余课程量
 */
class ClassStudentItemDTO : public oatpp::DTO {
    DTO_INIT(ClassStudentItemDTO, DTO);

    // 学员ID (用于跳转详情)
    DTO_FIELD(UInt64, id);
    DTO_FIELD_INFO(id) {
        info->description = ZH_WORDS_GETTER("class.field.id");
    }

    // 学员姓名
    DTO_FIELD(String, name);
    DTO_FIELD_INFO(name) {
        info->description = ZH_WORDS_GETTER("class.field.studentName");
    }

    // 性别 (0未知, 1男, 2女)
    DTO_FIELD(String, gender);
    DTO_FIELD_INFO(gender) {
        info->description = ZH_WORDS_GETTER("class.field.gender");
    }

    // 剩余课时数
    DTO_FIELD(Int32, remainingLessonCount);
    DTO_FIELD_INFO(remainingLessonCount) {
        info->description = ZH_WORDS_GETTER("class.field.remainingCount");
    }
};

/**
 * 班级学员详情DTO
 * 对应接口: 获取班级学员详情
 * 只显示: 姓名、手机号码、性别、生日、年龄、类型、备注
 */
class StudentDetailDTO : public oatpp::DTO {
    DTO_INIT(StudentDetailDTO, DTO);

    // 学员ID
    DTO_FIELD(UInt64, id);
    DTO_FIELD_INFO(id) {
        info->description = ZH_WORDS_GETTER("class.field.id");
    }

    // 姓名
    DTO_FIELD(String, name);
    DTO_FIELD_INFO(name) {
        info->description = ZH_WORDS_GETTER("class.field.studentName");
    }

    // 手机号码
    DTO_FIELD(String, mobile);
    DTO_FIELD_INFO(mobile) {
        info->description = ZH_WORDS_GETTER("class.field.mobile");
    }

    // 性别
    DTO_FIELD(String, gender);
    DTO_FIELD_INFO(gender) {
        info->description = ZH_WORDS_GETTER("class.field.gender");
    }

    // 年龄
    DTO_FIELD(Int32, age);
    DTO_FIELD_INFO(age) {
        info->description = ZH_WORDS_GETTER("class.field.age");
    }

    // 生日
    DTO_FIELD(String, birthday);
    DTO_FIELD_INFO(birthday) {
        info->description = ZH_WORDS_GETTER("class.field.birthday");
    }

    // 学员类型
    DTO_FIELD(String, stage);
    DTO_FIELD_INFO(stage) {
        info->description = ZH_WORDS_GETTER("class.field.stage");
    }

    // 备注
    DTO_FIELD(String, remark);
    DTO_FIELD_INFO(remark) {
        info->description = ZH_WORDS_GETTER("class.field.remark");
    }
};

/**
 * 学员课程列表项DTO
 * 对应接口: 获取班级学员课程列表（分页）
 * 只显示: 课程名称、学习进度、剩余次数、有效期
 */
class StudentCourseItemDTO : public oatpp::DTO {
    DTO_INIT(StudentCourseItemDTO, DTO);

    // 报名记录ID
    DTO_FIELD(UInt64, id);
    DTO_FIELD_INFO(id) {
        info->description = ZH_WORDS_GETTER("class.field.recordId");
    }

    // 课程名称
    DTO_FIELD(String, courseName);
    DTO_FIELD_INFO(courseName) {
        info->description = ZH_WORDS_GETTER("class.field.courseName");
    }

    // 已上课次
    DTO_FIELD(Int32, countLessonComplete);
    DTO_FIELD_INFO(countLessonComplete) {
        info->description = ZH_WORDS_GETTER("class.field.completedCount");
    }

    // 总课次
    DTO_FIELD(Int32, countLessonTotal);
    DTO_FIELD_INFO(countLessonTotal) {
        info->description = ZH_WORDS_GETTER("class.field.totalCount");
    }

    // 剩余课次
    DTO_FIELD(Int32, countLessonRemaining);
    DTO_FIELD_INFO(countLessonRemaining) {
        info->description = ZH_WORDS_GETTER("class.field.remainingCount");
    }

    // 过期日期
    DTO_FIELD(String, expireDate);
    DTO_FIELD_INFO(expireDate) {
        info->description = ZH_WORDS_GETTER("class.field.expireDate");
    }

    // 学习进度文本 - 方便前端直接显示 "0/5"、"8/50"
    DTO_FIELD(String, progressText);
    DTO_FIELD_INFO(progressText) {
        info->description = ZH_WORDS_GETTER("class.field.progressText");
    }

    // 剩余次数文本 - 方便前端直接显示 "剩余：5次"
    DTO_FIELD(String, remainingText);
    DTO_FIELD_INFO(remainingText) {
        info->description = ZH_WORDS_GETTER("class.field.remainingText");
    }

    // 有效期文本 - 方便前端直接显示 "有效期2026-01-27"
    DTO_FIELD(String, expireText);
    DTO_FIELD_INFO(expireText) {
        info->description = ZH_WORDS_GETTER("class.field.expireText");
    }
};

/**
 * 班级学员列表分页DTO
 */
class ClassStudentPageDTO : public PageDTO<ClassStudentItemDTO::Wrapper> {
    DTO_INIT(ClassStudentPageDTO, PageDTO<ClassStudentItemDTO::Wrapper>);
};

/**
 * 学员课程列表分页DTO
 */
class StudentCoursePageDTO : public PageDTO<StudentCourseItemDTO::Wrapper> {
    DTO_INIT(StudentCoursePageDTO, PageDTO<StudentCourseItemDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_STUDENT_DTO_H_
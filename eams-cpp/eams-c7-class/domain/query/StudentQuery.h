#pragma once

#ifndef _STUDENT_QUERY_H_
#define _STUDENT_QUERY_H_

#include "../GlobalInclude.h"
#include "../lib-oatpp/include/domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 班级学员列表查询对象
 * 对应接口: 获取班级学员列表（分页）
 * 只保留必要的查询参数
 */
class ClassStudentListQuery : public PageQuery {
    DTO_INIT(ClassStudentListQuery, PageQuery);

    // 班级ID (必传)
    API_DTO_FIELD_REQUIRE(UInt64, classId, ZH_WORDS_GETTER("stu.field.classId"), true);

    // 学员姓名 (模糊查询)
    API_DTO_FIELD_DEFAULT(String, studentName, ZH_WORDS_GETTER("stu.field.studentName"));

    // 手机号 (模糊查询)
    API_DTO_FIELD_DEFAULT(String, mobile, ZH_WORDS_GETTER("stu.field.mobile"));

    // 学员阶段状态 (0意向学员, 1正式学员等)
    API_DTO_FIELD_DEFAULT(Int32, stage, ZH_WORDS_GETTER("stu.field.stage"));
};

/**
 * 学员课程列表查询对象
 * 对应接口: 获取班级学员课程列表（分页）
 * 只保留必要的查询参数
 */
class StudentCourseListQuery : public PageQuery {
    DTO_INIT(StudentCourseListQuery, PageQuery);

    // 学员ID (必传)
    API_DTO_FIELD_REQUIRE(UInt64, studentId, ZH_WORDS_GETTER("stu.field.studentId"), true);

    // 课程名称 (模糊查询)
    API_DTO_FIELD_DEFAULT(String, courseName, ZH_WORDS_GETTER("stu.field.courseName"));
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_StudentQuery_H_
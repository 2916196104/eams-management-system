#pragma once

#ifndef _STUDENT_VO_H_
#define _STUDENT_VO_H_

#include "../GlobalInclude.h"
#include "../dto/StudentDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 班级学员列表JsonVO
 */
class ClassStudentPageJsonVO : public JsonVO<ClassStudentPageDTO::Wrapper> {
    DTO_INIT(ClassStudentPageJsonVO, JsonVO<ClassStudentPageDTO::Wrapper>);
};

/**
 * 班级学员详情JsonVO
 */
class StudentDetailJsonVO : public JsonVO<StudentDetailDTO::Wrapper> {
    DTO_INIT(StudentDetailJsonVO, JsonVO<StudentDetailDTO::Wrapper>);
};

/**
 * 学员课程列表JsonVO
 */
class StudentCoursePageJsonVO : public JsonVO<StudentCoursePageDTO::Wrapper> {
    DTO_INIT(StudentCoursePageJsonVO, JsonVO<StudentCoursePageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_StudentVO_H_
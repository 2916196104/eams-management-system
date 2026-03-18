#pragma once
#ifndef _CLASS_STUDENT_VO_H_
#define _CLASS_STUDENT_VO_H_

#include "../../GlobalInclude.h"
#include "../../dto/class/ClassStudentDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class ClassStudentJsonVO : public JsonVO<ClassStudentDTO::Wrapper>
{
	DTO_INIT(ClassStudentJsonVO, JsonVO<ClassStudentDTO::Wrapper>);
};

class ClassStudentDetailJsonVO : public JsonVO<ClassStudentDetailDTO::Wrapper>
{
	DTO_INIT(ClassStudentDetailJsonVO, JsonVO<ClassStudentDetailDTO::Wrapper>);
};

class ClassStudentPageJsonVO : public JsonVO<ClassStudentPageDTO::Wrapper>
{
	DTO_INIT(ClassStudentPageJsonVO, JsonVO<ClassStudentPageDTO::Wrapper>);
};

class ClassStudentCoursePageJsonVO : public JsonVO<ClassStudentCoursePageDTO::Wrapper>
{
	DTO_INIT(ClassStudentCoursePageJsonVO, JsonVO<ClassStudentCoursePageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif

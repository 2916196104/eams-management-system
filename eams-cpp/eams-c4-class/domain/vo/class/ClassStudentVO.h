#pragma once
#ifndef _CLASS_STUDENT_VO_H_
#define _CLASS_STUDENT_VO_H_

#include "../../GlobalInclude.h"
#include "../../dto/class/ClassStudentDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class ClassStudentListJsonVO : public JsonVO<ClassStudentListDTO::Wrapper>
{
	DTO_INIT(ClassStudentListJsonVO, JsonVO<ClassStudentListDTO::Wrapper>);
};

class ClassStudentDetailJsonVO : public JsonVO<ClassStudentDetailDTO::Wrapper>
{
	DTO_INIT(ClassStudentDetailJsonVO, JsonVO<ClassStudentDetailDTO::Wrapper>);
};

class ClassStudentListPageJsonVO : public JsonVO<ClassStudentListPageDTO::Wrapper>
{
	DTO_INIT(ClassStudentListPageJsonVO, JsonVO<ClassStudentListPageDTO::Wrapper>);
};

class ClassStudentCoursePageJsonVO : public JsonVO<ClassStudentCoursePageDTO::Wrapper>
{
	DTO_INIT(ClassStudentCoursePageJsonVO, JsonVO<ClassStudentCoursePageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif

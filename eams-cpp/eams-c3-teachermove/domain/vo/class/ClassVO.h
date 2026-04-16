#ifndef __CLASS_VO_H__
#define __CLASS_VO_H__


#include"domain/dto/class/ClassDTO.h"
#include "domain/GlobalInclude.h"

#include"domain/dto/class/ClassDetailDTO.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/* 班级视图对象 */
class ClassVO : public JsonVO<ClassDTO::Wrapper>
{
	DTO_INIT(ClassVO, JsonVO<ClassDTO::Wrapper>);
};

class ClassPageJsonVO : public JsonVO<ClassPageDTO::Wrapper> {
	DTO_INIT(ClassPageJsonVO, JsonVO<ClassPageDTO::Wrapper>);
};

class CoursePageJsonVO : public JsonVO<CoursePageDTO::Wrapper> {
	DTO_INIT(CoursePageJsonVO, JsonVO<CoursePageDTO::Wrapper>);
};

class ClassDetailJsonVO : public JsonVO<ClassDetailDTO::Wrapper> {
	DTO_INIT(ClassDetailJsonVO, JsonVO<ClassDetailDTO::Wrapper>);
};
class ClassDetailPageJsonVO : public JsonVO<ClassDetailPageDTO::Wrapper> {
	DTO_INIT(ClassDetailPageJsonVO, JsonVO<ClassDetailPageDTO::Wrapper>);
};

// 学员详情JsonVO
class StudentDetailJsonVO : public JsonVO<oatpp::Object<StudentDetailDTO>> {
	DTO_INIT(StudentDetailJsonVO, JsonVO<oatpp::Object<StudentDetailDTO>>);
};

#include OATPP_CODEGEN_END(DTO)

#endif
#pragma once


#ifndef _EnrollCourses_VO_
#define _EnrollCourses_VO_

#include "../../../GlobalInclude.h"
#include "../../../dto/home/EnrollCourse/EnrollCourseDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)


class EnrollCourseJsonVO : public JsonVO<EnrollCourseDTO::Wrapper> {
	DTO_INIT(EnrollCourseJsonVO, JsonVO<EnrollCourseDTO::Wrapper>)
};


class EnrollCoursePageJsonVO : public JsonVO<EnrollCoursePageDTO::Wrapper> {
	DTO_INIT(EnrollCoursePageJsonVO, JsonVO<EnrollCoursePageDTO::Wrapper>)
};


#include OATPP_CODEGEN_END(DTO)
#endif
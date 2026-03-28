#pragma once
#ifndef _COURSEVO_H_
#define _COURSEVO_H_

#include "../../GlobalInclude.h"
#include "../../../../lib-oatpp/include/domain/vo/BaseJsonVO.h"
#include "../../dto/Course/CourseDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

// 分页显示对象
class CoursePageJsonVO : public JsonVO<CoursePageDTO::Wrapper>
{
	DTO_INIT(CoursePageJsonVO, JsonVO<CoursePageDTO::Wrapper>);
};

// 课程列表显示对象（不分页）
class CourseListJsonVO : public ListJsonVO<CourseDTO::Wrapper>
{
	DTO_INIT(CourseListJsonVO, ListJsonVO<CourseDTO::Wrapper>);
};

// 单个课程详情VO
class CourseDetailJsonVO : public JsonVO<CourseDTO::Wrapper>
{
	DTO_INIT(CourseDetailJsonVO, JsonVO<CourseDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif
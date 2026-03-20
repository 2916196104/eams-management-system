#pragma once
#pragma once
#pragma once
#ifndef _COURSEVO_H_
#define _COURSEVO_H_
#include "../../GlobalInclude.h"
#include "../../../../lib-oatpp/include/domain/vo/BaseJsonVO.h"
#include "../../dto/course/CourseDTO.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 分页显示对象
 */
class CoursePageJsonVO : public JsonVO<CoursePageDTO::Wrapper>
{
	DTO_INIT(CoursePageJsonVO, JsonVO<CoursePageDTO::Wrapper>);
};
/*
* 课程列表显示对象
*/
class CourseListJsonVO : public ListJsonVO<CourseDTO::Wrapper>
{
	DTO_INIT(CourseListJsonVO, ListJsonVO<CourseDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_SAMPLE_DTO_


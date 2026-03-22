#pragma once
#ifndef _COURSEEVALUATE_VO_H_
#define _COURSEEVALUATE_VO_H_

#include "../../GlobalInclude.h"
#include "../../dto/CourseEvaluate/CourseEvaluateDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 课程评价显示JsonVO，用于响应给客户端的Json对象
 */
class CourseEvaluateJsonVO : public JsonVO<CourseEvaluateDTO::Wrapper> {
	DTO_INIT(CourseEvaluateJsonVO, JsonVO<CourseEvaluateDTO::Wrapper>);
};

/**
 * 课程评价分页显示JsonVO，用于响应给客户端的Json对象
 */
class CourseEvaluatePageJsonVO : public JsonVO<CourseEvaluatePageDTO::Wrapper> {
	DTO_INIT(CourseEvaluatePageJsonVO, JsonVO<CourseEvaluatePageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_COURSEEVALUATE_VO_H_

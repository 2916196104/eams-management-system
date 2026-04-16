#pragma once
#ifndef _GRADEMANAGEVO_H_
#define _GRADEMANAGEVO_H_

#include "domain/GlobalInclude.h"
#include "domain/dto/GradeTable/GradeManageDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 定义一个成绩分页显示JsonVO对象，用于响应给客户端
 */
class GradeManagePageJsonVO : public JsonVO<GradeManagePageDTO::Wrapper>
{
	DTO_INIT(GradeManagePageJsonVO, JsonVO<GradeManagePageDTO::Wrapper>);

};

#include OATPP_CODEGEN_END(DTO)
#endif 
#pragma once

#include "../GlobalInclude.h"
#include "../dto/student/GradeDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)


/**
 * 定义一个用户信息分页显示JsonVO对象，用于响应给客户端
 */
class GradeJsonVO : public JsonVO<GradeDTO::Wrapper>
{
	DTO_INIT(GradeJsonVO, JsonVO<GradeDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)




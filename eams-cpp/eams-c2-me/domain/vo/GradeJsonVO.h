#pragma once


#include "../GlobalInclude.h"
#include "../dto/student/GradeDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)


/**
 * 定义一个用户信息分页显示JsonVO对象，用于响应给客户端
 */
class GradePageJsonVO : public JsonVO<GradePageDTO::Wrapper>
{
	DTO_INIT(GradePageJsonVO, JsonVO<GradePageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
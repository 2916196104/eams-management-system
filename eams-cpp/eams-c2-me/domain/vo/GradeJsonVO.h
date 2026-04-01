#pragma once


#include "../GlobalInclude.h"
#include "../dto/student/GradeDTO.h"
#include "../dto/student/GradeListDTO.h"
#include OATPP_CODEGEN_BEGIN(DTO)


/**
 * 定义一个用户信息分页显示JsonVO对象，用于响应给客户端
 */
class GradeListJsonVO : public JsonVO<GradeListDTO::Wrapper>
{
	DTO_INIT(GradeListJsonVO, JsonVO<GradeListDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
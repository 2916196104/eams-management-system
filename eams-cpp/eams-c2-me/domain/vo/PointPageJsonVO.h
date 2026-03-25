#pragma once

#include "../GlobalInclude.h"
#include "../dto/student/PointDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)


/**
 * 定义一个用户信息分页显示JsonVO对象，用于响应给客户端
 */
class PointPageJsonVO : public JsonVO<PointPageDTO::Wrapper>
{
	DTO_INIT(PointPageJsonVO, JsonVO<PointPageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)





#pragma once

#ifndef _PARENT_VO_
#define _PARENT_VO_

#include "../../GlobalInclude.h"
#include "domain/dto/parent/ParentInfoDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
 * 显示JsonVO，用于响应给客户端的Json对象
 */
class ParentInfoJsonVO : public JsonVO<ParentInfoDTO::Wrapper> {
  DTO_INIT(ParentInfoJsonVO, JsonVO<ParentInfoDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_PARENT_VO_

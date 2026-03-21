#pragma once

#ifndef _PARENT_VO_
#define _PARENT_VO_

#include "../../GlobalInclude.h"
#include "../../dto/parent/ParentDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
 * 显示JsonVO，用于响应给客户端的Json对象 
 */
class ParentJsonVO : public JsonVO<ParentDTO::Wrapper> {
  DTO_INIT(ParentJsonVO, JsonVO<ParentDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_PARENT_VO_


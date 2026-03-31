#pragma once

#ifndef _PARENTINFO_VO_
#define _PARENTINFO_VO_

#include "../../GlobalInclude.h"
#include "../../dto/parent/ParentDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
 * 显示JsonVO，用于响应给客户端的Json对象 
 */
class ParentInfoJsonVO : public JsonVO<ParentDTO::Wrapper> {
  DTO_INIT(ParentInfoJsonVO, JsonVO<ParentDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_PARENTINFO_VO_


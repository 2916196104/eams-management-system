#pragma once

#ifndef _PARENTVO_H_
#define _PARENTVO_H_

#include "../../GlobalInclude.h"
#include "../../dto/parent/ParentDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 示例显示JsonVO，用于响应给客户端的Json对象
	家长数据传输对象
 */
class ParentJsonVO : public JsonVO<ParentDTO::Wrapper> {
  DTO_INIT(ParentDTO, JsonVO<ParentDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_PARENTVO_H_

#pragma once

<<<<<<< Updated upstream
<<<<<<< Updated upstream
#ifndef _PARENTVO_H_
#define _PARENTVO_H_
=======
#ifndef _PARENT_VO_
#define _PARENT_VO_
>>>>>>> Stashed changes
=======
#ifndef _PARENT_VO_
#define _PARENT_VO_
>>>>>>> Stashed changes

#include "../../GlobalInclude.h"
#include "../../dto/parent/ParentDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

<<<<<<< Updated upstream
<<<<<<< Updated upstream
/**
 * 示例显示JsonVO，用于响应给客户端的Json对象
	家长数据传输对象
 */
class ParentJsonVO : public JsonVO<ParentDTO::Wrapper> {
  DTO_INIT(ParentDTO, JsonVO<ParentDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_PARENTVO_H_
=======
=======
>>>>>>> Stashed changes
/*
 * 显示JsonVO，用于响应给客户端的Json对象 
 */
class ParentJsonVO : public JsonVO<ParentDTO::Wrapper> {
  DTO_INIT(ParentJsonVO, JsonVO<ParentDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_PARENT_VO_

<<<<<<< Updated upstream
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes

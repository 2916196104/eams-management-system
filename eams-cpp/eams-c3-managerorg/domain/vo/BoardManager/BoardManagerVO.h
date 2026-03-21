#ifndef __BOARDMANAGERVO_H__
#define __BOARDMANAGERVO_H__

#include "domain/GlobalInclude.h"
#include "domain/dto/BoardManager/BoardManagerDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

//公告管理视图类

class GetBoardDetailJsonVO : public JsonVO<GetBoardDetailDTO::Wrapper> {
	DTO_INIT(GetBoardDetailJsonVO, JsonVO<GetBoardDetailDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif
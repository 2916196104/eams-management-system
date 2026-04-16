#ifndef __BOARDMANAGERVO_H__
#define __BOARDMANAGERVO_H__

#include "domain/GlobalInclude.h"
#include "domain/dto/BoardManager/BoardManagerDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)




class GetBoardDetailJsonVO : public JsonVO<GetBoardDetailDTO::Wrapper> {
	DTO_INIT(GetBoardDetailJsonVO, JsonVO<GetBoardDetailDTO::Wrapper>);
};

// 定义一个公告信息分页显示JsonVO对象，用于响应给客户端

class BoardPageJsonVO : public JsonVO<BoardPageDTO::Wrapper>
{
	DTO_INIT(BoardPageJsonVO, JsonVO<BoardPageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif
#pragma once
#ifndef COMMENTRECORDVO_H
#define COMMENTRECORDVO_H
#include "ServerInfo.h" //中文字典需要引入的头文件
#include "Macros.h"   //中文字典需要引入的头文件
#include "../../GlobalInclude.h"
#include "../../dto/huitailang-dto/commentrecorddto.h"

#include OATPP_CODEGEN_BEGIN(DTO)
//rollcallDTO
class CommentrecordsonVO : public JsonVO< CommentrecordPageDTO::Wrapper> {
	DTO_INIT(CommentrecordsonVO, JsonVO< CommentrecordPageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)





#endif
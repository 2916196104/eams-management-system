#pragma once
#ifndef ROLLCALLVO_H
#define ROLLCALLVO_H
#include "ServerInfo.h" //中文字典需要引入的头文件
#include "Macros.h"   //中文字典需要引入的头文件
#include "../../GlobalInclude.h"
#include "../../dto/huitailang-dto/rollcalldto.h"

#include OATPP_CODEGEN_BEGIN(DTO)
//rollcallDTO
class RollCallJsonVO : public JsonVO<rollcallPageDTO::Wrapper> {
	DTO_INIT(RollCallJsonVO, JsonVO<rollcallPageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !
#pragma once
#ifndef INTENDEDSTUDENTVO_H
#define INTENDEDSTUDENTVO_H

#include "ServerInfo.h" //中文字典需要引入的头文件
#include "Macros.h"   //中文字典需要引入的头文件
#include "../../GlobalInclude.h"
#include "../../dto/dto-huitailang/intendedstudentdto.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class intendedstudentJsonVO : public JsonVO<intendedstudentDTO::Wrapper> {
	DTO_INIT(intendedstudentJsonVO, JsonVO<intendedstudentDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)


#endif
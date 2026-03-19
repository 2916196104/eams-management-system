#pragma once
#ifndef ROLLCALLDTO_H
#include "../../GlobalInclude.h"
#include "ServerInfo.h" //中文字典需要引入的头文件
#include "Macros.h"   //中文字典需要引入的头文件
#include OATPP_CODEGEN_BEGIN(DTO)
class rollcallDTO : public oatpp::DTO
{
	DTO_INIT(rollcallDTO, DTO);
	//学生姓名
	API_DTO_FIELD_REQUIRE(String, stunameid, ZH_WORDS_GETTER("rollcall.stuname"), true);
	//签到时间
	API_DTO_FIELD_REQUIRE(String, checkindate, ZH_WORDS_GETTER("rollcall.checkindate"), true);
	

};

class rollcallPageDTO : public PageDTO<rollcallDTO::Wrapper>
{
	DTO_INIT(rollcallDTO, PageDTO<rollcallDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)



#endif // !ROLLCALLDTO_H


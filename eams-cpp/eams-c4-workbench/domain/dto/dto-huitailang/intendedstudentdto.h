#pragma once
#ifndef INTENDEDSTUDENTDTO_H
#define INTENDEDSTUDENTDTO_H
#include "../../GlobalInclude.h"
#include "ServerInfo.h" //中文字典需要引入的头文件
#include "Macros.h"   //中文字典需要引入的头文件
#include OATPP_CODEGEN_BEGIN(DTO)
class intendedstudentDTO : public oatpp::DTO
{
	DTO_INIT(intendedstudentDTO, DTO);
	//学生姓名
	
	API_DTO_FIELD_REQUIRE(String, studentName, ZH_WORDS_GETTER("intendedstudent.stuname"), true);
	//手机号
	API_DTO_FIELD_REQUIRE(String, phoneNumber, ZH_WORDS_GETTER("intendedstudent.phonenumber"), true);
	//学生类别
	API_DTO_FIELD_REQUIRE(Int8, studentType, ZH_WORDS_GETTER("intendedstudent.stutype"), true);
	//性别
	API_DTO_FIELD_REQUIRE(Int8, sex, ZH_WORDS_GETTER("intendedstudent.sex"), true);
	//出生年月
	API_DTO_FIELD_DEFAULT(String, birthday, ZH_WORDS_GETTER("intendedstudent.birthday"));
	//身份证号
	API_DTO_FIELD_DEFAULT(String, cardId, ZH_WORDS_GETTER("intendedstudent.cardid"));
	//备注信息
	API_DTO_FIELD_DEFAULT(String, text, ZH_WORDS_GETTER("intendedstudent.text"));
	// 关联一个PayloadDTO负载数据对象
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
public:
	//数据校验
	std::string validate()
	{
		if (!studentName || studentName->empty())
			return "name invalidate.";
		if (!phoneNumber || phoneNumber->empty())
			return "phoneNumber invalidate.";
		return "";
	}
};



#include OATPP_CODEGEN_END(DTO)


#endif
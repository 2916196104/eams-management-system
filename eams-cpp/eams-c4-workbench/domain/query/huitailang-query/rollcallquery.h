#pragma once
#ifndef ROLLCALLQUERY_H
#define ROLLCALLQUERY_H
#include "domain/query/PageQuery.h"
#include "../../GlobalInclude.h"
#include "ServerInfo.h" //中文字典需要引入的头文件
#include "Macros.h"   //中文字典需要引入的头文件

#include OATPP_CODEGEN_BEGIN(DTO)

class RollcallQuery : public PageQuery
{
	DTO_INIT(RollcallQuery, PageQuery);
	
	//教师id
	API_DTO_FIELD_REQUIRE(String, teacherId, ZH_WORDS_GETTER("rollcall.teacherid"),true);
	//课程id
	API_DTO_FIELD_REQUIRE(String, courseId, ZH_WORDS_GETTER("rollcall.courseid"),true);
	
};


#include OATPP_CODEGEN_END(DTO)
#endif // !ROLLCALLQUERY_H

#pragma once
#ifndef COMMENTRECORDQUERY_H
#define COMMENTRECORDQUERY_H
#include "domain/query/PageQuery.h"
#include "../../GlobalInclude.h"
#include "ServerInfo.h" //中文字典需要引入的头文件
#include "Macros.h"   //中文字典需要引入的头文件

#include OATPP_CODEGEN_BEGIN(DTO)

class CommentrecordQuery : public PageQuery
{
	DTO_INIT(CommentrecordQuery, PageQuery);

	//教师id
	API_DTO_FIELD_REQUIRE(String, teacherId, ZH_WORDS_GETTER("comment.teacherid"), true);

};


#include OATPP_CODEGEN_END(DTO)
#endif // !COMMENTRECORDQUERY_H
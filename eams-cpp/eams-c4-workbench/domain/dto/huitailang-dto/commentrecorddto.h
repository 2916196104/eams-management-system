#pragma once
#ifndef COMMENTRECORDDTO_H
#define COMMENTRECORDDTO_H

#include "../../GlobalInclude.h"
#include "ServerInfo.h" //中文字典需要引入的头文件
#include "Macros.h"   //中文字典需要引入的头文件
#include OATPP_CODEGEN_BEGIN(DTO)
class CommentrecordDTO : public oatpp::DTO
{
	DTO_INIT(CommentrecordDTO, DTO);
	//学生姓名
	API_DTO_FIELD_REQUIRE(String, studentName, ZH_WORDS_GETTER("comment.stuname"), true);
	//评论内容
	API_DTO_FIELD_REQUIRE(String, commentText, ZH_WORDS_GETTER("comment.text"), true);
	//评论时间
	API_DTO_FIELD_REQUIRE(String, commentDate, ZH_WORDS_GETTER("comment.date"), true);
	//综合评价
	API_DTO_FIELD_REQUIRE(Int8, score, ZH_WORDS_GETTER("comment.score"), true);
	//是否匿名
	/*API_DTO_FIELD_REQUIRE(Int8, anonymity, ZH_WORDS_GETTER("comment.anonymity"), true);*/


};

class CommentrecordPageDTO : public PageDTO<CommentrecordDTO::Wrapper>
{
	DTO_INIT(CommentrecordPageDTO, PageDTO<CommentrecordDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)



#endif // !COMMENTRECORDDTO_H

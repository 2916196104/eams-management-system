#ifndef __GRADE_MANAGE_DTO_H__
#define __GRADE_MANAGE_DTO_H__

#include "domain/GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

//成绩DTO类



class GradeManageDTO : public oatpp::DTO
{
	DTO_INIT(GradeManageDTO, DTO);

	// id (非必须, 通常新增时不传，更新时传)，但是目前而言，这个id是什么，我不知道
	API_DTO_FIELD_DEFAULT(Int64, id, ZH_WORDS_GETTER("Grade.field.id"));
	//考核项（必须）
	API_DTO_FIELD_REQUIRE(String, item, ZH_WORDS_GETTER("Grade.field.item"), true);
	//学生姓名
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("Grade.field.name"));
	//成绩
	API_DTO_FIELD_DEFAULT(Float32, score, ZH_WORDS_GETTER("Grade.field.sc"));
	//操作
	API_DTO_FIELD_DEFAULT(String, operation, ZH_WORDS_GETTER("Grade.field.operation"));

public:

	// 数据校验
	std::string validate()
	{
		if (!item || item->empty())
			return "item invalidate.";
		return "";
	}
};


//成绩分页类
class GradeManagePageDTO : public PageDTO<GradeManageDTO::Wrapper>
{
	DTO_INIT(GradeManagePageDTO, PageDTO<GradeManageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif
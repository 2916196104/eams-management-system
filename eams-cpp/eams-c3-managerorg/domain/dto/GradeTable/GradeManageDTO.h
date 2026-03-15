#ifndef __GRADE_MANAGE_DTO_H__
#define __GRADE_MANAGE_DTO_H__

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*成绩DTO类*/


class GradeManageDTO : public oatpp::DTO
{
	DTO_INIT(GradeManageDTO, DTO);
	//考核项
	API_DTO_FIELD_REQUIRE(String, item, ZH_WORDS_GETTER("Grade.field.item"), true);
	//学生姓名
	API_DTO_FIELD_REQUIRE(String, name, ZH_WORDS_GETTER("Grade.field.name"), true);
	//成绩
	API_DTO_FIELD_REQUIRE(Float32, score, ZH_WORDS_GETTER("Grade.field.sc"), true);
	//操作
	
};


//成绩分页类
class GradeManagePageDTO : public PageDTO<GradeManageDTO::Wrapper>
{
	DTO_INIT(GradeManagePageDTO, PageDTO<GradeManageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif
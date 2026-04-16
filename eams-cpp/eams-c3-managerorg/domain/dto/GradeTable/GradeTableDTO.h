#ifndef __GRADE_TABLE_DTO_H__
#define __GRADE_TABLE_DTO_H__

#include "domain/GlobalInclude.h"
#include "domain/dto/PageDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

//成绩单DTO
class GradeTableDTO : public oatpp::DTO
{
	DTO_INIT(GradeTableDTO, DTO);

	// 1. 主键ID（成绩单记录唯一标识）
	API_DTO_FIELD_DEFAULT(UInt64, id, ZH_WORDS_GETTER("GradeTableDTO.id"))

		// 2. 考核项信息
		API_DTO_FIELD_DEFAULT(String, itemName, ZH_WORDS_GETTER("GradeTableDTO.itemName"))
		API_DTO_FIELD_DEFAULT(String, itemDesc, ZH_WORDS_GETTER("GradeTableDTO.itemDesc"))

		// 3. 发布者信息
		API_DTO_FIELD_DEFAULT(UInt64, publisherId, ZH_WORDS_GETTER("GradeTableDTO.publisherId"))
		API_DTO_FIELD_DEFAULT(String, publisherName, ZH_WORDS_GETTER("GradeTableDTO.publisherName"))

		// 4. 发布时间
		API_DTO_FIELD_DEFAULT(String, publishTime, ZH_WORDS_GETTER("GradeTableDTO.publishTime"))
};


//成绩单分页类
class GradeTablePageDTO : public PageDTO<GradeTableDTO::Wrapper>
{
	DTO_INIT(GradeTablePageDTO, PageDTO<GradeTableDTO::Wrapper>);
};
#include OATPP_CODEGEN_END(DTO)

#endif // !__GRADE_TABLE_DTO_H__
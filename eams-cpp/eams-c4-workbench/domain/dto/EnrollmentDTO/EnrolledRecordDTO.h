#pragma once
#ifndef _ENROLLEDRECORD_DTO_
#define _ENROLLEDRECORD_DTO_
#include"../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)
/*
* 报名记录数据传输对象
*/
class EnrolledRecordDTO :public oatpp::DTO
{
	DTO_INIT(EnrolledRecordDTO, DTO);
	API_DTO_FIELD_REQUIRE(Int64,id,ZH_WORDS_GETTER(""),false);
	API_DTO_FIELD_DEFAULT(String,name, ZH_WORDS_GETTER(""));

};
/*
* 报名记录分页传输对象
*/
class EnrolledRecordPageDTO :public PageDTO<EnrolledRecordDTO::Wrapper>
{
	DTO_INIT(EnrolledRecordPageDTO,PageDTO<EnrolledRecordDTO::Wrapper>);
};
/*
* 报名记录详情传输对象
*/
class EnrolledRecordDetailDTO :public EnrolledRecordDTO
{
	DTO_INIT(EnrolledRecordDetailDTO, EnrolledRecordDTO);
	// 其他报名记录详情字段
};
#include OATPP_CODEGEN_END(DTO)
#endif // !ENROLLEDRECORDDTO

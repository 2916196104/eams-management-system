#pragma once
#ifndef _ENROLLEDRECORD_VO_
#define _ENROLLEDRECORD_VO_
#include"../../GlobalInclude.h"
#include"../../dto/EnrollmentDTO/EnrolledRecordDTO.h"
#include"../../../../lib-oatpp/include/domain/vo/BaseJsonVO.h"
#include OATPP_CODEGEN_BEGIN(DTO)
/*
* 报名记录分页显示对象
*/
class EnrolledRecordPageJsonVO :public JsonVO<EnrolledRecordPageDTO::Wrapper>
{
	DTO_INIT(EnrolledRecordPageJsonVO, JsonVO<EnrolledRecordPageDTO::Wrapper>);
};
/*
* 报名记录列表显示对象
*/
class EnrolledRecordListJsonVO :public JsonVO<EnrolledRecordPageDTO::Wrapper>
{
	DTO_INIT(EnrolledRecordListJsonVO, JsonVO<EnrolledRecordPageDTO::Wrapper>);
};
/*
* 报名记录详情显示对象
*/
class EnrolledRecordDetailJsonVO :public JsonVO<EnrolledRecordDTO::Wrapper>
{
	DTO_INIT(EnrolledRecordDetailJsonVO, JsonVO<EnrolledRecordDTO::Wrapper>);
};
#include OATPP_CODEGEN_END(DTO)
#endif // !_ENROLLEDRECORD_VO_

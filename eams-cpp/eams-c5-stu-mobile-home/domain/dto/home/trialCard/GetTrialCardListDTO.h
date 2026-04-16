#pragma once
#ifndef _GETTRIALCARDLISTDTO_H_
#define _GETTRIALCARDLISTDTO_H_
#include "../../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class GetTrialCardListAddDTO : public oatpp::DTO
{
	DTO_INIT(GetTrialCardListAddDTO, DTO)
	
	DTO_FIELD(String, name); // 试用卡名称
	DTO_FIELD_INFO(name)
	{
		info->description = ZH_WORDS_GETTER("home.trialCard.name");
	}
		
	DTO_FIELD(String, courseName); // 试用卡课程名称
	DTO_FIELD_INFO(courseName)
	{
		info->description = ZH_WORDS_GETTER("home.trialCard.courseName");
	}

	DTO_FIELD(Int32, lessonCount); // 试用卡课时
	DTO_FIELD_INFO(lessonCount)
	{
		info->description = ZH_WORDS_GETTER("home.trialCard.lessonCount");
	}

	DTO_FIELD(Int32, remainingQuantity); // 试用卡剩余数量
	DTO_FIELD_INFO(remainingQuantity)
	{
		info->description = ZH_WORDS_GETTER("home.trialCard.remainingQuantity");
	}

	DTO_FIELD(String, endTime); // 试用卡截止时间
	DTO_FIELD_INFO(endTime)
	{
		info->description = ZH_WORDS_GETTER("home.trialCard.endTime");
	}
	// 关联一个PayloadDTO负载数据对象
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
};

class GetTrialCardListDTO : public GetTrialCardListAddDTO
{
	DTO_INIT(GetTrialCardListDTO, GetTrialCardListAddDTO)
	
	DTO_FIELD(String, id); // 试用卡id
	DTO_FIELD_INFO(id)
	{
		info->description = ZH_WORDS_GETTER("student.id");
	}
};

class GetTrialCardListPageDTO : public PageDTO<GetTrialCardListDTO::Wrapper>
{
	DTO_INIT(GetTrialCardListPageDTO, PageDTO<GetTrialCardListDTO::Wrapper>)
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_GETTRIALCARDLISTDTO_H

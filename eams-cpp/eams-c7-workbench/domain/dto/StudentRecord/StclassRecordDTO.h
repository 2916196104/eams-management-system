#pragma once

#include"../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

//数据DTO
class StclassRecordDTO :public oatpp::DTO
{
	DTO_INIT(StclassRecordDTO, DTO);

	//课程名称
	DTO_FIELD(String, title);
	DTO_FIELD_INFO(title)
	{
		info->description = ZH_WORDS_GETTER("stclassrecord.dto.title");
	}
	// 课程状态
	DTO_FIELD(Int32, state);
	DTO_FIELD_INFO(state)
	{
		info->description = ZH_WORDS_GETTER("stclassrecord.dto.state");
	}
	// 是否签到
	DTO_FIELD(Int32, signType);
	DTO_FIELD_INFO(signType)
	{
		info->description = ZH_WORDS_GETTER("stclassrecord.dto.signType");
	}
	// 课程开始时间
	DTO_FIELD(String, startTime);
	DTO_FIELD_INFO(startTime)
	{
		info->description = ZH_WORDS_GETTER("stclassrecord.dto.startTime");
	}
	// 课程结束时间
	DTO_FIELD(String, endTime);
	DTO_FIELD_INFO(endTime)
	{
		info->description = ZH_WORDS_GETTER("stclassrecord.dto.endTime");
	}
};


//分页
class StclassRecordPageDTO :public PageDTO<StclassRecordDTO::Wrapper>
{
	DTO_INIT(StclassRecordPageDTO, PageDTO<StclassRecordDTO::Wrapper>);
};
#include OATPP_CODEGEN_END(DTO)
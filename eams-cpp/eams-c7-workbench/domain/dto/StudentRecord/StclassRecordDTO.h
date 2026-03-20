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
		info->description=ZH_WORDS_GETTER("stclassrecord.dto.title");
	}
	// 课程状态
	DTO_FIELD(Int32, state);
	DTO_FIELD_INFO(state)
	{
		info->description=ZH_WORDS_GETTER("stclassrecord.dto.state");
	}
	// 是否签到
	DTO_FIELD(Int32, sign_state);
	DTO_FIELD_INFO(sign_state)
	{
		info->description=ZH_WORDS_GETTER("stclassrecord.dto.sign_state");
	}
	// 课程开始时间
	DTO_FIELD(String, start_time);
	DTO_FIELD_INFO(start_time)
	{
		info->description=ZH_WORDS_GETTER("stclassrecord.dto.start_time");
	}
	// 课程结束时间
	DTO_FIELD(String, end_time);
	DTO_FIELD_INFO(end_time)
	{
		info->description=ZH_WORDS_GETTER("stclassrecord.dto.end_time");
	}
};


//分页
class StclassRecordPageDTO :public PageDTO<StclassRecordDTO::Wrapper>
{
	DTO_INIT(StclassRecordPageDTO, PageDTO<StclassRecordDTO::Wrapper>);
};
#include OATPP_CODEGEN_END(DTO)
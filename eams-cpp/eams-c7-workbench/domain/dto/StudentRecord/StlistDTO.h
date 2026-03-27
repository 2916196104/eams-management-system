#pragma once

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

//传输对象DTO
class StlistDTO :public oatpp::DTO
{
	DTO_INIT(StlistDTO, DTO);

	//学生姓名
	DTO_FIELD(String, name);
	DTO_FIELD_INFO(name) {
		info->description = ZH_WORDS_GETTER("stlist.dto.name");
	}
	//学生手机号
	DTO_FIELD(String, mobile);
	DTO_FIELD_INFO(mobile) {
		info->description = ZH_WORDS_GETTER("stlist.dto.mobile");
	}
	//学生剩余课时
	DTO_FIELD(Int32, closeTime);
	DTO_FIELD_INFO(closeTime) {
		info->description = ZH_WORDS_GETTER("stlist.dto.closeTime");
	}

	//学生性别
	DTO_FIELD(Int32, gender);
	DTO_FIELD_INFO(gender) {
		info->description = ZH_WORDS_GETTER("stlist.dto.gender");
	}
public:
	// 数据校验
	std::string validate()
	{
		if (closeTime < 0)
			return "timeRemaining invalidate.";
		if (!name || name->empty())
			return "name invalidate.";
		if (!mobile || mobile->empty())
			return "telephone invalidate.";
		return "";
	}
};


/**
DTO分页对象
 */
class StlistPageDTO : public PageDTO<StlistDTO::Wrapper>
{
	DTO_INIT(StlistPageDTO, PageDTO<StlistDTO::Wrapper>);
};


#include OATPP_CODEGEN_END(DTO)
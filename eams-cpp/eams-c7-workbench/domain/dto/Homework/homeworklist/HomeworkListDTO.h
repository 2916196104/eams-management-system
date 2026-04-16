#pragma once

#include "../../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)
class HomeworkListDTO :public oatpp::DTO
{
	DTO_INIT(HomeworkListDTO, DTO);
	
	//作业标题
	DTO_FIELD(String, title);
	DTO_FIELD_INFO(title) {
		info->description = ZH_WORDS_GETTER("homeworklist.dto.title");
	}

	//提交作业人数
	DTO_FIELD(Int32, number);
	DTO_FIELD_INFO(number) {
		info->description = ZH_WORDS_GETTER("homeworklist.dto.number");
	}

	//班级名称
	DTO_FIELD(String, className);
	DTO_FIELD_INFO(className) {
		info->description = ZH_WORDS_GETTER("homeworklist.dto.className");
	}

	//课程名称
	DTO_FIELD(String, courseName);
	DTO_FIELD_INFO(courseName) {
		info->description = ZH_WORDS_GETTER("homeworklist.dto.courseName");
	}
};

class HomeworkListPageDTO :public PageDTO<HomeworkListDTO::Wrapper>
{
	DTO_INIT(HomeworkListPageDTO, PageDTO<HomeworkListDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
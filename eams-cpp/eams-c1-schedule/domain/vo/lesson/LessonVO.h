#pragma once
#ifndef _LESSON_VO_
#define _LESSON_VO_

#include "../../GlobalInclude.h"
#include "domain/dto/PageDTO.h"
#include "ApiHelper.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class LessonVO : public oatpp::DTO
{
	DTO_INIT(LessonVO, DTO);

	// 对应 JSON 里的字段名
	API_DTO_FIELD_DEFAULT(UInt64, id, ZH_WORDS_GETTER("lesson.field.id"));
	API_DTO_FIELD_DEFAULT(String, date, ZH_WORDS_GETTER("lesson.field.date"));
	API_DTO_FIELD_DEFAULT(String, startTime, ZH_WORDS_GETTER("lesson.field.startTime"));
	API_DTO_FIELD_DEFAULT(String, endTime, ZH_WORDS_GETTER("lesson.field.endTime"));

	API_DTO_FIELD_DEFAULT(String, courseName, ZH_WORDS_GETTER("lesson.field.courseName"));
	API_DTO_FIELD_DEFAULT(String, className, ZH_WORDS_GETTER("lesson.field.className"));
	API_DTO_FIELD_DEFAULT(String, teacherNames, ZH_WORDS_GETTER("lesson.field.teacherNames"));
	API_DTO_FIELD_DEFAULT(String, classroom, ZH_WORDS_GETTER("lesson.field.classroom"));

	API_DTO_FIELD_DEFAULT(String, state, ZH_WORDS_GETTER("lesson.field.state")); // "进行中"
	API_DTO_FIELD_DEFAULT(String, studentSignState, ZH_WORDS_GETTER("lesson.field.studentSignState")); // "未签到"

	// 按钮权限控制 (布尔值)
	API_DTO_FIELD_DEFAULT(Boolean, studentCanSign, ZH_WORDS_GETTER("lesson.field.studentCanSign"));
	API_DTO_FIELD_DEFAULT(Boolean, studentCanLeave, ZH_WORDS_GETTER("lesson.field.studentCanLeave"));
	API_DTO_FIELD_DEFAULT(Boolean, bookable, ZH_WORDS_GETTER("lesson.field.bookable"));
};

// 定义分页 DTO
class LessonPageDTO : public PageDTO<LessonVO::Wrapper>
{
	DTO_INIT(LessonPageDTO, PageDTO<LessonVO::Wrapper>);
};

// 定义最终返回的 JsonVO
class LessonPageJsonVO : public JsonVO<LessonPageDTO::Wrapper> {
	DTO_INIT(LessonPageJsonVO, JsonVO<LessonPageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_LESSON_VO_
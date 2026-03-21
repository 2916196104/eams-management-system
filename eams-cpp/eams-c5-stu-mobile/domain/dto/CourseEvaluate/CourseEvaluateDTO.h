#pragma once
#ifndef _COURSEEVALUATE_DTO_H_
#define _COURSEEVALUATE_DTO_H_

#include "../../GlobalInclude.h"
#include "domain/dto/PageDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class CourseEvaluateDTO : public oatpp::DTO
{
	DTO_INIT(CourseEvaluateDTO, DTO);

	DTO_FIELD(UInt64, id);
	DTO_FIELD_INFO(id) { info->description = ZH_WORDS_GETTER("CourseEvaluate.field.id"); }

	DTO_FIELD(UInt64, course_id);
	DTO_FIELD_INFO(course_id) { info->description = ZH_WORDS_GETTER("CourseEvaluate.field.course_id"); }

	DTO_FIELD(UInt64, student_id);
	DTO_FIELD_INFO(student_id) { info->description = ZH_WORDS_GETTER("CourseEvaluate.field.student_id"); }

	DTO_FIELD(UInt64, order_id);
	DTO_FIELD_INFO(order_id) { info->description = ZH_WORDS_GETTER("CourseEvaluate.field.order_id"); }

	DTO_FIELD(String, content);
	DTO_FIELD_INFO(content) { info->description = ZH_WORDS_GETTER("CourseEvaluate.field.content"); }

	DTO_FIELD(Int32, score);
	DTO_FIELD_INFO(score) { info->description = ZH_WORDS_GETTER("CourseEvaluate.field.score"); }

	DTO_FIELD(Int32, state);
	DTO_FIELD_INFO(state) { info->description = ZH_WORDS_GETTER("CourseEvaluate.field.state"); }

	DTO_FIELD(UInt64, creator);
	DTO_FIELD_INFO(creator) { info->description = ZH_WORDS_GETTER("CourseEvaluate.field.creator"); }

	DTO_FIELD(UInt64, editor);
	DTO_FIELD_INFO(editor) { info->description = ZH_WORDS_GETTER("CourseEvaluate.field.editor"); }

	DTO_FIELD(String, add_time);
	DTO_FIELD_INFO(add_time) { info->description = ZH_WORDS_GETTER("CourseEvaluate.field.add_time"); }

	DTO_FIELD(String, edit_time);
	DTO_FIELD_INFO(edit_time) { info->description = ZH_WORDS_GETTER("CourseEvaluate.field.edit_time"); }

	DTO_FIELD(Int32, deleted);
	DTO_FIELD_INFO(deleted) { info->description = ZH_WORDS_GETTER("CourseEvaluate.field.deleted"); }

	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
};

class CourseEvaluatePageDTO : public PageDTO<CourseEvaluateDTO::Wrapper>
{
	DTO_INIT(CourseEvaluatePageDTO, PageDTO<CourseEvaluateDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_COURSEEVALUATE_DTO_H_

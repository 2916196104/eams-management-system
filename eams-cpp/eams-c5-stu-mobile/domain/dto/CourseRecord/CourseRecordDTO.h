#pragma once
#ifndef _COURSERECORD_DTO_H_
#define _COURSERECORD_DTO_H_

#include "../../GlobalInclude.h"
#include "domain/dto/PageDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class CourseRecordDTO : public oatpp::DTO
{
	DTO_INIT(CourseRecordDTO, DTO);

	DTO_FIELD(UInt64, id);
	DTO_FIELD_INFO(id) { info->description = ZH_WORDS_GETTER("CourseRecord.field.id"); }

	DTO_FIELD(String, title);
	DTO_FIELD_INFO(title) { info->description = ZH_WORDS_GETTER("CourseRecord.field.title"); }

	DTO_FIELD(Int32, sn);
	DTO_FIELD_INFO(sn) { info->description = ZH_WORDS_GETTER("CourseRecord.field.sn"); }

	DTO_FIELD(UInt64, course_id);
	DTO_FIELD_INFO(course_id) { info->description = ZH_WORDS_GETTER("CourseRecord.field.course_id"); }

	DTO_FIELD(UInt64, schedule_id);
	DTO_FIELD_INFO(schedule_id) { info->description = ZH_WORDS_GETTER("CourseRecord.field.schedule_id"); }

	DTO_FIELD(UInt64, class_id);
	DTO_FIELD_INFO(class_id) { info->description = ZH_WORDS_GETTER("CourseRecord.field.class_id"); }

	DTO_FIELD(UInt64, room_id);
	DTO_FIELD_INFO(room_id) { info->description = ZH_WORDS_GETTER("CourseRecord.field.room_id"); }

	DTO_FIELD(String, date);
	DTO_FIELD_INFO(date) { info->description = ZH_WORDS_GETTER("CourseRecord.field.date"); }

	DTO_FIELD(String, start_time);
	DTO_FIELD_INFO(start_time) { info->description = ZH_WORDS_GETTER("CourseRecord.field.start_time"); }

	DTO_FIELD(String, end_time);
	DTO_FIELD_INFO(end_time) { info->description = ZH_WORDS_GETTER("CourseRecord.field.end_time"); }

	DTO_FIELD(UInt64, creator);
	DTO_FIELD_INFO(creator) { info->description = ZH_WORDS_GETTER("CourseRecord.field.creator"); }

	DTO_FIELD(UInt64, editor);
	DTO_FIELD_INFO(editor) { info->description = ZH_WORDS_GETTER("CourseRecord.field.editor"); }

	DTO_FIELD(String, add_time);
	DTO_FIELD_INFO(add_time) { info->description = ZH_WORDS_GETTER("CourseRecord.field.add_time"); }

	DTO_FIELD(String, edit_time);
	DTO_FIELD_INFO(edit_time) { info->description = ZH_WORDS_GETTER("CourseRecord.field.edit_time"); }

	DTO_FIELD(Int32, deleted);
	DTO_FIELD_INFO(deleted) { info->description = ZH_WORDS_GETTER("CourseRecord.field.deleted"); }

	DTO_FIELD(Int32, dec_count);
	DTO_FIELD_INFO(dec_count) { info->description = ZH_WORDS_GETTER("CourseRecord.field.dec_count"); }

	DTO_FIELD(String, remark);
	DTO_FIELD_INFO(remark) { info->description = ZH_WORDS_GETTER("CourseRecord.field.remark"); }

	DTO_FIELD(Int32, teach_type);
	DTO_FIELD_INFO(teach_type) { info->description = ZH_WORDS_GETTER("CourseRecord.field.teach_type"); }

	DTO_FIELD(Int32, on_trial);
	DTO_FIELD_INFO(on_trial) { info->description = ZH_WORDS_GETTER("CourseRecord.field.on_trial"); }

	DTO_FIELD(String, trial_result);
	DTO_FIELD_INFO(trial_result) { info->description = ZH_WORDS_GETTER("CourseRecord.field.trial_result"); }

	DTO_FIELD(Int32, state);
	DTO_FIELD_INFO(state) { info->description = ZH_WORDS_GETTER("CourseRecord.field.state"); }

	DTO_FIELD(String, close_time);
	DTO_FIELD_INFO(close_time) { info->description = ZH_WORDS_GETTER("CourseRecord.field.close_time"); }

	DTO_FIELD(UInt64, close_operator);
	DTO_FIELD_INFO(close_operator) { info->description = ZH_WORDS_GETTER("CourseRecord.field.close_operator"); }

	DTO_FIELD(UInt64, teacher_id);
	DTO_FIELD_INFO(teacher_id) { info->description = ZH_WORDS_GETTER("CourseRecord.field.teacher_id"); }

	DTO_FIELD(Int32, bookable);
	DTO_FIELD_INFO(bookable) { info->description = ZH_WORDS_GETTER("CourseRecord.field.bookable"); }

	DTO_FIELD(UInt64, school_id);
	DTO_FIELD_INFO(school_id) { info->description = ZH_WORDS_GETTER("CourseRecord.field.school_id"); }

	DTO_FIELD(UInt64, org_id);
	DTO_FIELD_INFO(org_id) { info->description = ZH_WORDS_GETTER("CourseRecord.field.org_id"); }

	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
};

class CourseRecordPageDTO : public PageDTO<CourseRecordDTO::Wrapper>
{
	DTO_INIT(CourseRecordPageDTO, PageDTO<CourseRecordDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_COURSERECORD_DTO_H_

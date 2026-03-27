#pragma once




#ifndef _ENROLLCOURSES_DTO_
#define _ENROLLCOURSES_DTO_
#include "../../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class EnrollCourseDTO : public oatpp::DTO
{
	DTO_INIT(EnrollCourseDTO, DTO);

	DTO_FIELD(UInt64, id);
	DTO_FIELD_INFO(id) {
		info->description = ZH_WORDS_GETTER("EnrollCourse.field.id");
	}

	DTO_FIELD(UInt64, student_id);
	DTO_FIELD_INFO(student_id) {
		info->description = ZH_WORDS_GETTER("EnrollCourse.field.student_id");
	}


	DTO_FIELD(UInt64, course_id);
	DTO_FIELD_INFO(course_id) {
		info->description = ZH_WORDS_GETTER("EnrollCourse.field.course_id");
	}

	//来自别的表的数据
	DTO_FIELD(String, course_name);
	DTO_FIELD_INFO(course_name) {
		info->description = ZH_WORDS_GETTER("EnrollCourse.field.course_name");
	}

	DTO_FIELD(UInt64, subject_id);
	DTO_FIELD_INFO(subject_id) {
		info->description = ZH_WORDS_GETTER("EnrollCourse.field.subject_id");
	}

	DTO_FIELD(String, subject_name);
	DTO_FIELD_INFO(subject_name) {
		info->description = ZH_WORDS_GETTER("EnrollCourse.field.subject_name");
	}

	DTO_FIELD(String, start_date);
	DTO_FIELD_INFO(start_date) {
		info->description = ZH_WORDS_GETTER("EnrollCourse.field.start_date");
	}

	DTO_FIELD(String, expire_date);
	DTO_FIELD_INFO(expire_date) {
		info->description = ZH_WORDS_GETTER("EnrollCourse.field.expire_date");
	}

	DTO_FIELD(String, remark);
	DTO_FIELD_INFO(remark) {
		info->description = ZH_WORDS_GETTER("EnrollCourse.field.remark");
	}

	DTO_FIELD(Int32, count_lesson_total);
	DTO_FIELD_INFO(count_lesson_total) {
		info->description = ZH_WORDS_GETTER("EnrollCourse.field.count_lesson_total");
	}

	DTO_FIELD(Int32, count_lesson_complete);
	DTO_FIELD_INFO(count_lesson_complete) {
		info->description = ZH_WORDS_GETTER("EnrollCourse.field.count_lesson_complete");
	}

	DTO_FIELD(Int32, count_lesson_refund);
	DTO_FIELD_INFO(count_lesson_refund) {
		info->description = ZH_WORDS_GETTER("EnrollCourse.field.count_lesson_refund");
	}

	DTO_FIELD(Float32, course_amount);
	DTO_FIELD_INFO(course_amount) {
		info->description = ZH_WORDS_GETTER("EnrollCourse.field.course_amount");
	}

	DTO_FIELD(Float32, discount_amount);
	DTO_FIELD_INFO(discount_amount) {
		info->description = ZH_WORDS_GETTER("EnrollCourse.field.discount_amount");
	}

	DTO_FIELD(Float32, amount);
	DTO_FIELD_INFO(amount) {
		info->description = ZH_WORDS_GETTER("EnrollCourse.field.amount");
	}

	DTO_FIELD(Float32, paid_amount);
	DTO_FIELD_INFO(paid_amount) {
		info->description = ZH_WORDS_GETTER("EnrollCourse.field.paid_amount");
	}

	DTO_FIELD(Int32, pay_off);
	DTO_FIELD_INFO(pay_off) {
		info->description = ZH_WORDS_GETTER("EnrollCourse.field.pay_off");
	}

	DTO_FIELD(Int64, operater);
	DTO_FIELD_INFO(operater) {
		info->description = ZH_WORDS_GETTER("EnrollCourse.field.operater");
	}

	DTO_FIELD(Int64, creator);
	DTO_FIELD_INFO(creator) {
		info->description = ZH_WORDS_GETTER("EnrollCourse.field.creator");
	}

	DTO_FIELD(String, add_time);
	DTO_FIELD_INFO(add_time) {
		info->description = ZH_WORDS_GETTER("EnrollCourse.field.add_time");
	}

	DTO_FIELD(Int64, editor);
	DTO_FIELD_INFO(editor) {
		info->description = ZH_WORDS_GETTER("EnrollCourse.field.editor");
	}

	DTO_FIELD(String, edit_time);
	DTO_FIELD_INFO(edit_time) {
		info->description = ZH_WORDS_GETTER("EnrollCourse.field.edit_time");
	}

	DTO_FIELD(Int32, deleted);
	DTO_FIELD_INFO(deleted) {
		info->description = ZH_WORDS_GETTER("EnrollCourse.field.deleted");
	}

	DTO_FIELD(Int32, verify_state);
	DTO_FIELD_INFO(verify_state) {
		info->description = ZH_WORDS_GETTER("EnrollCourse.field.verify_state");
	}

	DTO_FIELD(Int32, warning_times);
	DTO_FIELD_INFO(warning_times) {
		info->description = ZH_WORDS_GETTER("EnrollCourse.field.warning_times");
	}

	DTO_FIELD(Int32, priority);
	DTO_FIELD_INFO(priority) {
		info->description = ZH_WORDS_GETTER("EnrollCourse.field.priority");
	}

	DTO_FIELD(Float32, unit_price);
	DTO_FIELD_INFO(unit_price) {
		info->description = ZH_WORDS_GETTER("EnrollCourse.field.unit_price");
	}

	DTO_FIELD(Int32, from_trial);
	DTO_FIELD_INFO(from_trial) {
		info->description = ZH_WORDS_GETTER("EnrollCourse.field.from_trial");
	}

	DTO_FIELD(Int64, org_id);
	DTO_FIELD_INFO(org_id) {
		info->description = ZH_WORDS_GETTER("EnrollCourse.field.org_id");
	}



	
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
};


//class EnrollCoursesDTO : public EnrollCoursesAddDTO
//{
//	DTO_INIT(EnrollCoursesDTO, EnrollC   oursesAddDTO);
//
//	DTO_FIELD(Int32, id);
//	DTO_FIELD_INFO(id) {
//		info->description = "";
//	}
//	
//	
//};


class EnrollCoursePageDTO : public PageDTO<EnrollCourseDTO::Wrapper>
{
	DTO_INIT(EnrollCoursePageDTO, PageDTO<EnrollCourseDTO::Wrapper>);
};





#include OATPP_CODEGEN_END(DTO)
#endif
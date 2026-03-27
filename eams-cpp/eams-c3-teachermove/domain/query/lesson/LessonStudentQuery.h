#pragma once
#ifndef _LESSON_STUDENT_QUERY_H_
#define _LESSON_STUDENT_QUERY_H_

#include "domain/GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 课时学员分页查询对象
 */
class LessonStudentQuery : public PageQuery
{
	DTO_INIT(LessonStudentQuery, PageQuery);

	// 课次ID（精确查询）
	DTO_FIELD(String, lesson_id);
	DTO_FIELD_INFO(lesson_id) {
		info->description = ZH_WORDS_GETTER("lessonStudent.field.lesson_id");
	}

	// 班级ID（精确查询）
	DTO_FIELD(String, class_id);
	DTO_FIELD_INFO(class_id) {
		info->description = ZH_WORDS_GETTER("lessonStudent.field.class_id");
	}

	// 学员ID（精确查询）
	DTO_FIELD(String, student_id);
	DTO_FIELD_INFO(student_id) {
		info->description = ZH_WORDS_GETTER("lessonStudent.field.student_id");
	}

	// 点名老师ID（精确查询）
	DTO_FIELD(String, teacher_id);
	DTO_FIELD_INFO(teacher_id) {
		info->description = ZH_WORDS_GETTER("lessonStudent.field.teacher_id");
	}

	// 签到结果（精确查询）
	DTO_FIELD(String, sign_state);
	DTO_FIELD_INFO(sign_state) {
		info->description = ZH_WORDS_GETTER("lessonStudent.field.sign_state");
	}

	// 组织ID（精确查询）
	DTO_FIELD(String, org_id);
	DTO_FIELD_INFO(org_id) {
		info->description = ZH_WORDS_GETTER("lessonStudent.field.org_id");
	}
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_LESSON_STUDENT_QUERY_H_

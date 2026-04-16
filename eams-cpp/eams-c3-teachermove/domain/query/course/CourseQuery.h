#pragma once
#ifndef _COURSE_QUERY_H_
#define _COURSE_QUERY_H_

#include "domain/GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 课程分页查询对象
 */
class CourseQuery : public PageQuery
{
	DTO_INIT(CourseQuery, PageQuery);

	// 课程名称（模糊查询）
	DTO_FIELD(String, name);
	DTO_FIELD_INFO(name) {
		info->description = ZH_WORDS_GETTER("course.field.name");
	}

	// 科目ID（精确查询）
	DTO_FIELD(String, subject_id);
	DTO_FIELD_INFO(subject_id) {
		info->description = ZH_WORDS_GETTER("course.field.subject_id");
	}

	// 状态（精确查询）
	DTO_FIELD(String, state);
	DTO_FIELD_INFO(state) {
		info->description = ZH_WORDS_GETTER("course.field.state");
	}

	// 课堂类型（精确查询）
	DTO_FIELD(String, lesson_type);
	DTO_FIELD_INFO(lesson_type) {
		info->description = ZH_WORDS_GETTER("course.field.lesson_type");
	}

	// 是否可预约（精确查询）
	DTO_FIELD(String, bookable);
	DTO_FIELD_INFO(bookable) {
		info->description = ZH_WORDS_GETTER("course.field.bookable");
	}

	// 是否上架（精确查询）
	DTO_FIELD(String, for_sale);
	DTO_FIELD_INFO(for_sale) {
		info->description = ZH_WORDS_GETTER("course.field.for_sale");
	}

	// 是否推荐（精确查询）
	DTO_FIELD(String, recommend);
	DTO_FIELD_INFO(recommend) {
		info->description = ZH_WORDS_GETTER("course.field.recommend");
	}

	// 组织ID（精确查询）
	DTO_FIELD(String, org_id);
	DTO_FIELD_INFO(org_id) {
		info->description = ZH_WORDS_GETTER("course.field.org_id");
	}
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_COURSE_QUERY_H_

#ifndef __CLASS_QUERY_H__
#define __CLASS_QUERY_H__

#include "domain/GlobalInclude.h"

#include"domain/query/PageQuery.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/* 班级查询参数 */

class ClassQuery : public PageQuery
{
	DTO_INIT(ClassQuery, PageQuery);

	// 班级负责人/老师ID
	DTO_FIELD(String, teacher_id);
	DTO_FIELD_INFO(teacher_id) {
		info->description = ZH_WORDS_GETTER("class.teacher");
	}

	DTO_FIELD(String, name);
	DTO_FIELD_INFO(name) {
		info->description = ZH_WORDS_GETTER("class.name");
	}
	// 课程ID
	DTO_FIELD(String, course_id);
	DTO_FIELD_INFO(course_id) {
		info->description = ZH_WORDS_GETTER("class.course");
	}
	// 学校ID
	DTO_FIELD(String, school_id);
	DTO_FIELD_INFO(school_id) {
		info->description = ZH_WORDS_GETTER("class.school");
	}
	// 组织ID
	DTO_FIELD(String, org_id);
	DTO_FIELD_INFO(org_id) {
		info->description = ZH_WORDS_GETTER("class.org");
	}

	DTO_FIELD(String, be_over);
	DTO_FIELD_INFO(be_over) {
		info->description = ZH_WORDS_GETTER("class.beOver");
	}
};
// 课程列表查询参数
class CourseListQuery : public oatpp::DTO
{
	DTO_INIT(CourseListQuery, DTO)

	DTO_FIELD(Int32, page, "page"); // 当前页码
	DTO_FIELD(Int32, size, "size"); // 每页大小
};

#include OATPP_CODEGEN_END(DTO)

#endif
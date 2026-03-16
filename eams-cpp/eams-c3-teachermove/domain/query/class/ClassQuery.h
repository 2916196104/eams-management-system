#ifndef __CLASS_QUERY_H__
#define __CLASS_QUERY_H__

#include "../../GlobalInclude.h"
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
	// 班级名（模糊）
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
	// 是否完结：0 未完结，1 已完结
	DTO_FIELD(String, be_over);
	DTO_FIELD_INFO(be_over) {
		info->description = ZH_WORDS_GETTER("class.beOver");
	}
};

#include OATPP_CODEGEN_END(DTO)

#endif
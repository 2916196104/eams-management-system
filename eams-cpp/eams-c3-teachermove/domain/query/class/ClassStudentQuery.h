#ifndef __CLASS_STUDENT_QUERY_H__
#define __CLASS_STUDENT_QUERY_H__

#include "domain/GlobalInclude.h"
#include "domain/query/PageQuery.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 班级学员列表查询参数
 */
class ClassStudentQuery : public PageQuery
{
	DTO_INIT(ClassStudentQuery, PageQuery);

	// 班级ID（必填）
	DTO_FIELD(String, class_id);
	DTO_FIELD_INFO(class_id) {
		info->description = ZH_WORDS_GETTER("classStudent.classId");
		info->required = true;
	}
	// 学员姓名（模糊）
	DTO_FIELD(String, student_name);
	DTO_FIELD_INFO(student_name) {
		info->description = ZH_WORDS_GETTER("classStudent.studentName");
	}
};

#include OATPP_CODEGEN_END(DTO)

#endif

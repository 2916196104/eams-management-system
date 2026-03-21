#pragma once
#ifndef _COURSERECORD_QUERY_H_
#define _COURSERECORD_QUERY_H_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 上课记录分页查询对象
 */
class CourseRecordQuery : public PageQuery
{
	DTO_INIT(CourseRecordQuery, PageQuery);

	// 学生ID
	DTO_FIELD(UInt64, student_id);
	DTO_FIELD_INFO(student_id) {
		info->description = ZH_WORDS_GETTER("CourseRecord.field.student_id");
	}

	// 课程ID
	DTO_FIELD(UInt64, course_id);
	DTO_FIELD_INFO(course_id) {
		info->description = ZH_WORDS_GETTER("CourseRecord.field.course_id");
	}
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_COURSERECORD_QUERY_H_

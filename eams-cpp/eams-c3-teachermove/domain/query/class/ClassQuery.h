#ifndef __CLASS_QUERY_H__
#define __CLASS_QUERY_H__

#include "domain/GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)



// 课程列表查询参数
class CourseListQuery : public oatpp::DTO
{
	DTO_INIT(CourseListQuery, DTO)

		DTO_FIELD(Int32, page, "page"); // 当前页码
	DTO_FIELD(Int32, size, "size"); // 每页大小
	DTO_FIELD(String, studentId, "studentId"); // 学员ID
};

#include OATPP_CODEGEN_END(DTO)

#endif
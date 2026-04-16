#pragma once
#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)


// 我的客户列表
class MyCustomersQuery : public PageQuery
{
	DTO_INIT(MyCustomersQuery, PageQuery);

	// 顾问ID
	DTO_FIELD(UInt64, counselor_id);
	DTO_FIELD_INFO(counselor_id) {
		info->description = u8"顾问ID";
	}

	// 学生姓名（搜索）
	DTO_FIELD(String, name);
	DTO_FIELD_INFO(name) {
		info->description = ZH_WORDS_GETTER("customer.query.name");
	}

	// 学生电话（搜索）
	DTO_FIELD(String, telephone);
	DTO_FIELD_INFO(telephone) {
		info->description = ZH_WORDS_GETTER("customer.query.telephone");
	}
};

//  学员详情查询（学生ID）
class StudentDetailQuery : public oatpp::DTO
{
	DTO_INIT(StudentDetailQuery, oatpp::DTO);

	DTO_FIELD(UInt64, student_id);
	DTO_FIELD_INFO(student_id) {
		info->description = ZH_WORDS_GETTER("student.query.detail.id");
	}
};

//  学员课程列表查询（学生ID）
class StudentCourseQuery : public PageQuery
{
	DTO_INIT(StudentCourseQuery, PageQuery);

	DTO_FIELD(UInt64, student_id);
	DTO_FIELD_INFO(student_id) {
		info->description = ZH_WORDS_GETTER("student.course.query.student_id");
	}
};

#include OATPP_CODEGEN_END(DTO)
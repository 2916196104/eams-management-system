#pragma once
#ifndef _CLASS_STUDENT_QUERY_H_
#define _CLASS_STUDENT_QUERY_H_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class ClassStudentQuery : public PageQuery
{
	DTO_INIT(ClassStudentQuery, PageQuery);
	API_DTO_FIELD_REQUIRE(UInt64, classId, ZH_WORDS_GETTER("class.field.classId"), true);
	API_DTO_FIELD_DEFAULT(String, keyword, ZH_WORDS_GETTER("class.field.keyword"));
};

class ClassStudentCourseQuery : public PageQuery
{
	DTO_INIT(ClassStudentCourseQuery, PageQuery);
	API_DTO_FIELD_REQUIRE(UInt64, classId, ZH_WORDS_GETTER("class.field.classId"), true);
	API_DTO_FIELD_REQUIRE(UInt64, studentId, ZH_WORDS_GETTER("class.field.studentId"), true);
	API_DTO_FIELD_DEFAULT(String, keyword, ZH_WORDS_GETTER("class.field.keyword"));
};

#include OATPP_CODEGEN_END(DTO)
#endif

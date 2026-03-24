#pragma once
#include "ApiHelper.h"
#include "oatpp/core/Types.hpp"
#ifndef _FINISH_STUDENT_DTO_H_
#define _FINISH_STUDENT_DTO_H_
#include "Macros.h"
#include "domain/GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)


class FinishStudentDTO : public oatpp::DTO
{
	DTO_INIT(FinishStudentDTO, DTO);

	API_DTO_FIELD_DEFAULT(Int64, id, ZH_WORDS_GETTER("finishstudent.field.finish-student-query.id"));
	API_DTO_FIELD_DEFAULT(String, studentName, ZH_WORDS_GETTER("finishstudent.field.finish-student-query.student-name"));
	API_DTO_FIELD_DEFAULT(String, parentName, ZH_WORDS_GETTER("finishstudent.field.finish-student-query.parent-name"));
	API_DTO_FIELD_DEFAULT(Int32, familyRel, ZH_WORDS_GETTER("finishstudent.field.finish-student-query.family-relation"));
	API_DTO_FIELD_DEFAULT(String, mobile, ZH_WORDS_GETTER("finishstudent.field.finish-student-query.mobile"));
	API_DTO_FIELD_DEFAULT(String, counselor, ZH_WORDS_GETTER("finishstudent.field.finish-student-query.counselor"));
	API_DTO_FIELD_DEFAULT(String, grade, ZH_WORDS_GETTER("finishstudent.field.finish-student-query.grade"));
	API_DTO_FIELD_DEFAULT(String, schoolName, ZH_WORDS_GETTER("finishstudent.field.finish-student-query.school-name"));
	API_DTO_FIELD_DEFAULT(Int32, lessonCount, ZH_WORDS_GETTER("finishstudent.field.finish-student-query.lesson-count"));
	API_DTO_FIELD_DEFAULT(Int32, points, ZH_WORDS_GETTER("finishstudent.field.finish-student-query.points"));
	API_DTO_FIELD_DEFAULT(Int32, gender, ZH_WORDS_GETTER("finishstudent.field.finish-student-query.gender"));
	API_DTO_FIELD_DEFAULT(Int32, age, ZH_WORDS_GETTER("finishstudent.field.finish-student-query.age"));
	API_DTO_FIELD_DEFAULT(String, remark, ZH_WORDS_GETTER("finishstudent.field.finish-student-query.remark"));
	API_DTO_FIELD_DEFAULT(String, graduationDate, ZH_WORDS_GETTER("finishstudent.field.finish-student-query.graduation-date"));
};

class FinishStudentImportDTO : public oatpp::DTO
{
	DTO_INIT(FinishStudentImportDTO, DTO);
	API_DTO_FIELD_REQUIRE(oatpp::swagger::Binary, excel, ZH_WORDS_GETTER("intendedstudent.field.excel"), true);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_FINISH_STUDENT_DTO_H_

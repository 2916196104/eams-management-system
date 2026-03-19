#pragma once
#include "ApiHelper.h"
#include "oatpp/core/Types.hpp"
#ifndef _FINISH_STUDENT_DTO_H_
#define _FINISH_STUDENT_DTO_H_
#include "Macros.h"
#include "domain/GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 结业学员查询DTO
 */
class FinishStudentDTO : public oatpp::DTO
{
	DTO_INIT(FinishStudentDTO, DTO);

	API_DTO_FIELD_DEFAULT(Int64, id, ZH_WORDS_GETTER("finishstudent.field.id"));
	API_DTO_FIELD_DEFAULT(String, studentName, ZH_WORDS_GETTER("finishstudent.field.student-name"));
	API_DTO_FIELD_DEFAULT(String, parentName, ZH_WORDS_GETTER("finishstudent.field.parent-name"));
	API_DTO_FIELD_DEFAULT(Int32, familyRel, ZH_WORDS_GETTER("finishstudent.field.family-relation"));
	API_DTO_FIELD_DEFAULT(String, mobile, ZH_WORDS_GETTER("finishstudent.field.mobile"));
	API_DTO_FIELD_DEFAULT(String, counselor, ZH_WORDS_GETTER("finishstudent.field.counselor"));
	API_DTO_FIELD_DEFAULT(String, grade, ZH_WORDS_GETTER("finishstudent.field.grade"));
	API_DTO_FIELD_DEFAULT(String, schoolName, ZH_WORDS_GETTER("finishstudent.field.school-name"));
	API_DTO_FIELD_DEFAULT(Int32, lessonCount, ZH_WORDS_GETTER("finishstudent.field.lesson-count"));
	API_DTO_FIELD_DEFAULT(Int32, points, ZH_WORDS_GETTER("finishstudent.field.points"));
	API_DTO_FIELD_DEFAULT(Int32, gender, ZH_WORDS_GETTER("finishstudent.field.gender"));
	API_DTO_FIELD_DEFAULT(Int32, age, ZH_WORDS_GETTER("finishstudent.field.age"));
	API_DTO_FIELD_DEFAULT(String, remark, ZH_WORDS_GETTER("finishstudent.field.remark"));
	API_DTO_FIELD_DEFAULT(String, graduationDate, ZH_WORDS_GETTER("finishstudent.field.graduation-date"));
//	API_DTO_FIELD_DEFAULT(String, graduationReason, ZH_WORDS_GETTER("finish_student.graduationReason"));
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_FINISH_STUDENT_DTO_H_

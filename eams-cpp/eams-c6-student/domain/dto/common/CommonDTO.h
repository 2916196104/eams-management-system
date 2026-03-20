#pragma once
#ifndef CommonDTO_h
#define CommonDTO_h
#include"../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)
class CourseCountDTO :public oatpp::DTO {
	DTO_INIT(CourseCountDTO, DTO);
	API_DTO_FIELD_DEFAULT(String, courseName, ZH_WORDS_GETTER("common.field.course.name"));
	API_DTO_FIELD_DEFAULT(Int32, totalCourseCount, ZH_WORDS_GETTER("common.field.course.total"));
	API_DTO_FIELD_DEFAULT(Int32, leftCourseCount, ZH_WORDS_GETTER("common.field.course.left"));
};
class SaveStudentDTO : public oatpp::DTO {
	DTO_INIT(SaveStudentDTO, DTO);
	API_DTO_FIELD_DEFAULT(String, phone, ZH_WORDS_GETTER("common.field.student.phone"));
	API_DTO_FIELD_DEFAULT(String, parentName, ZH_WORDS_GETTER("common.field.student.parent-name"));
	API_DTO_FIELD_DEFAULT(String, relationType, ZH_WORDS_GETTER("common.field.student.relation-type"));
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("common.field.student.name"));
	API_DTO_FIELD_DEFAULT(Int32, sex, ZH_WORDS_GETTER("common.field.student.sex"));
	API_DTO_FIELD_DEFAULT(String, enterTime, ZH_WORDS_GETTER("common.field.student.enter-time"));
	API_DTO_FIELD_DEFAULT(Int32, grade, ZH_WORDS_GETTER("common.field.student.grade"));
	API_DTO_FIELD_DEFAULT(String, birthday, ZH_WORDS_GETTER("common.field.student.birthday"));
	API_DTO_FIELD_DEFAULT(String, identificationNumber, ZH_WORDS_GETTER("common.field.student.identification-number"));
	API_DTO_FIELD_DEFAULT(Int32, source, ZH_WORDS_GETTER("common.field.student.source"));
	API_DTO_FIELD_DEFAULT(String, note, ZH_WORDS_GETTER("common.field.student.note"));
};
class SaveDTO :public SaveStudentDTO {
	DTO_INIT(SaveDTO, SaveStudentDTO);
	API_DTO_FIELD_DEFAULT(Int32, id, ZH_WORDS_GETTER("common.field.student.id"));
};
#include OATPP_CODEGEN_END(DTO)
#endif
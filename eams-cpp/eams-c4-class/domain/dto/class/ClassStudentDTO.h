#pragma once
#ifndef _CLASS_STUDENT_DTO_H_
#define _CLASS_STUDENT_DTO_H_

#include "../../GlobalInclude.h"
#include "domain/dto/PageDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class ClassStudentListDTO : public oatpp::DTO
{
	DTO_INIT(ClassStudentListDTO, DTO);
	API_DTO_FIELD_REQUIRE(UInt64, id, ZH_WORDS_GETTER("class.student.list.field.id"), true);
	API_DTO_FIELD_REQUIRE(UInt64, classId, ZH_WORDS_GETTER("class.student.list.field.classId"), true);
	API_DTO_FIELD_REQUIRE(UInt64, studentId, ZH_WORDS_GETTER("class.student.list.field.studentId"), true);
	API_DTO_FIELD_DEFAULT(String, studentName, ZH_WORDS_GETTER("class.student.list.field.studentName"));
	API_DTO_FIELD_DEFAULT(Int32, gender, ZH_WORDS_GETTER("class.student.list.field.gender"));
	API_DTO_FIELD_DEFAULT(String, headImg, ZH_WORDS_GETTER("class.student.list.field.headImg"));
	API_DTO_FIELD_DEFAULT(UInt64, consumeCourseId, ZH_WORDS_GETTER("class.student.list.field.consumeCourseId"));
	API_DTO_FIELD_DEFAULT(Int32, countLessonRemaining, ZH_WORDS_GETTER("class.student.list.field.countLessonRemaining"));
};

class ClassStudentDetailDTO : public oatpp::DTO
{
	DTO_INIT(ClassStudentDetailDTO, DTO);
	API_DTO_FIELD_REQUIRE(UInt64, id, ZH_WORDS_GETTER("class.student.detail.field.id"), true);
	API_DTO_FIELD_REQUIRE(UInt64, classId, ZH_WORDS_GETTER("class.student.detail.field.classId"), true);
	API_DTO_FIELD_REQUIRE(UInt64, studentId, ZH_WORDS_GETTER("class.student.detail.field.studentId"), true);
	API_DTO_FIELD_DEFAULT(UInt64, consumeCourseId, ZH_WORDS_GETTER("class.student.detail.field.consumeCourseId"));
	API_DTO_FIELD_DEFAULT(UInt64, userId, ZH_WORDS_GETTER("class.student.detail.field.userId"));
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("class.student.detail.field.name"));
	API_DTO_FIELD_DEFAULT(String, mobile, ZH_WORDS_GETTER("class.student.detail.field.mobile"));
	API_DTO_FIELD_DEFAULT(Int32, gender, ZH_WORDS_GETTER("class.student.detail.field.gender"));
	API_DTO_FIELD_DEFAULT(String, birthday, ZH_WORDS_GETTER("class.student.detail.field.birthday"));
	API_DTO_FIELD_DEFAULT(Int32, age, ZH_WORDS_GETTER("class.student.detail.field.age"));
	API_DTO_FIELD_DEFAULT(Int32, stage, ZH_WORDS_GETTER("class.student.detail.field.stage"));
	API_DTO_FIELD_DEFAULT(String, headImg, ZH_WORDS_GETTER("class.student.detail.field.headImg"));
	API_DTO_FIELD_DEFAULT(String, remark, ZH_WORDS_GETTER("class.student.detail.field.remark"));
	API_DTO_FIELD_DEFAULT(String, classStudentRemark, ZH_WORDS_GETTER("class.student.detail.field.classStudentRemark"));
};

class ClassStudentListPageDTO : public PageDTO<ClassStudentListDTO::Wrapper>
{
	DTO_INIT(ClassStudentListPageDTO, PageDTO<ClassStudentListDTO::Wrapper>);
};

class ClassStudentCourseDTO : public oatpp::DTO
{
	DTO_INIT(ClassStudentCourseDTO, DTO);
	API_DTO_FIELD_REQUIRE(UInt64, id, ZH_WORDS_GETTER("class.student.course.field.id"), true);
	API_DTO_FIELD_REQUIRE(UInt64, studentId, ZH_WORDS_GETTER("class.student.course.field.studentId"), true);
	API_DTO_FIELD_REQUIRE(UInt64, courseId, ZH_WORDS_GETTER("class.student.course.field.courseId"), true);
	API_DTO_FIELD_DEFAULT(String, courseName, ZH_WORDS_GETTER("class.student.course.field.courseName"));
	API_DTO_FIELD_DEFAULT(UInt64, subjectId, ZH_WORDS_GETTER("class.student.course.field.subjectId"));
	API_DTO_FIELD_DEFAULT(String, subjectName, ZH_WORDS_GETTER("class.student.course.field.subjectName"));
	API_DTO_FIELD_DEFAULT(String, startDate, ZH_WORDS_GETTER("class.student.course.field.startDate"));
	API_DTO_FIELD_DEFAULT(String, expireDate, ZH_WORDS_GETTER("class.student.course.field.expireDate"));
	API_DTO_FIELD_DEFAULT(Int32, countLessonTotal, ZH_WORDS_GETTER("class.student.course.field.countLessonTotal"));
	API_DTO_FIELD_DEFAULT(Int32, countLessonComplete, ZH_WORDS_GETTER("class.student.course.field.countLessonComplete"));
	API_DTO_FIELD_DEFAULT(Int32, countLessonRefund, ZH_WORDS_GETTER("class.student.course.field.countLessonRefund"));
	API_DTO_FIELD_DEFAULT(Int32, countLessonRemaining, ZH_WORDS_GETTER("class.student.course.field.countLessonRemaining"));
	API_DTO_FIELD_DEFAULT(String, progress, ZH_WORDS_GETTER("class.student.course.field.progress"));
	API_DTO_FIELD_DEFAULT(Int32, defaultConsumeCourse, ZH_WORDS_GETTER("class.student.course.field.defaultConsumeCourse"));
};

class ClassStudentCoursePageDTO : public PageDTO<ClassStudentCourseDTO::Wrapper>
{
	DTO_INIT(ClassStudentCoursePageDTO, PageDTO<ClassStudentCourseDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif

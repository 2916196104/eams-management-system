#pragma once
#ifndef _CLASS_STUDENT_DTO_H_
#define _CLASS_STUDENT_DTO_H_

#include "../../GlobalInclude.h"
#include "domain/dto/PageDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class ClassStudentDTO : public oatpp::DTO
{
	DTO_INIT(ClassStudentDTO, DTO);
	API_DTO_FIELD_REQUIRE(UInt64, id, ZH_WORDS_GETTER("class.student.field.id"), true);
	API_DTO_FIELD_REQUIRE(UInt64, classId, ZH_WORDS_GETTER("class.student.field.classId"), true);
	API_DTO_FIELD_REQUIRE(UInt64, studentId, ZH_WORDS_GETTER("class.student.field.studentId"), true);
	API_DTO_FIELD_DEFAULT(UInt64, consumeCourseId, ZH_WORDS_GETTER("class.student.field.consumeCourseId"));
	API_DTO_FIELD_DEFAULT(Int32, reason, ZH_WORDS_GETTER("class.student.field.reason"));
	API_DTO_FIELD_DEFAULT(String, addTime, ZH_WORDS_GETTER("class.student.field.addTime"));
	API_DTO_FIELD_DEFAULT(String, classStudentRemark, ZH_WORDS_GETTER("class.student.field.classStudentRemark"));
	API_DTO_FIELD_DEFAULT(String, studentName, ZH_WORDS_GETTER("class.student.field.studentName"));
	API_DTO_FIELD_DEFAULT(Int32, familyRel, ZH_WORDS_GETTER("class.student.field.familyRel"));
	API_DTO_FIELD_DEFAULT(Int32, stage, ZH_WORDS_GETTER("class.student.field.stage"));
	API_DTO_FIELD_DEFAULT(Int32, gender, ZH_WORDS_GETTER("class.student.field.gender"));
	API_DTO_FIELD_DEFAULT(String, birthday, ZH_WORDS_GETTER("class.student.field.birthday"));
	API_DTO_FIELD_DEFAULT(String, headImg, ZH_WORDS_GETTER("class.student.field.headImg"));
	API_DTO_FIELD_DEFAULT(UInt64, userId, ZH_WORDS_GETTER("class.student.field.userId"));
	API_DTO_FIELD_DEFAULT(String, parentName, ZH_WORDS_GETTER("class.student.field.parentName"));
	API_DTO_FIELD_DEFAULT(String, mobile, ZH_WORDS_GETTER("class.student.field.mobile"));
	API_DTO_FIELD_DEFAULT(String, studentRemark, ZH_WORDS_GETTER("class.student.field.studentRemark"));
	API_DTO_FIELD_DEFAULT(Int32, countLessonRemaining, ZH_WORDS_GETTER("class.student.field.countLessonRemaining"));
};

class ClassStudentDetailDTO : public ClassStudentDTO
{
	DTO_INIT(ClassStudentDetailDTO, ClassStudentDTO);
	API_DTO_FIELD_DEFAULT(String, className, ZH_WORDS_GETTER("class.student.field.className"));
	API_DTO_FIELD_DEFAULT(UInt64, classCourseId, ZH_WORDS_GETTER("class.student.field.classCourseId"));
	API_DTO_FIELD_DEFAULT(String, classCourseName, ZH_WORDS_GETTER("class.student.field.classCourseName"));
	API_DTO_FIELD_DEFAULT(UInt64, gradeId, ZH_WORDS_GETTER("class.student.field.gradeId"));
	API_DTO_FIELD_DEFAULT(String, gradeName, ZH_WORDS_GETTER("class.student.field.gradeName"));
};

class ClassStudentPageDTO : public PageDTO<ClassStudentDTO::Wrapper>
{
	DTO_INIT(ClassStudentPageDTO, PageDTO<ClassStudentDTO::Wrapper>);
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
	API_DTO_FIELD_DEFAULT(String, remark, ZH_WORDS_GETTER("class.student.course.field.remark"));
	API_DTO_FIELD_DEFAULT(Int32, countLessonTotal, ZH_WORDS_GETTER("class.student.course.field.countLessonTotal"));
	API_DTO_FIELD_DEFAULT(Int32, countLessonComplete, ZH_WORDS_GETTER("class.student.course.field.countLessonComplete"));
	API_DTO_FIELD_DEFAULT(Int32, countLessonRefund, ZH_WORDS_GETTER("class.student.course.field.countLessonRefund"));
	API_DTO_FIELD_DEFAULT(Int32, countLessonRemaining, ZH_WORDS_GETTER("class.student.course.field.countLessonRemaining"));
	API_DTO_FIELD_DEFAULT(Float64, courseAmount, ZH_WORDS_GETTER("class.student.course.field.courseAmount"));
	API_DTO_FIELD_DEFAULT(Float64, discountAmount, ZH_WORDS_GETTER("class.student.course.field.discountAmount"));
	API_DTO_FIELD_DEFAULT(Float64, amount, ZH_WORDS_GETTER("class.student.course.field.amount"));
	API_DTO_FIELD_DEFAULT(Float64, paidAmount, ZH_WORDS_GETTER("class.student.course.field.paidAmount"));
	API_DTO_FIELD_DEFAULT(Int32, payOff, ZH_WORDS_GETTER("class.student.course.field.payOff"));
	API_DTO_FIELD_DEFAULT(UInt64, operatorId, ZH_WORDS_GETTER("class.student.course.field.operatorId"));
	API_DTO_FIELD_DEFAULT(UInt64, creator, ZH_WORDS_GETTER("class.student.course.field.creator"));
	API_DTO_FIELD_DEFAULT(String, addTime, ZH_WORDS_GETTER("class.student.course.field.addTime"));
	API_DTO_FIELD_DEFAULT(UInt64, editor, ZH_WORDS_GETTER("class.student.course.field.editor"));
	API_DTO_FIELD_DEFAULT(String, editTime, ZH_WORDS_GETTER("class.student.course.field.editTime"));
	API_DTO_FIELD_DEFAULT(Int32, verifyState, ZH_WORDS_GETTER("class.student.course.field.verifyState"));
	API_DTO_FIELD_DEFAULT(Int32, warningTimes, ZH_WORDS_GETTER("class.student.course.field.warningTimes"));
	API_DTO_FIELD_DEFAULT(Int32, priority, ZH_WORDS_GETTER("class.student.course.field.priority"));
	API_DTO_FIELD_DEFAULT(Float64, unitPrice, ZH_WORDS_GETTER("class.student.course.field.unitPrice"));
	API_DTO_FIELD_DEFAULT(Int32, fromTrial, ZH_WORDS_GETTER("class.student.course.field.fromTrial"));
	API_DTO_FIELD_DEFAULT(UInt64, orgId, ZH_WORDS_GETTER("class.student.course.field.orgId"));
	API_DTO_FIELD_DEFAULT(Int32, defaultConsumeCourse, ZH_WORDS_GETTER("class.student.course.field.defaultConsumeCourse"));
};

class ClassStudentCoursePageDTO : public PageDTO<ClassStudentCourseDTO::Wrapper>
{
	DTO_INIT(ClassStudentCoursePageDTO, PageDTO<ClassStudentCourseDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif

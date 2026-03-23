#pragma once
#ifndef _CLASS_STUDENT_DO_H_
#define _CLASS_STUDENT_DO_H_

#include <cstdint>
#include "../DoInclude.h"

class ClassStudentDO
{
	CC_SYNTHESIZE(uint64_t, id, Id);
	CC_SYNTHESIZE(uint64_t, classId, ClassId);
	CC_SYNTHESIZE(uint64_t, studentId, StudentId);
	CC_SYNTHESIZE(uint64_t, consumeCourseId, ConsumeCourseId);
	CC_SYNTHESIZE(int, reason, Reason);
	CC_SYNTHESIZE(string, addTime, AddTime);
	CC_SYNTHESIZE(string, classStudentRemark, ClassStudentRemark);

	CC_SYNTHESIZE(string, className, ClassName);
	CC_SYNTHESIZE(uint64_t, classCourseId, ClassCourseId);
	CC_SYNTHESIZE(string, classCourseName, ClassCourseName);
	CC_SYNTHESIZE(uint64_t, gradeId, GradeId);
	CC_SYNTHESIZE(string, gradeName, GradeName);

	CC_SYNTHESIZE(uint64_t, userId, UserId);
	CC_SYNTHESIZE(string, parentName, ParentName);
	CC_SYNTHESIZE(string, mobile, Mobile);

	CC_SYNTHESIZE(int, familyRel, FamilyRel);
	CC_SYNTHESIZE(string, studentName, StudentName);
	CC_SYNTHESIZE(int, stage, Stage);
	CC_SYNTHESIZE(int, gender, Gender);
	CC_SYNTHESIZE(string, birthday, Birthday);
	CC_SYNTHESIZE(string, headImg, HeadImg);
	CC_SYNTHESIZE(string, studentRemark, StudentRemark);

	CC_SYNTHESIZE(int, countLessonRemaining, CountLessonRemaining);
};

typedef std::shared_ptr<ClassStudentDO> PtrClassStudentDO;

class ClassStudentCourseDO
{
	CC_SYNTHESIZE(uint64_t, id, Id);
	CC_SYNTHESIZE(uint64_t, studentId, StudentId);
	CC_SYNTHESIZE(uint64_t, courseId, CourseId);
	CC_SYNTHESIZE(string, courseName, CourseName);
	CC_SYNTHESIZE(uint64_t, subjectId, SubjectId);
	CC_SYNTHESIZE(string, subjectName, SubjectName);
	CC_SYNTHESIZE(string, startDate, StartDate);
	CC_SYNTHESIZE(string, expireDate, ExpireDate);
	CC_SYNTHESIZE(string, remark, Remark);
	CC_SYNTHESIZE(int, countLessonTotal, CountLessonTotal);
	CC_SYNTHESIZE(int, countLessonComplete, CountLessonComplete);
	CC_SYNTHESIZE(int, countLessonRefund, CountLessonRefund);
	CC_SYNTHESIZE(int, countLessonRemaining, CountLessonRemaining);
	CC_SYNTHESIZE(double, courseAmount, CourseAmount);
	CC_SYNTHESIZE(double, discountAmount, DiscountAmount);
	CC_SYNTHESIZE(double, amount, Amount);
	CC_SYNTHESIZE(double, paidAmount, PaidAmount);
	CC_SYNTHESIZE(int, payOff, PayOff);
	CC_SYNTHESIZE(uint64_t, operatorId, OperatorId);
	CC_SYNTHESIZE(uint64_t, creator, Creator);
	CC_SYNTHESIZE(string, addTime, AddTime);
	CC_SYNTHESIZE(uint64_t, editor, Editor);
	CC_SYNTHESIZE(string, editTime, EditTime);
	CC_SYNTHESIZE(int, verifyState, VerifyState);
	CC_SYNTHESIZE(int, warningTimes, WarningTimes);
	CC_SYNTHESIZE(int, priority, Priority);
	CC_SYNTHESIZE(double, unitPrice, UnitPrice);
	CC_SYNTHESIZE(int, fromTrial, FromTrial);
	CC_SYNTHESIZE(uint64_t, orgId, OrgId);
	CC_SYNTHESIZE(int, defaultConsumeCourse, DefaultConsumeCourse);
};

typedef std::shared_ptr<ClassStudentCourseDO> PtrClassStudentCourseDO;

#endif

#pragma once
#ifndef _STUDENT_COURSE_VIEW_DO_
#define _STUDENT_COURSE_VIEW_DO_
#include "../eams-c7-workbench/domain/do/DoInclude.h"

/**
 * 课程进度 视图DO (对应 CourseProgressDTO)
 * 联表查询专用，无真实数据库表
 */
class CourseProgressViewDO
{
	// 课程名称（联表 course 表）
	MYSQL_SYNTHESIZE(string, courseName, CourseName);
	// 课程状态
	MYSQL_SYNTHESIZE(string, courseStatus, CourseStatus);
	// 课程总数
	MYSQL_SYNTHESIZE(int32_t, courseSum, CourseSum);
	// 已完成数
	MYSQL_SYNTHESIZE(int32_t, finishedSum, FinishedSum);
	// 未完成数（计算字段：总数-已完成）
	MYSQL_SYNTHESIZE(int32_t, unfinishedSum, UnfinishedSum);

public:
	CourseProgressViewDO() = default;
};
typedef std::shared_ptr<CourseProgressViewDO> PtrCourseProgressViewDO;

/**
 * 课时记录 视图DO (对应 CourseRecordDTO)
 */
class CourseRecordViewDO
{
	// 课程名称
	MYSQL_SYNTHESIZE(string, courseName, CourseName);
	// 课程状态
	MYSQL_SYNTHESIZE(string, courseStatus, CourseStatus);
	// 消课数（已完成）
	MYSQL_SYNTHESIZE(int32_t, consumeCourseNum, ConsumeCourseNum);
	// 剩余课时
	MYSQL_SYNTHESIZE(int32_t, courseBalance, CourseBalance);

public:
	CourseRecordViewDO() = default;
};
typedef std::shared_ptr<CourseRecordViewDO> PtrCourseRecordViewDO;

/**
 * 学员报名 视图DO (对应 StudentSighnUPDTO)
 */
class StudentSignUpViewDO
{
	// 课程名称
	MYSQL_SYNTHESIZE(string, courseName, CourseName);
	// 报名时间
	MYSQL_SYNTHESIZE(string, signUpTime, SignUpTime);
	// 购买课程数
	MYSQL_SYNTHESIZE(int32_t, buyCourseSum, BuyCourseSum);
	// 支付费用
	MYSQL_SYNTHESIZE(double, payAmount, PayAmount);

public:
	StudentSignUpViewDO() = default;
};
typedef std::shared_ptr<StudentSignUpViewDO> PtrStudentSignUpViewDO;

#endif // !_STUDENT_COURSE_VIEW_DO_
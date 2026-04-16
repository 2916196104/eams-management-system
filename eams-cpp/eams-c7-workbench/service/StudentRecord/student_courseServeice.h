#pragma once
#ifndef _STUDENT_COURSE_SERVICE_
#define _STUDENT_COURSE_SERVICE_
#include "../../domain/query/StudentRecord/studentinformation.h"
#include "../../domain/dto/StudentRecord/student_courseDTO.h"
#include "../../dao/StudentRecord/student_courseDAO.h"

/**
 * 学生课程表服务实现，分页查询服务实现
 */
class StudentCourseService
{
public:
	// 分页查询所有数据
	CourseProgressPageDTO::Wrapper listAllCourseProgress(const StudentQuery::Wrapper& query);
	StudentSighnUPPageDTO::Wrapper listAllStudentSighnUP(const StudentQuery::Wrapper& query);
	CourseRecordPageDTO::Wrapper listAllCourseRecord(const StudentQuery::Wrapper& query);
	
};

#endif // !_SAMPLE_SERVICE_


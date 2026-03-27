#pragma once

#ifndef _CLASS_SERVICE_H_
#define _CLASS_SERVICE_H_

#include "domain/dto/class/ClassDTO.h"
#include "domain/dto/class/ClassDetailDTO.h"
#include "domain/vo/class/ClassVO.h"
#include "domain/GlobalInclude.h"
#include "domain/query/class/ClassQuery.h"

#include "domain/dto/class/ClassStudentDTO.h"
class ClassService {
public:
	// 获取班级学员详情
	oatpp::Object<StudentDetailDTO> getStudentDetail(const oatpp::String& studentId);
	oatpp::Object<ClassPageDTO> getClassList(const ClassQuery::Wrapper& query);
	oatpp::Object<ClassDetailDTO> getClassDetail(const oatpp::String& classId);
	oatpp::Object<ClassStudentListPageDTO> getClassStudentList(const oatpp::String& classId);
	// 获取班级学员课程列表（分页）
	CoursePageJsonVO::Wrapper getStudentCourseList(const oatpp::String& studentId, const oatpp::String& pageIndex, const oatpp::String& pageSize, const PayloadDTO& payload);
};

#endif // !_CLASS_SERVICE_H_

#pragma once

#ifndef _CLASS_SERVICE_H_
#define _CLASS_SERVICE_H_

#include "domain/dto/class/ClassDTO.h"
#include "domain/vo/class/ClassVO.h"
#include "domain/GlobalInclude.h"

class ClassService {
public:
	// 获取班级学员详情
	oatpp::Object<StudentDetailDTO> getStudentDetail(const oatpp::String& studentId);
	
	// 获取班级学员课程列表（分页）
	CoursePageJsonVO::Wrapper getStudentCourseList(const oatpp::String& studentId, const oatpp::String& pageIndex, const oatpp::String& pageSize, const PayloadDTO& payload);
};

#endif // !_CLASS_SERVICE_H_

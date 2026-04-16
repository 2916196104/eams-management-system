#include "stdafx.h"
#include "ClassController.h"

// 执行获取班级学员详情
StudentDetailJsonVO::Wrapper ClassController::execGetStudentDetail(const oatpp::String& studentId) {
	// 调用服务层获取学员详情
	auto studentDetail = classService.getStudentDetail(studentId);
	
	// 创建响应VO
	auto response = StudentDetailJsonVO::createShared();
	response->data = studentDetail;
	response->code = 0;
	response->message = "success";
	
	return response;
}

// 执行获取班级学员课程列表
CoursePageJsonVO::Wrapper ClassController::execGetStudentCourseList(const oatpp::String& studentId, const oatpp::String& pageIndex, const oatpp::String& pageSize, const PayloadDTO& payload) {
	// 调用服务层获取课程列表
	return classService.getStudentCourseList(studentId, pageIndex, pageSize, payload);
}
#include "stdafx.h"
#include "ClassController.h"


// 执行获取班级学员详情
oatpp::Object<StudentDetailDTO> ClassController::execGetStudentDetail(const oatpp::String& studentId) {
	// 这里可以根据 studentId 查询学员详情
	auto dto = StudentDetailDTO::createShared();
	return dto;
}

// 执行获取班级学员课程列表
CoursePageJsonVO::Wrapper ClassController::execGetStudentCourseList(const oatpp::String& studentId, const oatpp::String& pageIndex, const oatpp::String& pageSize, const PayloadDTO& payload) {
	// 创建并返回课程分页JSON VO
	auto response = CoursePageJsonVO::createShared();
	response->data = CoursePageDTO::createShared();
	response->code = 0;
	response->message = "success";
	
	return response;
}
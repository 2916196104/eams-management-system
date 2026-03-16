#include "stdafx.h"
#include "ClassController.h"


// 执行获取班级学员详情
oatpp::Object<StudentDetailDTO> ClassController::execGetStudentDetail(const oatpp::String& studentId) {
	// 创建并返回空的学员详情DTO
	return StudentDetailDTO::createShared();
}

// 执行获取班级学员课程列表
oatpp::Object<CourseListResponseDTO> ClassController::execGetStudentCourseList(const oatpp::Object<CourseListQuery>& query, const PayloadDTO& payload) {
	// 创建并返回空的课程列表响应DTO
	return CourseListResponseDTO::createShared();
}
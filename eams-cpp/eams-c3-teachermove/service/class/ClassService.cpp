#include "stdafx.h"
#include "ClassService.h"

// 获取班级学员详情
oatpp::Object<StudentDetailDTO> ClassService::getStudentDetail(const oatpp::String& studentId) {
	// 创建学员详情DTO
	auto studentDetail = StudentDetailDTO::createShared();
	
	// 模拟数据
	studentDetail->name = "张三";
	studentDetail->phone = "13800138000";
	studentDetail->birthday = "2008-01-01";
	
	return studentDetail;
}

// 获取班级学员课程列表（分页）
CoursePageJsonVO::Wrapper ClassService::getStudentCourseList(const oatpp::String& studentId, const oatpp::String& pageIndex, const oatpp::String& pageSize, const PayloadDTO& payload) {
	// 创建课程分页DTO
	auto coursePage = CoursePageDTO::createShared();
	
	// 设置分页信息
	coursePage->pageIndex = pageIndex ? std::stoi(pageIndex->c_str()) : 1;
	coursePage->pageSize = pageSize ? std::stoi(pageSize->c_str()) : 10;
	coursePage->total = 2;
	
	// 计算总页数
	coursePage->calcPages();
	
	// 创建课程列表
	auto courseList = oatpp::List<oatpp::Object<CourseInfoDTO>>::createShared();
	
	// 添加课程1
	auto course1 = CourseInfoDTO::createShared();
	course1->courseName = "数学";
	course1->progress = "80%";
	course1->validityPeriod = "2026-01-01 至 2026-12-31";
	course1->remainingCount = 10;
	courseList->push_back(course1);
	
	// 添加课程2
	auto course2 = CourseInfoDTO::createShared();
	course2->courseName = "英语";
	course2->progress = "60%";
	course2->validityPeriod = "2026-01-01 至 2026-12-31";
	course2->remainingCount = 15;
	courseList->push_back(course2);
	
	// 设置课程列表
	coursePage->rows = courseList;
	
	// 创建响应VO
	auto response = CoursePageJsonVO::createShared();
	response->data = coursePage;
	response->code = 0;
	response->message = "success";
	
	return response;
}

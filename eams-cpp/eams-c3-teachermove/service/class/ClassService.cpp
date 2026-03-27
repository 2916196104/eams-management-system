#include "stdafx.h"
#include "ClassService.h"
#include "dao/class/ClassDao.h"
#include "dao/staff/StaffDao.h"
#include "dao/course/CourseDao.h"
#include "dao/class_student/ClassStudentDao.h"

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

oatpp::Object<ClassPageDTO> ClassService::getClassList(const ClassQuery::Wrapper& query)
{
	ClassDao classDao;
	StaffDao staffDao;
	CourseDao courseDao;
	ClassStudentDAO classStudentDao;

	auto page = ClassPageDTO::createShared();

	v_uint64 pageIndex = query && query->pageIndex ? query->pageIndex.getValue(1) : static_cast<v_uint64>(1);
	v_uint64 pageSize = query && query->pageSize ? query->pageSize.getValue(10) : static_cast<v_uint64>(10);
	if (pageIndex == 0) pageIndex = 1;
	if (pageSize == 0) pageSize = 10;
	page->pageIndex = pageIndex;
	page->pageSize = pageSize;

	const uint64_t total = classDao.count(query);
	page->total = static_cast<v_int64>(total);

	auto rows = oatpp::List<oatpp::Object<ClassDTO>>::createShared();
	auto classList = classDao.selectWithPage(query);
	for (const auto& classItem : classList)
	{
		auto dto = ClassDTO::createShared();
		dto->classNo = std::to_string(classItem.getId());
		dto->className = classItem.getName();
		dto->startTime = classItem.getStartDate();
		dto->endTime = classItem.getEndDate();

		dto->teacherName = "";
		if (classItem.getTeacherIdPtr())
		{
			auto staff = staffDao.selectById(static_cast<uint64_t>(classItem.getTeacherId()));
			if (staff && staff->getNamePtr())
			{
				dto->teacherName = staff->getName();
			}
		}

		dto->courseName = "";
		if (classItem.getCourseIdPtr())
		{
			auto course = courseDao.selectById(static_cast<uint64_t>(classItem.getCourseId()));
			if (course && course->getNamePtr())
			{
				dto->courseName = course->getName();
			}
		}

		const uint64_t joinedCount = classStudentDao.countByClassId(classItem.getId());
		const int32_t plannedCount = classItem.getPlannedStudentCountPtr() ? classItem.getPlannedStudentCount() : 0;
		dto->participantCount = std::to_string(joinedCount) + "/" + std::to_string(plannedCount);

		rows->push_back(dto);
	}
	page->rows = rows;
	page->calcPages();

	return page;
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

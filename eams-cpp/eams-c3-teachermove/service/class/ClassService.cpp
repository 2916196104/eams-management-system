#include "stdafx.h"
#include "ClassService.h"
#include "dao/class/ClassDao.h"
#include "dao/staff/StaffDao.h"
#include "dao/course/CourseDao.h"
#include "dao/classroom/ClassroomDao.h"
#include "dao/class_student/ClassStudentDao.h"
#include "dao/lesson/LessonDao.h"
#include "dao/lesson/LessonStudentDao.h"

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

oatpp::Object<ClassDetailDTO> ClassService::getClassDetail(const oatpp::String& classId)
{
	auto detail = ClassDetailDTO::createShared();
	if (!classId || classId->empty())
	{
		return detail;
	}

	ClassDao classDao;
	StaffDao staffDao;
	ClassroomDao classroomDao;
	CourseDao courseDao;
	LessonDAO lessonDao;
	ClassStudentDAO classStudentDao;

	uint64_t id = 0;
	try
	{
		id = static_cast<uint64_t>(std::stoull(classId->c_str()));
	}
	catch (...)
	{
		return detail;
	}
	auto classData = classDao.selectById(id);
	if (!classData)
	{
		return detail;
	}

	detail->classId = static_cast<v_int64>(classData->getId());
	detail->className = classData->getName();
	detail->startDate = classData->getStartDate();
	detail->endDate = classData->getEndDate();
	detail->remark = classData->getRemark();
	detail->classStatus = classData->getBeOver()
		? ZH_WORDS_GETTER("class.status.finished")
		: ZH_WORDS_GETTER("class.status.ongoing");

	detail->teacherName = "";
	if (classData->getTeacherIdPtr())
	{
		auto staff = staffDao.selectById(static_cast<uint64_t>(classData->getTeacherId()));
		if (staff && staff->getNamePtr())
		{
			detail->teacherName = staff->getName();
		}
	}

	detail->classroomName = "";
	if (classData->getClassroomIdPtr())
	{
		auto classroom = classroomDao.selectById(static_cast<uint64_t>(classData->getClassroomId()));
		if (classroom && classroom->getNamePtr())
		{
			detail->classroomName = classroom->getName();
		}
	}

	detail->courseName = "";
	if (classData->getCourseIdPtr())
	{
		auto course = courseDao.selectById(static_cast<uint64_t>(classData->getCourseId()));
		if (course && course->getNamePtr())
		{
			detail->courseName = course->getName();
		}
	}

	const uint64_t finishedDecCount = lessonDao.sumFinishedDecCountByClassId(id);
	const int32_t plannedLessonCount = classData->getPlannedLessonCountPtr() ? classData->getPlannedLessonCount() : 0;
	detail->courseProgress = std::to_string(finishedDecCount) + "/" + std::to_string(plannedLessonCount);

	const uint64_t enrolledCount = classStudentDao.countByClassId(id);
	const int32_t plannedStudentCount = classData->getPlannedStudentCountPtr() ? classData->getPlannedStudentCount() : 0;
	detail->enrollmentProgress = std::to_string(enrolledCount) + "/" + std::to_string(plannedStudentCount);

	return detail;
}

oatpp::Object<ClassStudentListPageDTO> ClassService::getClassStudentList(const oatpp::String& classId)
{
	auto page = ClassStudentListPageDTO::createShared();
	page->pageIndex = 1;
	page->pageSize = 10;

	if (!classId || classId->empty())
	{
		return page;
	}

	uint64_t id = 0;
	try
	{
		id = static_cast<uint64_t>(std::stoull(classId->c_str()));
	}
	catch (...)
	{
		return page;
	}

	ClassDao classDao;
	ClassStudentDAO classStudentDao;
	LessonStudentDao lessonStudentDao;

	auto classData = classDao.selectById(id);
	if (!classData)
	{
		return page;
	}

	const int32_t plannedLessonCount = classData->getPlannedLessonCountPtr() ? classData->getPlannedLessonCount() : 0;
	const uint64_t total = classStudentDao.countByClassId(id);
	page->total = static_cast<v_int64>(total);

	auto rows = oatpp::List<ClassStudentListDTO::Wrapper>::createShared();
	auto students = classStudentDao.selectStudentBaseWithPage(id, page->pageIndex.getValue(1), page->pageSize.getValue(10));
	for (const auto& one : students)
	{
		auto dto = ClassStudentListDTO::createShared();
		dto->studentId = one.studentId;
		dto->studentName = one.studentName;
		dto->gender = one.gender;

		const uint64_t usedLessonCount = lessonStudentDao.sumLessonCountByClassAndStudent(id, one.studentId);
		dto->remaining = plannedLessonCount - static_cast<int32_t>(usedLessonCount);
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

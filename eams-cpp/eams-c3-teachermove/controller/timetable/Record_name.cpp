#include "stdafx.h"
#include "Record_name.h"

// Endpoint 1: Implementation of Get Student List (with conditions + pagination)
TimetableStudentPageJsonVO::Wrapper Record_name::execGetStuList(const StuListQuery::Wrapper& query, const PayloadDTO& payload)
{
	// 1. Create outer response object VO
	auto jvo = TimetableStudentPageJsonVO::createShared();

	// 2. Create pagination data container PageDTO (Note: ::Wrapper is required here)
	auto pages = PageDTO<TimetableStudentDTO::Wrapper>::createShared();

	pages->pageIndex = query->pageIndex ? query->pageIndex : 1;
	pages->pageSize = query->pageSize ? query->pageSize : 10;
	pages->total = 2; // Simulate a total of 2 records
	pages->calcPages(); // Calculate pagination data such as total pages

	// 3. Generate mock data 1
	auto stu1 = TimetableStudentDTO::createShared();
	stu1->id = "10001";
	stu1->name = "111";
	stu1->gender = "1";
	stu1->phone = "13903139008";
	stu1->rest_hour = 108;
	pages->addData(stu1);

	// 4. Generate mock data 2
	auto stu2 = TimetableStudentDTO::createShared();
	stu2->id = "10002";
	stu2->name = "222";
	stu2->gender = "1";
	stu2->phone = "15801062139";
	stu2->rest_hour = 107;
	pages->addData(stu2);

	// 5. Success response
	jvo->success(pages);
	return jvo;
}

// Endpoint 2: Implementation of Add Student to Lesson
StringJsonVO::Wrapper Record_name::execInsertStuToCS(const AddStudentToLessonDTO::Wrapper& dto, const PayloadDTO& payload)
{
	auto jvo = StringJsonVO::createShared();

	if (!dto->course_id || !dto->studentIds || dto->studentIds->size() == 0) {
		jvo->code = 500;
		jvo->message = ZH_WORDS_GETTER("timetable.message.paramIncomplete");
		return jvo;
	}

	// Simulate successful save, return success message
	jvo->success("successAdd");
	return jvo;
}

// Endpoint 3: Implementation of Get Student Course List
ListJsonVO<TimetableStudentCourseDTO::Wrapper>::Wrapper Record_name::execGetStuClassList(const StuClassQuery::Wrapper& query, const PayloadDTO& payload)
{
	auto jvo = ListJsonVO<TimetableStudentCourseDTO::Wrapper>::createShared();

	// 1. Validate parameters
	if (!query->id) {

		jvo->code = 500;
		jvo->message = ZH_WORDS_GETTER("timetable.message.studentIdEmpty");
		return jvo;
	}

	// 2. Create a plain List container (Note: ::Wrapper)
	auto list = oatpp::List<TimetableStudentCourseDTO::Wrapper>::createShared();

	// 3. Generate mock data
	auto course1 = TimetableStudentCourseDTO::createShared();
	course1->course_id = "c_001";
	course1->title = "class1";
	course1->rest_hour = 0;
	list->push_back(course1);

	auto course2 = TimetableStudentCourseDTO::createShared();
	course2->course_id = "c_002";
	course2->title = "class2";
	course2->rest_hour = 49;
	list->push_back(course2);

	// 4. Success response
	jvo->success(list);
	return jvo;
}
#include "stdafx.h"
#include "Record_name.h"
#include "stdafx.h"

namespace
{
}

GetDetailCSJsonVO::Wrapper Record_name::execGetDetailCS(const GetDetailCSQuery::Wrapper& query)
{
	auto data = GetDetailCSDTO::createShared();
	data->lesson_id = query && query->lesson_id ? query->lesson_id : oatpp::UInt64(10002);
	data->lesson_date = "2026-02-28";
	data->start_time = "15:12";
	data->end_time = "16:12";
	data->period_count = oatpp::UInt32(static_cast<v_uint32>(1));
	data->course_title = "Piano Beginner";
	data->teacher_name = "Zhang San";
	data->normal_count = oatpp::UInt32(static_cast<v_uint32>(0));
	data->leave_count = oatpp::UInt32(static_cast<v_uint32>(0));
	data->absent_count = oatpp::UInt32(static_cast<v_uint32>(0));
	data->makeup_count = oatpp::UInt32(static_cast<v_uint32>(0));
	data->can_comment_after_class = true;
	data->can_add_student = true;

	auto vo = GetDetailCSJsonVO::createShared();
	vo->success(data);
	return vo;
}

GetStuListJsonVO::Wrapper Record_name::execGetStuList(const GetStuListQuery::Wrapper& query)
{
	v_uint64 lessonId = static_cast<v_uint64>(10002);
	v_uint64 pageIndex = query && query->page_index ? query->page_index.getValue(1) : static_cast<v_uint64>(1);
	v_uint64 pageSize = query && query->page_size ? query->page_size.getValue(10) : static_cast<v_uint64>(10);
	if (pageIndex == 0)
	{
		pageIndex = 1;
	}
	if (pageSize == 0)
	{
		pageSize = 10;
	}

	v_uint64 total = static_cast<v_uint64>(1);
	v_uint64 totalPage = total == 0 ? 0 : (total + pageSize - 1) / pageSize;

	auto data = GetStuListDTO::createShared();
	data->lesson_id = oatpp::UInt64(lessonId);
	data->page_index = oatpp::UInt64(pageIndex);
	data->page_size = oatpp::UInt64(pageSize);
	data->total = oatpp::UInt64(total);
	data->total_page = oatpp::UInt64(totalPage);
	data->student_id = oatpp::UInt64(70001);
	data->unsigned_count = oatpp::UInt32(static_cast<v_uint32>(1));
	data->is_change_course = false;
	data->is_leave = false;
	data->is_absent = false;
	data->is_signed = false;

	auto vo = GetStuListJsonVO::createShared();
	vo->success(data);
	return vo;
}

SetStudyStatusRspJsonVO::Wrapper Record_name::updateModifyStatus(const SetStudyStatusDTO::Wrapper& dto, const PayloadDTO& payload)
{
	return SetStudyStatusRspJsonVO::Wrapper();
}

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
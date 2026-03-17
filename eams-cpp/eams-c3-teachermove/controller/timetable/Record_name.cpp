#include "Record_name.h"
#include "stdafx.h"

namespace
{
	StuListItemDTO::Wrapper buildStudent(
		v_uint64 studentId,
		const char* studentName,
		const char* consumeCourse,
		v_int32 attendanceState,
		const char* attendanceStateText,
		v_uint32 signedTimes)
	{
		auto item = StuListItemDTO::createShared();
		item->student_id = studentId;
		item->student_name = studentName;
		item->consume_course = consumeCourse;
		item->attendance_state = attendanceState;
		item->attendance_state_text = attendanceStateText;
		item->signed_times = oatpp::UInt32(signedTimes);
		item->adjust_count = oatpp::UInt32(static_cast<v_uint32>(1));
		item->can_change_course = true;
		item->can_leave = true;
		item->can_absent = true;
		item->can_sign = true;
		return item;
	}

	bool containsKeyword(const oatpp::String& text, const oatpp::String& keyword)
	{
		if (!keyword || keyword->empty())
		{
			return true;
		}
		if (!text)
		{
			return false;
		}
		return text->find(keyword->c_str()) != std::string::npos;
	}
}

GetDetailCSJsonVO::Wrapper Record_name::execGetDetailCS(const GetDetailCSQuery::Wrapper& query)
{
	auto data = GetDetailCSDTO::createShared();
	data->lesson_id = query && query->lesson_id ? query->lesson_id : oatpp::UInt64(10002);
	data->lesson_date = "2026-02-28";
	data->start_time = "15:12";
	data->end_time = "16:12";
	data->period_count = oatpp::UInt32(static_cast<v_uint32>(1));
	data->period_label = "1 period";
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
	v_uint64 lessonId = query && query->lesson_id ? query->lesson_id.getValue(10002) : static_cast<v_uint64>(10002);
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

	std::vector<StuListItemDTO::Wrapper> source;
	source.push_back(buildStudent(70001, "Zhang Xiaoming", "Piano Beginner", 0, "Unsigned", 1));
	source.push_back(buildStudent(70002, "Wang Ping", "Piano Beginner", 1, "Signed", 1));

	std::vector<StuListItemDTO::Wrapper> filtered;
	for (const auto& item : source)
	{
		if (!containsKeyword(item->student_name, query ? query->keyword : nullptr))
		{
			continue;
		}
		filtered.push_back(item);
	}

	v_uint64 total = static_cast<v_uint64>(filtered.size());
	v_uint64 totalPage = total == 0 ? 0 : (total + pageSize - 1) / pageSize;
	v_uint64 start = (pageIndex - 1) * pageSize;
	v_uint64 end = std::min(start + pageSize, total);

	auto data = GetStuListDTO::createShared();
	data->lesson_id = oatpp::UInt64(lessonId);
	data->page_index = oatpp::UInt64(pageIndex);
	data->page_size = oatpp::UInt64(pageSize);
	data->total = oatpp::UInt64(total);
	data->total_page = oatpp::UInt64(totalPage);
	data->records = {};

	if (start < end)
	{
		for (v_uint64 i = start; i < end; ++i)
		{
			data->records->push_back(filtered[static_cast<size_t>(i)]);
		}
	}

	auto vo = GetStuListJsonVO::createShared();
	vo->success(data);
	return vo;
}

SetStudyStatusRspJsonVO::Wrapper Record_name::updateModifyStatus(const SetStudyStatusDTO::Wrapper& dto, const PayloadDTO& payload)
{
	return SetStudyStatusRspJsonVO::Wrapper();
}
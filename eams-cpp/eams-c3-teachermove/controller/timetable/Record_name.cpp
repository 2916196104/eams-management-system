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
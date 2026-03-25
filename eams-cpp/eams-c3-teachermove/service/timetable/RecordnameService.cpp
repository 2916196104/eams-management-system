#include "RecordnameService.h"
#include "dao/timetable/RecordnameDao.h"

GetDetailCSJsonVO::Wrapper RecordnameService::getDetailCS(const GetDetailCSQuery::Wrapper& query) const
{
	RecordnameDao dao;
	v_uint64 lessonId = query && query->lesson_id ? static_cast<v_uint64>(query->lesson_id) : static_cast<v_uint64>(0);
	if (lessonId == 0)
	{
		lessonId = dao.selectLatestLessonId();
	}
	auto rows = dao.selectDetailByLessonId(lessonId);

	auto data = GetDetailCSDTO::createShared();
	if (!rows.empty())
	{
		const auto& row = rows.front();
		data->lesson_id = oatpp::UInt64(row.lesson_id);
		data->lesson_date = row.lesson_date.c_str();
		data->start_time = row.start_time.c_str();
		data->end_time = row.end_time.c_str();
		data->period_count = oatpp::UInt32(row.period_count);
		data->course_title = row.course_title.c_str();
		data->teacher_name = row.teacher_name.c_str();
		data->normal_count = oatpp::UInt32(row.normal_count);
		data->leave_count = oatpp::UInt32(row.leave_count);
		data->absent_count = oatpp::UInt32(row.absent_count);
		data->makeup_count = oatpp::UInt32(row.makeup_count);
	}
	else
	{
		data->lesson_id = oatpp::UInt64(lessonId);
		data->lesson_date = "";
		data->start_time = "";
		data->end_time = "";
		data->period_count = oatpp::UInt32(static_cast<v_uint32>(0));
		data->course_title = "";
		data->teacher_name = "";
		data->normal_count = oatpp::UInt32(static_cast<v_uint32>(0));
		data->leave_count = oatpp::UInt32(static_cast<v_uint32>(0));
		data->absent_count = oatpp::UInt32(static_cast<v_uint32>(0));
		data->makeup_count = oatpp::UInt32(static_cast<v_uint32>(0));
	}
	data->can_comment_after_class = true;
	data->can_add_student = true;

	auto vo = GetDetailCSJsonVO::createShared();
	vo->success(data);
	return vo;
}

GetStuListJsonVO::Wrapper RecordnameService::getCSStuList(const GetStuListQuery::Wrapper& query) const
{
	RecordnameDao dao;
	v_uint64 lessonId = dao.selectLatestLessonId();

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
	v_uint64 offset = (pageIndex - 1) * pageSize;

	v_uint64 total = 0;
	if (lessonId > 0)
	{
		total = dao.countStudentsByLessonId(lessonId);
	}

	v_uint64 totalPage = total == 0 ? 0 : (total + pageSize - 1) / pageSize;

	std::list<RecordStudentRow> stuRows;
	if (lessonId > 0)
	{
		stuRows = dao.selectStudentsByLessonId(lessonId, pageSize, offset);
	}

	auto data = GetStuListDTO::createShared();
	data->lesson_id = oatpp::UInt64(lessonId);
	data->page_index = oatpp::UInt64(pageIndex);
	data->page_size = oatpp::UInt64(pageSize);
	data->total = oatpp::UInt64(total);
	data->total_page = oatpp::UInt64(totalPage);
	if (!stuRows.empty())
	{
		const auto& first = stuRows.front();
		data->student_id = oatpp::UInt64(first.student_id);
		data->unsigned_count = oatpp::UInt32(first.unsigned_count);
		data->is_change_course = first.is_change_course;
		data->is_leave = first.is_leave;
		data->is_absent = first.is_absent;
		data->is_signed = first.is_signed;
	}
	else
	{
		data->student_id = oatpp::UInt64(static_cast<v_uint64>(0));
		data->unsigned_count = oatpp::UInt32(static_cast<v_uint32>(0));
		data->is_change_course = false;
		data->is_leave = false;
		data->is_absent = false;
		data->is_signed = false;
	}

	auto vo = GetStuListJsonVO::createShared();
	vo->success(data);
	return vo;
}

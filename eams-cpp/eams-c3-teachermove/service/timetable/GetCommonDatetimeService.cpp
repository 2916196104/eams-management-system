#include "GetCommonDatetimeService.h"
#include "dao/timetable/CommonDatetimeDao.h"

namespace
{
	CommonDatetimeLessonDTO::Wrapper buildLesson(
		v_uint32 lessonCount,
		const char* startTime,
		const char* endTime,
		v_uint64 teacherId,
		v_uint64 classroomId,
		bool isSigned,
		bool isLeave,
		bool isReserved)
	{
		auto lesson = CommonDatetimeLessonDTO::createShared();
		lesson->lesson_count = lessonCount;
		lesson->start_time = startTime;
		lesson->end_time = endTime;
		lesson->teacher_id = teacherId;
		lesson->classroom_id = classroomId;
		lesson->is_signed = isSigned;
		lesson->is_leave = isLeave;
		lesson->is_reserved = isReserved;
		return lesson;
	}
}

CommonDatetimeJsonVO::Wrapper GetCommonDatetimeService::getCommonDatetime(const GetCommonDatetimeQuery::Wrapper& query) const
{
	auto queryDate = query && query->date ? query->date : oatpp::String("2026-03-15");
	CommonDatetimeDao dao;
	auto rows = dao.selectByDate(queryDate.getValue(""));

	auto data = CommonDatetimeDTO::createShared();
	data->lesson_count = oatpp::UInt32(static_cast<v_uint32>(rows.size()));
	data->lessons = {};

	for (const auto& row : rows)
	{
		data->lessons->push_back(buildLesson(
			row.lesson_count,
			row.start_time.c_str(),
			row.end_time.c_str(),
			row.teacher_id,
			row.classroom_id,
			row.is_signed,
			row.is_leave,
			row.is_reserved));
	}

	auto vo = CommonDatetimeJsonVO::createShared();
	vo->success(data);
	return vo;
}

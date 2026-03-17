#include "GetCommonDatetime.h"
#include "stdafx.h"

namespace
{
	CommonDatetimeLessonDTO::Wrapper buildLesson(
		v_uint32 lessonCount,
		const char* startTime,
		const char* endTime,
		v_uint64 teacherId,
		v_uint64 classroomId,
		v_bool isSigned,
		v_bool isLeave,
		v_bool isReserved)
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

CommonDatetimeJsonVO::Wrapper GetCommonDatetime::execGetCommonDatetime(const GetCommonDatetimeQuery::Wrapper& query)
{
	auto queryDate = query && query->date ? query->date : oatpp::String("2026-03-15");

	auto data = CommonDatetimeDTO::createShared();
	data->lesson_count = oatpp::UInt32(3);
	data->lessons = {};

	(void)queryDate;
	data->lessons->push_back(buildLesson(1, "15:12", "16:12", 1001, 5001, true, false, true));
	data->lessons->push_back(buildLesson(1, "17:40", "18:20", 1002, 5002, false, true, false));
	data->lessons->push_back(buildLesson(1, "18:30", "19:10", 1003, 5003, false, false, true));

	auto vo = CommonDatetimeJsonVO::createShared();
	vo->success(data);
	return vo;
}
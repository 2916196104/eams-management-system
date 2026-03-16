#include "GetCommonDatetime.h"
#include "stdafx.h"

namespace
{
	CommonDatetimeLessonDTO::Wrapper buildLesson(
		v_uint64 id,
		v_uint64 classId,
		const char* className,
		v_uint64 courseId,
		const char* title,
		const oatpp::String& lessonDate,
		const char* startTime,
		const char* endTime,
		v_int32 state,
		const char* stateText,
		v_uint64 teacherId,
		const char* teacherName,
		v_uint64 classroomId,
		const char* classroomName,
		v_uint32 arrivedCount,
		v_uint32 shouldArriveCount,
		v_uint32 evaluatedCount)
	{
		auto lesson = CommonDatetimeLessonDTO::createShared();
		lesson->id = id;
		lesson->class_id = classId;
		lesson->class_name = className;
		lesson->course_id = courseId;
		lesson->title = title;
		lesson->date = lessonDate;
		lesson->start_time = startTime;
		lesson->end_time = endTime;
		lesson->state = state;
		lesson->state_text = stateText;
		lesson->teacher_id = teacherId;
		lesson->teacher_name = teacherName;
		lesson->classroom_id = classroomId;
		lesson->classroom_name = classroomName;
		lesson->arrived_count = arrivedCount;
		lesson->should_arrive_count = shouldArriveCount;
		lesson->evaluated_count = evaluatedCount;
		lesson->can_comment = true;
		lesson->can_sign = true;
		return lesson;
	}

	oatpp::String buildDateLabel(const oatpp::String& date)
	{
		if (date == "2026-03-15")
		{
			return "Today timetable";
		}
		return date + " timetable";
	}
}

CommonDatetimeJsonVO::Wrapper GetCommonDatetime::execGetCommonDatetime(const GetCommonDatetimeQuery::Wrapper& query)
{
	auto queryDate = query && query->date ? query->date : oatpp::String("2026-03-15");
	auto teacherId = query && query->teacher_id ? query->teacher_id : oatpp::UInt64(1001);

	auto data = CommonDatetimeDTO::createShared();
	data->date = queryDate;
	data->date_label = buildDateLabel(queryDate);
	data->lesson_count = oatpp::UInt32(3);
	data->lessons = {};

	data->lessons->push_back(buildLesson(10001, 20001, "PE Class 1", 30001, "Taekwondo Experience", queryDate, "09:00:00", "10:00:00", 2, "Finished", teacherId.getValue(1001), "Zhang San", 5001, "Multimedia Room 1", 1, 1, 1));
	data->lessons->push_back(buildLesson(10002, 20002, "Piano Class 1", 30002, "Piano Beginner", queryDate, "15:12:00", "16:12:00", 2, "Finished", teacherId.getValue(1001), "Zhang San", 5001, "Multimedia Room 1", 0, 1, 0));
	data->lessons->push_back(buildLesson(10003, 20001, "PE Class 1", 30001, "Taekwondo Experience", queryDate, "15:34:00", "16:34:00", 2, "Finished", teacherId.getValue(1001), "Zhang San", 5001, "Multimedia Room 1", 1, 1, 1));

	auto vo = CommonDatetimeJsonVO::createShared();
	vo->success(data);
	return vo;
}
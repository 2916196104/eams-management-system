#include "GetCommonDatetimeService.h"
#include "dao/lesson/LessonDao.h"
#include "domain/query/lesson/LessonQuery.h"

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
	LessonDAO dao;
	auto lessonQuery = LessonQuery::createShared();
	lessonQuery->pageIndex = 1;
	lessonQuery->pageSize = 200;
	auto rows = dao.selectWithPage(lessonQuery);

	auto data = CommonDatetimeDTO::createShared();
	data->lesson_count = oatpp::UInt32(static_cast<v_uint32>(0));
	data->lessons = {};

	for (const auto& row : rows)
	{
		if (queryDate && queryDate->size() > 0 && row.getDate() != queryDate.getValue(""))
		{
			continue;
		}

		data->lessons->push_back(buildLesson(
			static_cast<v_uint32>(row.getDecCount()),
			row.getStartTime().c_str(),
			row.getEndTime().c_str(),
			static_cast<v_uint64>(row.getTeacherId()),
			static_cast<v_uint64>(row.getRoomId()),
			false,
			false,
			false));
	}

	data->lesson_count = oatpp::UInt32(static_cast<v_uint32>(data->lessons->size()));

	auto vo = CommonDatetimeJsonVO::createShared();
	vo->success(data);
	return vo;
}

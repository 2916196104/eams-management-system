#include "stdafx.h"
#include "LessonDAO.h"
#include "LessonMapper.h"

std::list<ConflictInfo> LessonDAO::checkConflict(int64_t roomId, const std::string& date, const std::string& startTime, const std::string& endTime)
{
	string sql = "SELECT title, date, start_time, end_time FROM lesson "
		"WHERE room_id = ? AND date = ? AND deleted = 0 "
		"AND ((start_time < ? AND end_time > ?) OR (start_time >= ? AND start_time < ?) OR (end_time > ? AND end_time <= ?))";
	return sqlSession->executeQuery<ConflictInfo>(sql, ConflictInfoMapper(), "%ull%s%s%s%s%s%s%s", 
		roomId, date, endTime, startTime, startTime, endTime, startTime, endTime);
}

std::list<ConflictInfo> LessonDAO::checkConflictBatch(int64_t roomId, const std::set<std::string>& dates, const std::string& startTime, const std::string& endTime)
{
	std::list<ConflictInfo> conflicts;
	if (dates.empty()) return conflicts;
	
	for (const auto& date : dates)
	{
		auto result = checkConflict(roomId, date, startTime, endTime);
		conflicts.insert(conflicts.end(), result.begin(), result.end());
	}
	return conflicts;
}

int LessonDAO::getMaxSnByClassIdAndCourseId(int64_t classId, int64_t courseId)
{
	string sql = "SELECT COALESCE(MAX(sn), 0) FROM lesson WHERE class_id = ? AND course_id = ? AND deleted = 0";
	auto result = sqlSession->executeQuery<int>(sql, IntMapper(), "%ll%ll", classId, courseId);
	if (result.empty()) return 0;
	return result.front();
}

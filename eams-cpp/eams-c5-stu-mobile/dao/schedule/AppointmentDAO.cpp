#include "stdafx.h"
#include "AppointmentDAO.h"
#include <sstream>
#include <iomanip>
#include <chrono>
#include "string"
#include "../../../lib-common/include/id/SnowFlake.h"

string AppointmentDAO::generateSnowFlakeId()
{
	return std::to_string(SnowFlake(0, 0).nextId());
}

std::string AppointmentDAO::getCurrentDateTime() {
	// 1. 获取当前系统时间（精确到秒）
	auto now = std::chrono::system_clock::now();
	// 2. 转换为time_t类型（兼容传统时间接口）
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);
	// 3. 转换为本地时间（避免UTC时差）
	std::tm now_tm = *std::localtime(&now_c);

	// 4. 格式化输出（YYYY-MM-DD HH:MM:SS）
	std::ostringstream oss;
	oss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");
	return oss.str();
}

std::string AppointmentDAO::getCounselorId(const AppointmentQuery::Wrapper& query)
{
	std::stringstream sql;
	sql << "SELECT counselor FROM student WHERE id = ? LIMIT 1";
	SqlParams params;
	if (query->studentId) SQLPARAMS_PUSH(params, "s", std::string, query->studentId.getValue(""));

	uint64_t counselorId = sqlSession->executeQueryNumerical(sql.str(), params);

	return std::to_string(counselorId);
}

std::string AppointmentDAO::getLessonId(const AppointmentQuery::Wrapper& query)
{
	std::stringstream sql;
	sql << "SELECT id FROM lesson WHERE course_id = ? AND date = ? LIMIT 1";
	SqlParams params;
	if (query->courseId) SQLPARAMS_PUSH(params, "s", std::string, query->courseId.getValue(""));
	if (query->date) SQLPARAMS_PUSH(params, "s", std::string, query->date.getValue(""));

	uint64_t lessonId = sqlSession->executeQueryNumerical(sql.str(), params);
	
	return std::to_string(lessonId);
}

std::string AppointmentDAO::insertAppointment(const AppointmentQuery::Wrapper& query)
{
	string id = generateSnowFlakeId();
	string lessonId = getLessonId(query);
	string counselorId = getCounselorId(query);
	string currentDateTime = getCurrentDateTime();
	std::stringstream sql;
	sql << "INSERT INTO appointment (id, lesson_id, student_id, add_time, course_id, counselor)";
	sql << " VALUES ( ?, ?, ?, ?, ?, ? )";
	SqlParams params;
	// 预约id
	if (id.size()) SQLPARAMS_PUSH(params, "s", std::string, id);
	else return ZH_WORDS_GETTER("schedule.appointment.errmsg");
	// 试听课次id
	if (lessonId.size()) SQLPARAMS_PUSH(params, "s", std::string, lessonId);
	else return ZH_WORDS_GETTER("schedule.appointment.errmsg");
	// 学生id
	if (query->studentId) SQLPARAMS_PUSH(params, "s", std::string, query->studentId.getValue(""));
	else return ZH_WORDS_GETTER("schedule.appointment.errmsg");
	// 预约时间
	if(currentDateTime.size()) SQLPARAMS_PUSH(params, "s", std::string, currentDateTime);
	else return ZH_WORDS_GETTER("schedule.appointment.errmsg");
	// 预约课程id
	if (query->courseId) SQLPARAMS_PUSH(params, "s", std::string,query->courseId.getValue(""));
	else return ZH_WORDS_GETTER("schedule.appointment.errmsg");
	// 顾问id
	if (counselorId.size()) SQLPARAMS_PUSH(params, "s", std::string, counselorId);
	else return ZH_WORDS_GETTER("schedule.appointment.errmsg");

	sqlSession->executeUpdate(sql.str(), params);
	return "success";
}
#include "stdafx.h"
#include "AppointmentDAO.h"
#include <sstream>
#include <iomanip>
#include <chrono>
#include "domain/dto/schedule/AppointmentDTO.h"
#include "string"
#include "../../../lib-common/include/id/SnowFlake.h"

string AppointmentDAO::generateSnowFlakeId()
{
	return std::to_string(SnowFlake(0, 0).nextId());
}

//std::string AppointmentDAO::getCurrentDateTime() {
//	// 1. 获取当前系统时间（精确到秒）
//	auto now = std::chrono::system_clock::now();
//	// 2. 转换为time_t类型（兼容传统时间接口）
//	std::time_t now_c = std::chrono::system_clock::to_time_t(now);
//	// 3. 转换为本地时间（避免UTC时差）
//	std::tm now_tm = *std::localtime(&now_c);
//
//	// 4. 格式化输出（YYYY-MM-DD HH:MM:SS）
//	std::ostringstream oss;
//	oss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");
//	return oss.str();
//}

std::string AppointmentDAO::getCounselorId(const AppointmentAddDTO::Wrapper& dto)
{
	std::stringstream sql;
	sql << "SELECT counselor FROM student WHERE id = ? LIMIT 1";
	SqlParams params;
	if (dto->studentId) SQLPARAMS_PUSH(params, "s", std::string, dto->studentId.getValue(""));

	uint64_t counselorId = sqlSession->executeQueryNumerical(sql.str(), params);

	return std::to_string(counselorId);
}

std::string AppointmentDAO::getLessonId(const AppointmentAddDTO::Wrapper& dto)
{
	std::stringstream sql;
	sql << "SELECT id FROM lesson WHERE course_id = ? AND date = ? LIMIT 1";
	SqlParams params;
	if (dto->courseId) SQLPARAMS_PUSH(params, "s", std::string, dto->courseId.getValue(""));
	if (dto->date) SQLPARAMS_PUSH(params, "s", std::string, dto->date.getValue(""));

	uint64_t lessonId = sqlSession->executeQueryNumerical(sql.str(), params);
	
	return std::to_string(lessonId);
}

std::string AppointmentDAO::insertAppointment(const AppointmentAddDTO::Wrapper& dto)
{
	string id = generateSnowFlakeId();
	string lessonId = getLessonId(dto);
	string counselorId = getCounselorId(dto);
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
	if (dto->studentId) SQLPARAMS_PUSH(params, "s", std::string, dto->studentId.getValue(""));
	else return ZH_WORDS_GETTER("schedule.appointment.errmsg");
	// 预约时间
	if(dto->date) SQLPARAMS_PUSH(params, "s", std::string, dto->date.getValue(""));
	else return ZH_WORDS_GETTER("schedule.appointment.errmsg");
	// 预约课程id
	if (dto->courseId) SQLPARAMS_PUSH(params, "s", std::string, dto->courseId.getValue(""));
	else return ZH_WORDS_GETTER("schedule.appointment.errmsg");
	// 顾问id
	if (counselorId.size()) SQLPARAMS_PUSH(params, "s", std::string, counselorId);
	else return ZH_WORDS_GETTER("schedule.appointment.errmsg");

	sqlSession->executeUpdate(sql.str(), params);
	return id;
}
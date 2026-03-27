#include "stdafx.h"
#include "AppointmentDAO.h"


uint64_t AppointmentDAO::selectCountByStudentAndLesson(uint64_t studentId, uint64_t lessonId)
{
	SqlParams params;

	std::string sql = "SELECT COUNT(*) FROM appointment WHERE student_id = ? AND lesson_id = ?";

	// 绑定参数
	SQLPARAMS_PUSH(params, "ull", uint64_t, studentId);
	SQLPARAMS_PUSH(params, "ull", uint64_t, lessonId);

	// 执行查询
	return sqlSession->executeQueryNumerical(sql, params);
}

uint64_t AppointmentDAO::getCourseIdByScheduleId(uint64_t lessonId)
{
	SqlParams params;

	// 直接去 lesson (课次表) 里查这节课的 course_id
	// state = 1 通常表示这节课是正常状态（未取消）
	std::string sql = "SELECT course_id FROM lesson WHERE id = ? AND state = 1 LIMIT 1";

	SQLPARAMS_PUSH(params, "ull", uint64_t, lessonId);
	return sqlSession->executeQueryNumerical(sql, params);
}

uint64_t AppointmentDAO::getStudentCourseRemain(uint64_t studentId, uint64_t courseId)
{
	SqlParams params;
	// 假设 status = 1 表示这门课处于正常有效状态（未退费、未结业）
	std::string sql = "SELECT IFNULL(SUM(count_lesson_total - count_lesson_complete), 0) "
		"FROM student_course "
		"WHERE student_id = ? AND course_id = ? AND verify_state = 2";

	SQLPARAMS_PUSH(params, "ull", uint64_t, studentId);
	SQLPARAMS_PUSH(params, "ull", uint64_t, courseId);

	return sqlSession->executeQueryNumerical(sql, params);
}

uint64_t AppointmentDAO::getStudentTrialCardRemain(uint64_t studentId, uint64_t courseId)
{
	SqlParams params;

	// 查体验卡记录表：把属于这个学生的剩余课时加起来
	// 条件：必须没过期 (expired_date >= 当前日期)，并且剩余数量 > 0
	std::string sql = "SELECT IFNULL(SUM(lesson_count), 0) "
		"FROM course_trial_record "
		"WHERE student_id = ? "
		"AND (course_id = ? OR course_id IS NULL) " // 兼容通用体验卡
		"AND expired_date >= CURDATE()";

	SQLPARAMS_PUSH(params, "ull", uint64_t, studentId);
	SQLPARAMS_PUSH(params, "ull", uint64_t, courseId); 

	return sqlSession->executeQueryNumerical(sql, params);
}

std::pair<uint64_t, uint64_t> AppointmentDAO::getValidTrialCard(uint64_t studentId, uint64_t courseId)
{
	SqlParams params1;

	// 先查出那张最快过期的可用体验卡的 物理主键 ID (trial_record_id)
	std::string sql1 = "SELECT id "
		"FROM course_trial_record "
		"WHERE student_id = ? "
		"AND (course_id = ? OR course_id IS NULL) "
		"AND expired_date >= CURDATE() "
		"AND lesson_count > 0 "
		"ORDER BY expired_date ASC LIMIT 1";

	SQLPARAMS_PUSH(params1, "ull", uint64_t, studentId);
	SQLPARAMS_PUSH(params1, "ull", uint64_t, courseId);

	//拿回 recordId
	uint64_t recordId = sqlSession->executeQueryNumerical(sql1, params1);

	// 如果返回 0，说明这个学生根本没有可用的卡，直接退回
	if (recordId == 0) {
		return { 0, 0 };
	}

	// 既然已经找到了这张卡，直接拿主键查出它的模板trial_id
	SqlParams params2;
	std::string sql2 = "SELECT trial_id FROM course_trial_record WHERE id = ? LIMIT 1";
	SQLPARAMS_PUSH(params2, "ull", uint64_t, recordId);

	// 再次调用数值查询接口，拿回trialId
	uint64_t trialId = sqlSession->executeQueryNumerical(sql2, params2);

	// 返回这两个ID
	return { recordId, trialId };
}
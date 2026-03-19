#include "stdafx.h"
#include "ClassStudentDAO.h"
#include "ClassStudentMapper.h"

uint64_t ClassStudentDAO::countClassStudentList(const ClassStudentQuery::Wrapper& query)
{
	std::string sql =
		"SELECT COUNT(1) "
		"FROM class_student cs "
		"INNER JOIN student s ON s.id = cs.student_id AND s.deleted = 0 "
		"LEFT JOIN `user` u ON u.id = s.user_id "
		"WHERE cs.deleted = 0 AND cs.class_id = ? ";
	SqlParams params;
	SQLPARAMS_PUSH(params, "ull", uint64_t, query->classId.getValue(0));
	if (query->keyword && !query->keyword->empty()) {
		sql += "AND (s.name LIKE CONCAT('%', ?, '%') OR u.name LIKE CONCAT('%', ?, '%') OR u.mobile LIKE CONCAT('%', ?, '%')) ";
		std::string kw = query->keyword.getValue("");
		SQLPARAMS_PUSH(params, "s", std::string, kw);
		SQLPARAMS_PUSH(params, "s", std::string, kw);
		SQLPARAMS_PUSH(params, "s", std::string, kw);
	}
	return sqlSession->executeQueryOne<uint64_t>(sql, UInt64Mapper(), params);
}

std::list<PtrClassStudentDO> ClassStudentDAO::selectClassStudentList(const ClassStudentQuery::Wrapper& query)
{
	std::string sql =
		"SELECT "
		"cs.id, cs.class_id, cs.student_id, cs.consume_course_id, IFNULL(cs.reason, 0) AS reason, "
		"IFNULL(DATE_FORMAT(cs.add_time, '%Y-%m-%d %H:%i:%s'), '') AS add_time, IFNULL(cs.remark, '') AS class_student_remark, "
		"IFNULL(s.user_id, 0) AS user_id, IFNULL(u.name, '') AS parent_name, IFNULL(u.mobile, '') AS mobile, "
		"IFNULL(s.family_rel, 0) AS family_rel, s.name AS student_name, IFNULL(s.stage, 0) AS stage, IFNULL(s.gender, 0) AS gender, "
		"IFNULL(DATE_FORMAT(s.birthday, '%Y-%m-%d'), '') AS birthday, IFNULL(s.head_img, '') AS head_img, IFNULL(s.remark, '') AS student_remark, "
		"IFNULL((sc.count_lesson_total - sc.count_lesson_complete - sc.count_lesson_refund), 0) AS count_lesson_remaining "
		"FROM class_student cs "
		"INNER JOIN student s ON s.id = cs.student_id AND s.deleted = 0 "
		"LEFT JOIN `user` u ON u.id = s.user_id "
		"LEFT JOIN student_course sc ON sc.student_id = cs.student_id AND sc.course_id = cs.consume_course_id AND sc.deleted = 0 "
		"WHERE cs.deleted = 0 AND cs.class_id = ? ";
	SqlParams params;
	SQLPARAMS_PUSH(params, "ull", uint64_t, query->classId.getValue(0));
	if (query->keyword && !query->keyword->empty()) {
		sql += "AND (s.name LIKE CONCAT('%', ?, '%') OR u.name LIKE CONCAT('%', ?, '%') OR u.mobile LIKE CONCAT('%', ?, '%')) ";
		std::string kw = query->keyword.getValue("");
		SQLPARAMS_PUSH(params, "s", std::string, kw);
		SQLPARAMS_PUSH(params, "s", std::string, kw);
		SQLPARAMS_PUSH(params, "s", std::string, kw);
	}
	sql += "ORDER BY cs.add_time DESC, cs.id DESC LIMIT ?, ?";
	SQLPARAMS_PUSH(params, "ull", uint64_t, (query->pageIndex.getValue(1) - 1) * query->pageSize.getValue(10));
	SQLPARAMS_PUSH(params, "ull", uint64_t, query->pageSize.getValue(10));
	return sqlSession->executeQuery<PtrClassStudentDO>(sql, ClassStudentListMapper(), params);
}

PtrClassStudentDO ClassStudentDAO::selectClassStudentDetail(uint64_t id)
{
	std::string sql =
		"SELECT "
		"cs.id, cs.class_id, cs.student_id, cs.consume_course_id, IFNULL(cs.reason, 0) AS reason, "
		"IFNULL(DATE_FORMAT(cs.add_time, '%Y-%m-%d %H:%i:%s'), '') AS add_time, IFNULL(cs.remark, '') AS class_student_remark, "
		"IFNULL(c.name, '') AS class_name, IFNULL(c.course_id, 0) AS class_course_id, IFNULL(co.name, '') AS class_course_name, "
		"IFNULL(c.grade_id, 0) AS grade_id, IFNULL(cg.name, '') AS grade_name, "
		"IFNULL(s.user_id, 0) AS user_id, IFNULL(u.name, '') AS parent_name, IFNULL(u.mobile, '') AS mobile, "
		"IFNULL(s.family_rel, 0) AS family_rel, s.name AS student_name, IFNULL(s.stage, 0) AS stage, IFNULL(s.gender, 0) AS gender, "
		"IFNULL(DATE_FORMAT(s.birthday, '%Y-%m-%d'), '') AS birthday, IFNULL(s.head_img, '') AS head_img, IFNULL(s.remark, '') AS student_remark, "
		"IFNULL((sc.count_lesson_total - sc.count_lesson_complete - sc.count_lesson_refund), 0) AS count_lesson_remaining "
		"FROM class_student cs "
		"INNER JOIN class c ON c.id = cs.class_id AND c.deleted = 0 "
		"INNER JOIN student s ON s.id = cs.student_id AND s.deleted = 0 "
		"LEFT JOIN `user` u ON u.id = s.user_id "
		"LEFT JOIN class_grade cg ON cg.id = c.grade_id AND cg.deleted = 0 "
		"LEFT JOIN course co ON co.id = c.course_id AND co.deleted = 0 "
		"LEFT JOIN student_course sc ON sc.student_id = cs.student_id AND sc.course_id = cs.consume_course_id AND sc.deleted = 0 "
		"WHERE cs.deleted = 0 AND cs.id = ?";
	return sqlSession->executeQueryOne<PtrClassStudentDO>(sql, ClassStudentDetailMapper(), "%ull", id);
}

uint64_t ClassStudentDAO::countClassStudentCourseList(const ClassStudentCourseQuery::Wrapper& query)
{
	std::string sql =
		"SELECT COUNT(1) "
		"FROM student_course sc "
		"INNER JOIN class_student cs ON cs.class_id = ? AND cs.student_id = ? AND cs.deleted = 0 "
		"LEFT JOIN course co ON co.id = sc.course_id AND co.deleted = 0 "
		"LEFT JOIN subject sub ON sub.id = sc.subject_id AND sub.deleted = 0 "
		"WHERE sc.deleted = 0 AND sc.student_id = ? ";
	SqlParams params;
	SQLPARAMS_PUSH(params, "ull", uint64_t, query->classId.getValue(0));
	SQLPARAMS_PUSH(params, "ull", uint64_t, query->studentId.getValue(0));
	SQLPARAMS_PUSH(params, "ull", uint64_t, query->studentId.getValue(0));
	if (query->keyword && !query->keyword->empty()) {
		sql += "AND (co.name LIKE CONCAT('%', ?, '%') OR sub.name LIKE CONCAT('%', ?, '%')) ";
		std::string kw = query->keyword.getValue("");
		SQLPARAMS_PUSH(params, "s", std::string, kw);
		SQLPARAMS_PUSH(params, "s", std::string, kw);
	}
	return sqlSession->executeQueryOne<uint64_t>(sql, UInt64Mapper(), params);
}

std::list<PtrClassStudentCourseDO> ClassStudentDAO::selectClassStudentCourseList(const ClassStudentCourseQuery::Wrapper& query)
{
	std::string sql =
		"SELECT "
		"sc.id, sc.student_id, sc.course_id, IFNULL(co.name, '') AS course_name, "
		"sc.subject_id, IFNULL(sub.name, '') AS subject_name, "
		"IFNULL(DATE_FORMAT(sc.start_date, '%Y-%m-%d'), '') AS start_date, "
		"IFNULL(DATE_FORMAT(sc.expire_date, '%Y-%m-%d'), '') AS expire_date, "
		"IFNULL(sc.remark, '') AS remark, "
		"IFNULL(sc.count_lesson_total, 0) AS count_lesson_total, "
		"IFNULL(sc.count_lesson_complete, 0) AS count_lesson_complete, "
		"IFNULL(sc.count_lesson_refund, 0) AS count_lesson_refund, "
		"(IFNULL(sc.count_lesson_total, 0) - IFNULL(sc.count_lesson_complete, 0) - IFNULL(sc.count_lesson_refund, 0)) AS count_lesson_remaining, "
		"IFNULL(sc.course_amount, 0) AS course_amount, IFNULL(sc.discount_amount, 0) AS discount_amount, "
		"IFNULL(sc.amount, 0) AS amount, IFNULL(sc.paid_amount, 0) AS paid_amount, IFNULL(sc.pay_off, 0) AS pay_off, "
		"IFNULL(sc.operator, 0) AS operator, IFNULL(sc.creator, 0) AS creator, IFNULL(DATE_FORMAT(sc.add_time, '%Y-%m-%d %H:%i:%s'), '') AS add_time, "
		"IFNULL(sc.editor, 0) AS editor, IFNULL(DATE_FORMAT(sc.edit_time, '%Y-%m-%d %H:%i:%s'), '') AS edit_time, "
		"IFNULL(sc.verify_state, 0) AS verify_state, IFNULL(sc.warning_times, 0) AS warning_times, IFNULL(sc.priority, 0) AS priority, "
		"IFNULL(sc.unit_price, 0) AS unit_price, IFNULL(sc.from_trial, 0) AS from_trial, IFNULL(sc.org_id, 0) AS org_id, "
		"CASE WHEN sc.course_id = cs.consume_course_id THEN 1 ELSE 0 END AS default_consume_course "
		"FROM student_course sc "
		"INNER JOIN class_student cs ON cs.class_id = ? AND cs.student_id = ? AND cs.deleted = 0 "
		"LEFT JOIN course co ON co.id = sc.course_id AND co.deleted = 0 "
		"LEFT JOIN subject sub ON sub.id = sc.subject_id AND sub.deleted = 0 "
		"WHERE sc.deleted = 0 AND sc.student_id = ? ";
	SqlParams params;
	SQLPARAMS_PUSH(params, "ull", uint64_t, query->classId.getValue(0));
	SQLPARAMS_PUSH(params, "ull", uint64_t, query->studentId.getValue(0));
	SQLPARAMS_PUSH(params, "ull", uint64_t, query->studentId.getValue(0));
	if (query->keyword && !query->keyword->empty()) {
		sql += "AND (co.name LIKE CONCAT('%', ?, '%') OR sub.name LIKE CONCAT('%', ?, '%')) ";
		std::string kw = query->keyword.getValue("");
		SQLPARAMS_PUSH(params, "s", std::string, kw);
		SQLPARAMS_PUSH(params, "s", std::string, kw);
	}
	sql += "ORDER BY default_consume_course DESC, sc.add_time DESC, sc.id DESC LIMIT ?, ?";
	SQLPARAMS_PUSH(params, "ull", uint64_t, (query->pageIndex.getValue(1) - 1) * query->pageSize.getValue(10));
	SQLPARAMS_PUSH(params, "ull", uint64_t, query->pageSize.getValue(10));
	return sqlSession->executeQuery<PtrClassStudentCourseDO>(sql, ClassStudentCourseMapper(), params);
}

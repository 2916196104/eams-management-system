#include "stdafx.h"
#include "dao/finishstudent/FinishStudentDAO.h"
#include "dao/finishstudent/FinishStudentMapper.h"
#include <cstdint>

std::list<FinishStudentDTO::Wrapper> FinishStudentDAO::listFinishStudentByIds(const oatpp::List<oatpp::String>& ids)
{
	if (!ids || ids->empty()) {
		return {};
	}

	string sql =
		"SELECT "
		"s.id AS id, "
		"s.name AS student_name, "
		"IFNULL(u.name, '') AS parent_name, "
		"IFNULL(s.family_rel, 0) AS family_rel, "
		"IFNULL(u.mobile, '') AS mobile, "
		"IFNULL(st.name, '') AS counselor, "
		"IFNULL(cg.name, '') AS grade, "
		"IFNULL(org.name, '') AS school_name, "
		"IFNULL(course_stat.lesson_count, 0) AS lesson_count, "
		"IFNULL(s.credit, 0) AS points, "
		"IFNULL(s.gender, 0) AS gender, "
		"IFNULL(TIMESTAMPDIFF(YEAR, s.birthday, CURDATE()), 0) AS age, "
		"IFNULL(s.remark, '') AS remark, "
		"IFNULL(DATE_FORMAT(s.graduation_date, '%Y-%m-%d'), '') AS graduation_date "
		"FROM `student` s "
		"LEFT JOIN `user` u ON u.id = s.user_id "
		"LEFT JOIN `staff` st ON st.id = s.counselor "
		"LEFT JOIN `class_grade` cg ON cg.id = s.grade_id "
		"LEFT JOIN `org` org ON org.id = s.school_id "
		"LEFT JOIN ( "
		"  SELECT student_id, SUM(IFNULL(count_lesson_complete, 0)) AS lesson_count "
		"  FROM `student_course` "
		"  WHERE deleted = 0 "
		"  GROUP BY student_id "
		") course_stat ON course_stat.student_id = s.id "
		"WHERE s.deleted = 0 AND s.graduation_date IS NOT NULL ";

	SqlParams params;
	sql += "AND s.id IN (";
	bool first = true;
	for (const auto& id : *ids) {
		auto idValue = id.getValue("");
		if (idValue.empty()) continue;
		if (!first) sql += ", ";
		first = false;
		sql += "?";
		SQLPARAMS_PUSH(params, "s", string, idValue);
	}
	if (first) {
		return {};
	}
	sql += ") ";
	sql += "ORDER BY s.graduation_date DESC, s.id DESC ";

	return sqlSession->executeQuery<FinishStudentDTO::Wrapper>(sql, FinishStudentMapper(), params);
}

int FinishStudentDAO::updateFinishStudent(const FinishStudentDTO::Wrapper& dto)
{
	if (!dto || !dto->id) {
		return 0;
	}

	const auto id = static_cast<uint64_t>(dto->id.getValue(0));
	const auto remark = dto->remark.getValue("");
	const auto graduationDate = dto->graduationDate.getValue("");
	SqlParams params;

	if (graduationDate.empty()) {
		string sql =
			"UPDATE `student` "
			"SET `graduation_date` = NULL, `remark` = ?, `edit_time` = NOW() "
			"WHERE `id` = ? AND `deleted` = 0";
		SQLPARAMS_PUSH(params, "s", string, remark);
		SQLPARAMS_PUSH(params, "ull", uint64_t, id);
		return sqlSession->executeUpdate(sql, params);
	}

	string sql =
		"UPDATE `student` "
		"SET `graduation_date` = ?, `remark` = ?, `edit_time` = NOW() "
		"WHERE `id` = ? AND `deleted` = 0";
	SQLPARAMS_PUSH(params, "s", string, graduationDate);
	SQLPARAMS_PUSH(params, "s", string, remark);
	SQLPARAMS_PUSH(params, "ull", uint64_t, id);
	return sqlSession->executeUpdate(sql, params);
}

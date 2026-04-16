#include "stdafx.h"
#include "dao/finishstudent/FinishStudentDAO.h"
#include "dao/finishstudent/FinishStudentMapper.h"
#include <cstdint>

std::list<FinishStudentDTO::Wrapper> FinishStudentDAO::listFinishStudentByIds(const oatpp::List<oatpp::UInt64>& ids)
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
		"  WHERE deleted=0 "
		"  GROUP BY student_id "
		") course_stat ON course_stat.student_id = s.id ";
		

	SqlParams params;
	sql += "WHERE s.id IN (";
	bool first = true;
	for (const auto& id : *ids) {
		cout << "id:" << id << endl;
		if (!first) sql += ", ";
		first = false;
		sql += " ? ";
		SQLPARAMS_PUSH(params, "ull", uint64_t, id);
	}
	if (first) {
		return {};
	}
	sql += ") ";
	sql += "ORDER BY s.id DESC ";

	auto res = sqlSession->executeQuery<FinishStudentDTO::Wrapper>(sql, FinishStudentMapper(), params);
	return res;
}

int FinishStudentDAO::updateFinishStudentBatch(const std::list<FinishStudentDO>& rows)
{
	if (rows.empty()) {
		return 0;
	}

	int updatedRows = 0;
	sqlSession->beginTransaction();
	try {
		for (const auto& row : rows) {
			const auto id = row.getId();
			if (id == 0) {
				continue;
			}

			SqlParams studentParams;
			string studentSql =
				"UPDATE `student` s "
				"SET s.`name` = COALESCE(NULLIF(?, ''), s.`name`), "
				"    s.`family_rel` = ?, "
				"    s.`counselor` = (SELECT st.id FROM `staff` st WHERE st.`name` = NULLIF(?, '') LIMIT 1), "
				"    s.`grade_id` = (SELECT cg.id FROM `class_grade` cg WHERE cg.`name` = NULLIF(?, '') LIMIT 1), "
				"    s.`school_id` = (SELECT org.id FROM `org` org WHERE org.`name` = NULLIF(?, '') LIMIT 1), "
				"    s.`credit` = ?, "
				"    s.`gender` = ?, "
				"    s.`remark` = ?, "
				"    s.`graduation_date` = NULLIF(?, ''), "
				"    s.`edit_time` = NOW() "
				"WHERE s.`id` = ? AND s.`deleted` = 0";
			SQLPARAMS_PUSH(studentParams, "s", string, row.getStudentName());
			SQLPARAMS_PUSH(studentParams, "i", int32_t, row.getFamilyRel());
			SQLPARAMS_PUSH(studentParams, "s", string, row.getCounselor());
			SQLPARAMS_PUSH(studentParams, "s", string, row.getGrade());
			SQLPARAMS_PUSH(studentParams, "s", string, row.getSchoolName());
			SQLPARAMS_PUSH(studentParams, "i", int32_t, row.getPoints());
			SQLPARAMS_PUSH(studentParams, "i", int32_t, row.getGender());
			SQLPARAMS_PUSH(studentParams, "s", string, row.getRemark());
			SQLPARAMS_PUSH(studentParams, "s", string, row.getGraduationDate());
			SQLPARAMS_PUSH(studentParams, "ull", uint64_t, id);
			updatedRows += sqlSession->executeUpdate(studentSql, studentParams);

			SqlParams userParams;
			string userSql =
				"UPDATE `user` u "
				"INNER JOIN `student` s ON s.`user_id` = u.`id` "
				"SET u.`name` = COALESCE(NULLIF(?, ''), u.`name`), "
				"    u.`mobile` = COALESCE(NULLIF(?, ''), u.`mobile`) "
				"WHERE s.`id` = ? AND s.`deleted` = 0";
			SQLPARAMS_PUSH(userParams, "s", string, row.getParentName());
			SQLPARAMS_PUSH(userParams, "s", string, row.getMobile());
			SQLPARAMS_PUSH(userParams, "ull", uint64_t, id);
			sqlSession->executeUpdate(userSql, userParams);
		}
		sqlSession->commitTransaction();
	}
	catch (...) {
		sqlSession->rollbackTransaction();
		throw;
	}

	return updatedRows;
}


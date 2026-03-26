#include "stdafx.h"
#include "IntendedStudentDAO.h"

std::list<PtrStudentDetail> IntendedExportDAO::selectByIds(const std::vector<std::string>& ids)
{
    if (ids.empty()) return {};

    SqlParams params;
    std::string sql = R"(
		SELECT 
			s.id, s.name, s.gender,
			u.mobile, u.name,
			s.family_rel,
			o.name,
			cg.name,
			s.birthday,
			st.name
		FROM student s
		LEFT JOIN user u ON s.user_id = u.id
		LEFT JOIN org o ON s.school_id = o.id
		LEFT JOIN class_grade cg ON s.grade_id = cg.id
		LEFT JOIN staff st ON s.counselor = st.id
		WHERE s.id IN (
	)";

    for (size_t i = 0; i < ids.size(); ++i) {
        if (i > 0) sql += ",";
        sql += "?";
        SQLPARAMS_PUSH(params, "s", std::string, ids[i]);
    }
    sql += ")";


    return sqlSession->executeQuery<PtrStudentDetail>(sql, PtrIntendedExportMapper(), params);
}

// ==================== User 表操作实现 ====================
uint64_t IntendedImportDAO::selectUserIdByMobile(const std::string& mobile, SqlSession* session)
{
    SqlParams params;
    SQLPARAMS_PUSH(params, "s", std::string, mobile);
    std::string sql = "SELECT id FROM user WHERE mobile = ? AND state = 1 LIMIT 1";
    return session->executeQueryNumerical(sql, params);
}

bool IntendedImportDAO::restoreUserIfDisabled(const std::string& mobile, SqlSession* session)
{
    SqlParams params;
    SQLPARAMS_PUSH(params, "s", std::string, mobile);
    std::string sql = "UPDATE user SET state = 1 WHERE mobile = ? AND state = 0";
    return session->executeUpdate(sql, params) > 0;
}

int IntendedImportDAO::insertUser(const ExcelUserDO& user, SqlSession* session)
{
    if (restoreUserIfDisabled(user.getMobile(), session)) {
        // 恢复成功，返回0让上层重新查询获取id
        return 0;
    }

    SqlParams params;
    SQLPARAMS_PUSH(params, "s", std::string, user.getId());
    SQLPARAMS_PUSH(params, "s", std::string, user.getMobile());
    SQLPARAMS_PUSH(params, "s", std::string, user.getPassword());
    if (!user.getName().empty()) {
        SQLPARAMS_PUSH(params, "s", std::string, user.getName());
    }
    else {
        SQLPARAMS_PUSH(params, "nul", int, 0);
    }

    std::string sql = "INSERT INTO user (id, mobile, password, name, state) VALUES (?, ?, ?, ?, 1)";

    return session->executeUpdate(sql, params);
}

// ==================== Student 表操作实现 ====================

int IntendedImportDAO::insertStudent(const ExcelStudentDO& student, SqlSession* session)
{
    SqlParams params;
    SQLPARAMS_PUSH(params, "s", std::string, student.getId());
    SQLPARAMS_PUSH(params, "s", std::string, student.getUserId());
    SQLPARAMS_PUSH(params, "s", std::string, student.getName());

    if (student.getGender() >= 0) {
        SQLPARAMS_PUSH(params, "i", int, student.getGender());
    }
    else {
        SQLPARAMS_PUSH(params, "nul", int, 0);
    }
    if (!student.getBirthday().empty()) {
        SQLPARAMS_PUSH(params, "s", std::string, student.getBirthday());
    }
    else {
        SQLPARAMS_PUSH(params, "nul", int, 0);
    }
    if (!student.getIdcard().empty()) {
        SQLPARAMS_PUSH(params, "s", std::string, student.getIdcard());
    }
    else {
        SQLPARAMS_PUSH(params, "nul", int, 0);
    }

    std::string sql =
        "INSERT INTO student (id, user_id, name, gender, birthday, idcard, stage, deleted) VALUES (?, ?, ?, ?, ?, ?, 0, 0)";
    return session->executeUpdate(sql, params);
}


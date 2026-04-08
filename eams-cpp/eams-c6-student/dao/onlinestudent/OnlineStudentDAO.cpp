#include "stdafx.h"
#include "OnlineStudentDAO.h"
#include "SimpleDateTimeFormat.h"

std::list<PtrStudentDetail> OnlineExportDAO::selectByIds(const std::vector<std::string>& ids)
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

	return sqlSession->executeQuery<PtrStudentDetail>(sql, PtrOnlineExportMapper(), params);
}

// 导入学员数据的实现
int OnlineImportDAO::importStudents(const std::vector<OnlineAddDTO::Wrapper>& students)
{
	if (students.empty()) return 0;

	int importedCount = 0;
	
	// 实现批量导入学员的逻辑
	for (const auto& student : students) {
		// 验证数据
		std::string errmsg = student->validate();
		if (!errmsg.empty()) {
			continue; // 跳过验证失败的记录
		}
		
		// 1. 创建用户记录
		SqlParams userParams;
		std::string userSql = R"(
			INSERT INTO user 
			(id, name, mobile, type, add_time, deleted) 
			VALUES (?, ?, ?, ?, ?, ?)
		)";
		string userId = "user_" + std::to_string(time(nullptr)) + "_" + std::to_string(importedCount);
		SQLPARAMS_PUSH(userParams, "s", std::string, userId);
		SQLPARAMS_PUSH(userParams, "s", std::string, *student->parent);
		SQLPARAMS_PUSH(userParams, "s", std::string, *student->mobile);
		SQLPARAMS_PUSH(userParams, "i", int, 2); // 2表示家长
		SQLPARAMS_PUSH(userParams, "s", std::string, SimpleDateTimeFormat::format());
		SQLPARAMS_PUSH(userParams, "i", int, 0);
		sqlSession->executeUpdate(userSql, userParams);
		
		// 2. 创建学员记录
		SqlParams studentParams;
		std::string studentSql = R"(
			INSERT INTO student 
			(id, user_id, name, gender, family_rel, school_id, grade_id, counselor, birthday, add_time, deleted) 
			VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
		)";
		string studentId = "student_" + std::to_string(time(nullptr)) + "_" + std::to_string(importedCount);
		SQLPARAMS_PUSH(studentParams, "s", std::string, studentId);
		SQLPARAMS_PUSH(studentParams, "s", std::string, userId);
		SQLPARAMS_PUSH(studentParams, "s", std::string, *student->name);
		SQLPARAMS_PUSH(studentParams, "i", int, *student->sex == "男" ? 1 : 0);
		SQLPARAMS_PUSH(studentParams, "i", int, 0); // 默认为本人
		SQLPARAMS_PUSH(studentParams, "s", std::string, ""); // 学校ID
		SQLPARAMS_PUSH(studentParams, "s", std::string, ""); // 年级ID
		SQLPARAMS_PUSH(studentParams, "s", std::string, ""); // 顾问ID
		SQLPARAMS_PUSH(studentParams, "s", std::string, ""); // 生日
		SQLPARAMS_PUSH(studentParams, "s", std::string, SimpleDateTimeFormat::format());
		SQLPARAMS_PUSH(studentParams, "i", int, 0);
		sqlSession->executeUpdate(studentSql, studentParams);
		
		importedCount++;
	}
	
	return importedCount;
}

// 修改学员顾问的实现
int OnlineStudentDAO::updateCounselor(const std::vector<std::string>& studentIds, const std::string& counselorName, const std::string& counselorId)
{
	if (studentIds.empty()) return 0;

	SqlParams params;
	std::string sql = "UPDATE student SET counselor = ?, counselor_name = ? WHERE id IN (";
	SQLPARAMS_PUSH(params, "s", std::string, counselorId);
	SQLPARAMS_PUSH(params, "s", std::string, counselorName);

	for (size_t i = 0; i < studentIds.size(); ++i) {
		if (i > 0) sql += ",";
		sql += "?";
		SQLPARAMS_PUSH(params, "s", std::string, studentIds[i]);
	}
	sql += ")";

	return sqlSession->executeUpdate(sql, params);
}
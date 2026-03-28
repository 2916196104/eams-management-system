#include "stdafx.h"
#include "OnlineStudentDAO.h"

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
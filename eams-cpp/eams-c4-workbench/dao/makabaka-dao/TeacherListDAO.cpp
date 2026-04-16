#include"stdafx.h"
#include"TeacherListDAO.h"
#include"TeacherListMapper.h"

std::string TeacherListDAO::queryConditonBuilder(const TeacherQuery::Wrapper& query, SqlParams& params) {
	stringstream sqlCondition;
	sqlCondition << " WHERE 1=1";
	if (query->name) {

		sqlCondition << " AND s.`name` LIKE CONCAT('%',?,'%')";
		SQLPARAMS_PUSH(params, "s", std::string, query->name.getValue(""));
	}
	return sqlCondition.str();
}

std::list<TeacherDTO::Wrapper> TeacherListDAO::selectWithPage(const TeacherQuery::Wrapper& query) {
	SqlParams params;
	//基础查询语句
	string sql = "SELECT s.id, s.name, o.position_id, p.name AS position_name \
				FROM staff s \
				LEFT JOIN staff_orginfo o ON o.staff_id = s.id \
				LEFT JOIN staff_position p ON o.position_id = p.id";
	//构建查询条件
	sql += queryConditonBuilder(query, params);
	//分页
	sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);
	return sqlSession->executeQuery<TeacherDTO::Wrapper>(sql, TeacherListMapper(), params);
}


uint64_t TeacherListDAO::count(const TeacherQuery::Wrapper& query) {
	SqlParams params;
	//基础查询语句
	string sql ="SELECT COUNT(*) AS count\
				FROM staff s \
				LEFT JOIN staff_orginfo o ON o.staff_id = s.id \
				LEFT JOIN staff_position p ON o.position_id = p.id";
	//构建查询条件
	sql += queryConditonBuilder(query, params);
	return sqlSession->executeQueryNumerical(sql, params);
}
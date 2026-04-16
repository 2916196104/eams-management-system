#include"stdafx.h"
#include"ClassListDAO.h"
#include"ClassListMapper.h"

std::string ClassListDAO::queryConditionBuilder(const ClassQuery::Wrapper& query, SqlParams& params) {
	stringstream sqlCondition;
	sqlCondition << " WHERE 1=1";
	if (query->name) {
		sqlCondition << " AND `name` LIKE CONCAT('%', ?, '%')";
		SQLPARAMS_PUSH(params, "s", std::string, query->name.getValue(""));
	}
	if (query->grade) {

		sqlCondition << " AND grade_id=?";
		SQLPARAMS_PUSH(params, "i", int, query->grade.getValue(0));
	}
	if (query->id) {

		sqlCondition << " AND id=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->id.getValue(""));
	}
	return sqlCondition.str();
}


uint64_t ClassListDAO::count(const ClassQuery::Wrapper& query) {
	SqlParams params;
	string sql = "SELECT COUNT(*) FROM class";
	//构建查询条件
	sql += queryConditionBuilder(query, params);
	//执行查询
	return sqlSession->executeQueryNumerical(sql, params);
}

//分页查询数据
std::list<ClassDO> ClassListDAO::selectWithPage(const ClassQuery::Wrapper& query) {
	SqlParams params;
	string sql = "SELECT id,name,grade_id FROM class";
	//构建查询条件
	sql += queryConditionBuilder(query, params);
	//构建排序语句
	sql += " ORDER BY grade_id ,name, id DESC";
	//构建分页条件
	sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);
	//执行查询
	return sqlSession->executeQuery<ClassDO>(sql, ClassListMapper(), params);
}

//通过姓名查询数据
std::list<ClassDO> ClassListDAO::selectByName(const string& name) {
	string sql = "SELECT id,`name`,grade_id FROM class WHERE `name` LIKE CONCAT('%',? ,'%')";
	return sqlSession->executeQuery<ClassDO>(sql, ClassListMapper(), "%s", name);	
}
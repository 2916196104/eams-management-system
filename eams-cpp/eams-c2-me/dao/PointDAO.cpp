#include "stdafx.h"
#include "PointDAO.h"
#include "PointMapper.h"

std::string PointDAO::queryConditionBuilder(const PointQuery::Wrapper& query, SqlParams& params)
{
	stringstream sqlCondition;
	sqlCondition << " WHERE 1=1";
	if (query->student_id) {

		sqlCondition << " AND `student_id`=?";
		SQLPARAMS_PUSH(params, "ll", int, query->student_id.getValue(0));
	}
	
	return sqlCondition.str();
}

uint64_t PointDAO::count(const PointQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT COUNT(*) FROM student_credit_log ";
	// 构建查询条件
	sql += queryConditionBuilder(query, params);
	// 执行查询
	return sqlSession->executeQueryNumerical(sql, params);
}

std::list<PointDO> PointDAO::selectWithPage(const PointQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT id,student_id,user_id,credit,current_credit, change_type, add_time, remark, source_id, staff_id, school_id FROM student_credit_log ";
	// 构建查询条件
	sql += queryConditionBuilder(query, params);
	// 构建排序语句
	sql += " ORDER BY IFNULL(`add_time`) DESC ";
	// 构建分页条件
	sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);

	// 执行查询
	return sqlSession->executeQuery<PointDO>(sql, PointMapper(), params);
}

//std::list<SampleDO> PointDAO::selectByName(const string& name)
//{
//	string sql = "SELECT id, student_id, user_id, credit, current_credit, 
//		change_type, add_time, remark, source_id, staff_id, school_id FROM sample WHERE `name` LIKE CONCAT('%',?,'%')";
//	return sqlSession->executeQuery<PointDO>(sql, PointMapper(), "%s", name);
//}

//std::shared_ptr<PointDO> PointDAO::selectById(std::string id)
//{
//	string sql = "SELECT id, student_id, user_id, credit, current_credit, 
//		change_type, add_time, remark, source_id, staff_id, school_id FROM student_credit_log WHERE `id`=?";
//	return sqlSession->executeQueryOne<std::shared_ptr<PointDO>>(sql, PtrSampleMapper(), "%s", id);
//}
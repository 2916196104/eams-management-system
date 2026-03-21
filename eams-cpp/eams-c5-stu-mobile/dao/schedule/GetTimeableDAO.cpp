#include "stdafx.h"
#include "GetTimeableDAO.h"
#include "GetTimeableMapper.h"

std::string GetTimeableDAO::queryConditionBuilder(const GetTimeableQuery::Wrapper& query, SqlParams& params)
{
	stringstream sqlCondition;
	sqlCondition << " WHERE 1=1";
	/*if (query->name) {

		sqlCondition << " AND `name`=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->name.getValue(""));
	}
	if (query->sex) {

		sqlCondition << " AND sex=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->sex.getValue(""));
	}
	if (query->age) {

		sqlCondition << " AND age=?";
		SQLPARAMS_PUSH(params, "i", int, query->age.getValue(0));
	}*/

	/*if (query->name) {
		sqlCondition << " AND `name`=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->name.getValue(""));
	}*/
	//学生id
	if (query->student_id) {
		sqlCondition << " AND `student_id`=?";
		SQLPARAMS_PUSH(params, "i", int, query->student_id.getValue(0));
	}
	//日期(奇怪了，怎么数据库里没有课程日期的)
	if (query->date) {
		sqlCondition << " AND date=?";
		SQLPARAMS_PUSH(params, "s",std::string , query->date.getValue(""));
	}
	return sqlCondition.str();
}

//uint64_t GetTimeableDAO::count(const GetTimeableQuery::Wrapper& query)
//{
//	SqlParams params;
//	string sql = "SELECT COUNT(*) FROM sample ";
//	// 构建查询条件
//	sql += queryConditionBuilder(query, params);
//	// 执行查询
//	return sqlSession->executeQueryNumerical(sql, params);
//}
uint64_t GetTimeableDAO::count(const GetTimeableQuery::Wrapper& query)
{
	SqlParams params;
	// 关联表与selectWithPage完全一致：lesson_student + lesson + lesson_teacher + staff
	string sql = "SELECT COUNT(DISTINCT lesson.id) "
		"FROM lesson_student "
		"JOIN lesson ON lesson_student.lesson_id = lesson.id "
		"JOIN lesson_teacher ON lesson.id = lesson_teacher.lesson_id "
		"JOIN staff ON lesson_teacher.teacher_id = staff.id "
		"WHERE DATE(lesson.date) = CURDATE() "
		"AND lesson.deleted = 0 ";

	sql += queryConditionBuilder(query, params);
	return sqlSession->executeQueryNumerical(sql, params);
}
//std::list<GetTimeableDO> GetTimeableDAO::selectWithPage(const GetTimeableQuery::Wrapper& query)
//{
//	SqlParams params;
//	string sql = "SELECT id,name,sex,age FROM sample ";
//	// 构建查询条件
//	sql += queryConditionBuilder(query, params);
//	// 构建排序语句
//	sql += " ORDER BY IFNULL(`update_time`, `create_time`) DESC, `id` DESC ";
//	// 构建分页条件
//	sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);
//
//	// 执行查询
//	return sqlSession->executeQuery<GetTimeableDO>(sql, GetTimeableMapper(), params);
//}
std::list<GetTimeableDO> GetTimeableDAO::selectWithPage(const GetTimeableQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT "
		"lesson.id, "
		"lesson.title, "
		"lesson.sn, "
		"lesson.date, "
		"lesson.start_time, "
		"lesson.end_time, "
		"lesson_teacher.teacher_id, "
		"lesson.schedule_id, "
		"staff.name, " 
		"lesson_student.sign_state "
		"FROM lesson_student "
		"JOIN lesson ON lesson_student.lesson_id = lesson.id "
		"JOIN lesson_teacher ON lesson.id = lesson_teacher.lesson_id "
		"JOIN staff ON lesson_teacher.teacher_id = staff.id "  
		"WHERE DATE(lesson.date) = CURDATE() "
		"AND lesson.deleted = 0 ";

	sql += queryConditionBuilder(query, params);
	sql += " ORDER BY lesson.edit_time DESC, lesson.id DESC ";
	sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);

	return sqlSession->executeQuery<GetTimeableDO>(sql, GetTimeableMapper(), params);
}
//std::list<GetTimeableDO> GetTimeableDAO::selectByName(const string& name)
//{
//	string sql = "SELECT id,name,sex,age FROM sample WHERE `name` LIKE CONCAT('%',?,'%')";
//	return sqlSession->executeQuery<GetTimeableDO>(sql, GetTimeableMapper(), "%s", name);
//}
//
//PtrGetTimeableDO GetTimeableDAO::selectById(std::string id)
//{
//	string sql = "SELECT id,name,sex,age FROM sample WHERE `id`=?";
//	return sqlSession->executeQueryOne<PtrGetTimeableDO>(sql, PtrGetTimeableMapper(), "%s", id);
//}
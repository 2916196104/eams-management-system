#include "stdafx.h"
#include "GetTimeableDAO.h"
#include "GetTimeableMapper.h"

std::string GetTimeableDAO::queryConditionBuilder(const GetTimeableQuery::Wrapper& query, SqlParams& params)
{
	stringstream sqlCondition;
	sqlCondition << " WHERE 1=1";

	// 学生id
	if (query->student_id) {
		sqlCondition << " AND `student_id`=?";
		SQLPARAMS_PUSH(params, "i", int, query->student_id.getValue(0));
	}
	// 日期（使用传入的参数，不再硬编码）
	if (query->date) {
		sqlCondition << " AND DATE(lesson.date) = ?";  // 统一格式为日期
		SQLPARAMS_PUSH(params, "s", std::string, query->date.getValue(""));
	}
	// 补充 deleted 条件（和原代码对齐）
	sqlCondition << " AND lesson.deleted = 0";

	return sqlCondition.str();
}

uint64_t GetTimeableDAO::count(const GetTimeableQuery::Wrapper& query)
{
	SqlParams params;
	// 移除硬编码的 CURDATE() 和 deleted=0，交给 queryConditionBuilder 处理
	string sql = "SELECT COUNT(DISTINCT lesson.id) "
		"FROM lesson_student "
		"JOIN lesson ON lesson_student.lesson_id = lesson.id "
		"JOIN lesson_teacher ON lesson.id = lesson_teacher.lesson_id "
		"JOIN staff ON lesson_teacher.teacher_id = staff.id ";

	// 直接拼接条件（包含 student_id 和 date）
	sql += queryConditionBuilder(query, params);
	return sqlSession->executeQueryNumerical(sql, params);
}
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
        "JOIN staff ON lesson_teacher.teacher_id = staff.id ";

    // 1. 移除硬编码的 WHERE 条件，复用统一的条件构建器
    sql += queryConditionBuilder(query, params);

    // 2. 排序（保留原逻辑）
    sql += " ORDER BY lesson.edit_time DESC, lesson.id DESC ";

    // 3. 分页（保留原逻辑，注意参数合法性）
    int pageIndex = query->pageIndex.getValue(1);
    int pageSize = query->pageSize.getValue(10);
    sql += " LIMIT " + std::to_string(((pageIndex - 1) * pageSize)) + "," + std::to_string(pageSize);

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
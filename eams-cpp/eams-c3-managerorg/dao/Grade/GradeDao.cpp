#include "stdafx.h"
#include "GradeDao.h"
#include "GradeMapper.h"

/**
 * 查询条件构建器
 * 根据 GradeManageQuery 中的 item 字段按考核项标题筛选
 */
std::string GradeDao::queryConditionBuilder(const GradeManageQuery::Wrapper& query, SqlParams& params)
{
	stringstream sqlCondition;

    sqlCondition << " WHERE 1=1";
	// grade 表逻辑删除过滤
	sqlCondition << " AND g.deleted=0";
	// 按考核项标题筛选
	if (query->item)
	{
		sqlCondition << " AND g.title=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->item.getValue(""));
	}
	return sqlCondition.str();
}

/**
 * 联查三表的公共 FROM + JOIN 部分
 */

static const char* GRADE_JOIN_SQL =
	"FROM grade g "
	"INNER JOIN grade_record gr ON g.id = gr.grade_id "
	"INNER JOIN student s ON gr.student_id = s.id ";
/**
 * 统计满足条件的数据条数
 */
uint64_t GradeDao::count(const GradeManageQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT COUNT(*) ";
	sql += GRADE_JOIN_SQL;
	sql += queryConditionBuilder(query, params);
	return sqlSession->executeQueryNumerical(sql, params);
}

/**
 * 分页查询成绩列表（联查 grade + grade_record + student）
 * SQL 字段顺序与 GradeManageMapper 一一对应：
 *   gr.id, g.title, gr.score, s.name
 */
std::list<GradeDO> GradeDao::selectWithPage(const GradeManageQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT gr.id, g.title, gr.score, s.name ";
	sql += GRADE_JOIN_SQL;
	sql += queryConditionBuilder(query, params);
	sql += " ORDER BY gr.add_time DESC, gr.id DESC";
	sql += " LIMIT " + std::to_string((query->pageIndex - 1) * query->pageSize) + "," + std::to_string(query->pageSize);
	return sqlSession->executeQuery<GradeDO>(sql, GradeManageMapper(), params);
}

/**
 * 根据考核项标题查询 grade.id
 * @param title 考核项标题
 * @return grade.id，未找到返回 0
 */
int64_t GradeDao::selectGradeIdByTitle(const std::string& title)
{
	SqlParams params;
	string sql = "SELECT id FROM grade WHERE title=? AND deleted=0 LIMIT 1";
	SQLPARAMS_PUSH(params, "s", std::string, title);
	return sqlSession->executeQueryNumerical(sql, params);
}

/**
 * 根据学生姓名查询 student.id
 * @param name 学生姓名
 * @return student.id，未找到返回 0
 */
int64_t GradeDao::selectStudentIdByName(const std::string& name)
{
	SqlParams params;
	string sql = "SELECT id FROM student WHERE name=? AND deleted=0 LIMIT 1";
	SQLPARAMS_PUSH(params, "s", std::string, name);
	return sqlSession->executeQueryNumerical(sql, params);
}

/**
 * 新增一条成绩记录（插入 grade_record 表）
 */
uint64_t GradeDao::insertRecord(const GradeRecordDO& record)
{
	string sql = "INSERT INTO grade_record (id, grade_id, student_id, score, add_time, creator) VALUES (?, ?, ?, ?, NOW(), ?)";
	return sqlSession->executeUpdate(sql, "%ull%ull%ull%i%ull",
		record.getId(), record.getGradeId(), record.getStudentId(),
		(int)record.getScore(), record.getCreator());
}

/**
 * 批量删除成绩记录（根据 grade_record.id 列表删除）
 */
bool GradeDao::deleteRecordByIds(const std::list<std::string>& ids)
{
	// 构建 IN (?, ?, ...) 占位符
	stringstream placeholders;
	for (size_t i = 0; i < ids.size(); i++)
	{
		if (i > 0) placeholders << ",";
		placeholders << "?";
	}
	string sql = "DELETE FROM grade_record WHERE id IN (" + placeholders.str() + ")";
	// 构建参数
	string paramFormat;
	for (size_t i = 0; i < ids.size(); i++)
	{
		paramFormat += "%s";
	}
	// 使用 SqlParams 传递参数
	SqlParams params;
	for (const auto& id : ids)
	{
		SQLPARAMS_PUSH(params, "s", std::string, id);
	}
	return sqlSession->executeUpdate(sql, params) > 0;
}

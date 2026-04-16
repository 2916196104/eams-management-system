#include "ClassDao.h"

#include <sstream>

uint64_t ClassDao::count(const ClassQuery::Wrapper& query)
{
	SqlParams params;
	std::string whereSql = queryConditionBuilder(query, params);
	std::string sql = "SELECT COUNT(1) FROM class" + whereSql;
	return sqlSession->executeQueryNumerical(sql, params);
}

std::list<ClassDO> ClassDao::selectWithPage(const ClassQuery::Wrapper& query)
{
	SqlParams params;
	std::string whereSql = queryConditionBuilder(query, params);

	v_uint64 pageIndex = query && query->pageIndex ? query->pageIndex.getValue(1) : static_cast<v_uint64>(1);
	v_uint64 pageSize = query && query->pageSize ? query->pageSize.getValue(10) : static_cast<v_uint64>(10);
	if (pageIndex == 0)
	{
		pageIndex = 1;
	}
	if (pageSize == 0)
	{
		pageSize = 10;
	}
	v_uint64 offset = (pageIndex - 1) * pageSize;

	SQLPARAMS_PUSH(params, "ull", uint64_t, offset);
	SQLPARAMS_PUSH(params, "ull", uint64_t, pageSize);

	std::ostringstream sql;
	sql << "SELECT id, name, course_id, classroom_id, creator, editor, add_time, edit_time, deleted, teacher_id, "
		<< "remark, be_over, over_time, over_operator, start_date, end_date, planned_student_count, "
		<< "planned_lesson_count, school_id, org_id, grade_id "
		<< "FROM class" << whereSql << " ORDER BY id DESC LIMIT ?, ?";

	return sqlSession->executeQuery<ClassDO, ClassMapper>(sql.str(), ClassMapper(), params);
}

PtrClassDO ClassDao::selectById(uint64_t id)
{
	std::string sql =
		"SELECT id, name, course_id, classroom_id, creator, editor, add_time, edit_time, deleted, teacher_id, "
		"remark, be_over, over_time, over_operator, start_date, end_date, planned_student_count, "
		"planned_lesson_count, school_id, org_id, grade_id "
		"FROM class WHERE id = ? LIMIT 1";

	ClassDO data = sqlSession->executeQueryOne<ClassDO, ClassMapper>(sql, ClassMapper(), "%ull", id);
	if (!data.getIdPtr())
	{
		return nullptr;
	}

	return std::make_shared<ClassDO>(std::move(data));
}

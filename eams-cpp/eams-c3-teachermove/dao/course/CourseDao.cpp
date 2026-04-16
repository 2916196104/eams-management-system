#include "CourseDao.h"
#include "CourseMapper.h"

#include <sstream>

uint64_t CourseDao::count(const CourseQuery::Wrapper& query)
{
	SqlParams params;
	std::string whereSql = queryConditionBuilder(query, params);
	std::string sql = "SELECT COUNT(1) FROM course" + whereSql;
	return sqlSession->executeQueryNumerical(sql, params);
}

std::list<CourseDO> CourseDao::selectWithPage(const CourseQuery::Wrapper& query)
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
	sql << "SELECT id, subject_id, name, state, info, creator, editor, add_time, edit_time, expire_months, "
		<< "unit_price, price, unit_name, discount, lesson_count, lesson_type, description, deleted, "
		<< "bookable, for_sale, recommend, cover, close_date, teacher_info, service_info, storage, org_id, "
		<< "salary, grade_ids, grade_names "
		<< "FROM course" << whereSql << " ORDER BY id DESC LIMIT ?, ?";

	return sqlSession->executeQuery<CourseDO, CourseMapper>(sql.str(), CourseMapper(), params);
}

PtrCourseDO CourseDao::selectById(uint64_t id)
{
	std::string sql =
		"SELECT id, subject_id, name, state, info, creator, editor, add_time, edit_time, expire_months, "
		"unit_price, price, unit_name, discount, lesson_count, lesson_type, description, deleted, "
		"bookable, for_sale, recommend, cover, close_date, teacher_info, service_info, storage, org_id, "
		"salary, grade_ids, grade_names "
		"FROM course WHERE id = ? AND deleted = 0 LIMIT 1";

	CourseDO data = sqlSession->executeQueryOne<CourseDO, CourseMapper>(sql, CourseMapper(), "%ull", id);
	if (!data.getIdPtr())
	{
		return nullptr;
	}

	return std::make_shared<CourseDO>(std::move(data));
}

uint64_t CourseDao::insert(const CourseDO& data)
{
	return BaseDAO::insert(data);
}

uint64_t CourseDao::update(const CourseDO& data)
{
	return BaseDAO::update(data);
}

uint64_t CourseDao::deleteById(uint64_t id)
{
	std::string sql = "UPDATE course SET deleted = 1 WHERE id = ?";
	return sqlSession->executeUpdate(sql, "%ull", id);
}

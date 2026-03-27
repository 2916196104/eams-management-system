#include "ClassroomDao.h"
#include "ClassroomMapper.h"

#include <sstream>

uint64_t ClassroomDao::count(const ClassroomQuery::Wrapper& query)
{
	SqlParams params;
	std::string whereSql = queryConditionBuilder(query, params);
	std::string sql = "SELECT COUNT(1) FROM classroom" + whereSql;
	return sqlSession->executeQueryNumerical(sql, params);
}

std::list<ClassroomDO> ClassroomDao::selectWithPage(const ClassroomQuery::Wrapper& query)
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
	sql << "SELECT id, name, address, area, remark, creator, editor, add_time, edit_time, deleted, school_id, org_id "
		<< "FROM classroom" << whereSql << " ORDER BY id DESC LIMIT ?, ?";

	return sqlSession->executeQuery<ClassroomDO, ClassroomMapper>(sql.str(), ClassroomMapper(), params);
}

PtrClassroomDO ClassroomDao::selectById(uint64_t id)
{
	std::string sql =
		"SELECT id, name, address, area, remark, creator, editor, add_time, edit_time, deleted, school_id, org_id "
		"FROM classroom WHERE id = ? LIMIT 1";

	ClassroomDO data = sqlSession->executeQueryOne<ClassroomDO, ClassroomMapper>(sql, ClassroomMapper(), "%ull", id);
	if (!data.getIdPtr())
	{
		return nullptr;
	}

	return std::make_shared<ClassroomDO>(std::move(data));
}

uint64_t ClassroomDao::insert(const ClassroomDO& data)
{
	return BaseDAO::insert(data);
}

uint64_t ClassroomDao::update(const ClassroomDO& data)
{
	return BaseDAO::update(data);
}

uint64_t ClassroomDao::deleteById(uint64_t id)
{
	std::string sql = "UPDATE classroom SET deleted = 1 WHERE id = ?";
	return sqlSession->executeUpdate(sql, "%ull", id);
}

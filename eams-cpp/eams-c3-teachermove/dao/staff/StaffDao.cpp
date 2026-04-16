#include "StaffDao.h"

#include <sstream>

uint64_t StaffDao::count(const StaffQuery::Wrapper& query)
{
	SqlParams params;
	std::string whereSql = queryConditionBuilder(query, params);
	std::string sql = "SELECT COUNT(1) FROM staff" + whereSql;
	return sqlSession->executeQueryNumerical(sql, params);
}

std::list<StaffDO> StaffDao::selectWithPage(const StaffQuery::Wrapper& query)
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
	sql << "SELECT id, name, mobile, wx_access_id, email, birthday, gender, id_card, school, degree, remark, state, "
		<< "is_manager, head_img, hire_date, fire_date, intro, add_time, edit_time, creator, editor, deleted, "
		<< "password, class_fee, assistant_fee, org_id, is_inner "
		<< "FROM staff" << whereSql << " ORDER BY id DESC LIMIT ?, ?";

	return sqlSession->executeQuery<StaffDO, StaffMapper>(sql.str(), StaffMapper(), params);
}

PtrStaffDO StaffDao::selectById(uint64_t id)
{
	std::string sql =
		"SELECT id, name, mobile, wx_access_id, email, birthday, gender, id_card, school, degree, remark, state, "
		"is_manager, head_img, hire_date, fire_date, intro, add_time, edit_time, creator, editor, deleted, "
		"password, class_fee, assistant_fee, org_id, is_inner "
		"FROM staff WHERE id = ? AND deleted = 0 LIMIT 1";

	StaffDO data = sqlSession->executeQueryOne<StaffDO, StaffMapper>(sql, StaffMapper(), "%ull", id);
	if (!data.getIdPtr())
	{
		return nullptr;
	}

	return std::make_shared<StaffDO>(std::move(data));
}

PtrStaffDO StaffDao::selectByMobile(const std::string& mobile)
{
	std::string sql =
		"SELECT id, name, mobile, wx_access_id, email, birthday, gender, id_card, school, degree, remark, state, "
		"is_manager, head_img, hire_date, fire_date, intro, add_time, edit_time, creator, editor, deleted, "
		"password, class_fee, assistant_fee, org_id, is_inner "
		"FROM staff WHERE mobile = ? AND deleted = 0 LIMIT 1";

	StaffDO data = sqlSession->executeQueryOne<StaffDO, StaffMapper>(sql, StaffMapper(), "%s", mobile);
	if (!data.getIdPtr())
	{
		return nullptr;
	}

	return std::make_shared<StaffDO>(std::move(data));
}

uint64_t StaffDao::insert(const StaffDO& data)
{
	return BaseDAO::insert(data);
}

uint64_t StaffDao::update(const StaffDO& data)
{
	return BaseDAO::update(data);
}

uint64_t StaffDao::deleteById(uint64_t id)
{
	std::string sql = "UPDATE staff SET deleted = 1 WHERE id = ?";
	return sqlSession->executeUpdate(sql, "%ull", id);
}

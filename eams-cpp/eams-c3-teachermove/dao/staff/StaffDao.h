#pragma once
#ifndef _STAFF_DAO_H_
#define _STAFF_DAO_H_

#include "BaseDAO.h"
#include "dao/staff/StaffMapper.h"
#include "domain/do/staff/StaffDO.h"
#include "domain/query/staff/StaffQuery.h"

#include <memory>
#include <string>

using PtrStaffDO = std::shared_ptr<StaffDO>;

class StaffDao : public BaseDAO
{
private:
	inline std::string queryConditionBuilder(const StaffQuery::Wrapper& query, SqlParams& params)
	{
		std::string whereSql = " WHERE deleted = 0";
		if (!query)
		{
			return whereSql;
		}

		if (query->name && !query->name->empty())
		{
			whereSql += " AND name LIKE ?";
			SQLPARAMS_PUSH(params, "s", std::string, "%" + query->name.getValue("") + "%");
		}

		if (query->mobile && !query->mobile->empty())
		{
			whereSql += " AND mobile = ?";
			SQLPARAMS_PUSH(params, "s", std::string, query->mobile.getValue(""));
		}

		if (query->state && !query->state->empty())
		{
			whereSql += " AND state = ?";
			SQLPARAMS_PUSH(params, "i", int32_t, std::stoi(query->state.getValue("0")));
		}

		if (query->is_manager && !query->is_manager->empty())
		{
			whereSql += " AND is_manager = ?";
			SQLPARAMS_PUSH(params, "i", int32_t, std::stoi(query->is_manager.getValue("0")));
		}

		if (query->org_id && !query->org_id->empty())
		{
			whereSql += " AND org_id = ?";
			SQLPARAMS_PUSH(params, "ll", int64_t, std::stoll(query->org_id.getValue("0")));
		}

		return whereSql;
	}

public:
	uint64_t count(const StaffQuery::Wrapper& query);
	std::list<StaffDO> selectWithPage(const StaffQuery::Wrapper& query);
	PtrStaffDO selectById(uint64_t id);
	PtrStaffDO selectByMobile(const std::string& mobile);
	uint64_t insert(const StaffDO& data);
	uint64_t update(const StaffDO& data);
	uint64_t deleteById(uint64_t id);
};

#endif // !_STAFF_DAO_H_

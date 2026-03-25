#pragma once
#ifndef _STAFFSERVICE_H_
#define _STAFFSERVICE_H_
#include "domain/query/staff/StaffQuery.h"
#include "domain/dto/staff/StaffDTO.h"
#include "domain/do/staff/StaffDO.h"

/**
 * 员工业务逻辑类
 */
class StaffService
{
private:

public:
	// 获取员工详情
	StaffDetailDTO::Wrapper getStaffDetail(const oatpp::String& id);

	// 通过ID删除数据
	bool batchDeleteStaff(const oatpp::List<oatpp::String>& ids);
};

#endif // !_STAFFSERVICE_H_

#pragma once
#ifndef _STAFFDAO_H_
#define	_STAFFDAO_H_
#include"BaseDAO.h"
#include "domain/dto/staff/StaffDTO.h"
#include "domain/query/staff/StaffQuery.h"
#include "domain/do/staff/StaffDO.h"

/**
 * 用户数据操作类
 */
class StaffDAO : public BaseDAO
{
public:
	PtrStaffDO selectById(const string& id);

	// 新增：批量逻辑删除员工（核心，适配批量删除业务）
	// 参数：员工ID列表；返回值：成功删除的记录数
	int batchDeleteByIds(const std::list<std::string>& ids);
};

#endif // !_STAFFDAO_H_


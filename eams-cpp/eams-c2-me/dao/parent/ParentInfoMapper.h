#pragma once

#ifndef _PARENTINFO_MAPPER_
#define _PARENTINFO_MAPPER_
#include "Mapper.h"
#include "domain/do/parent/ParentInfoDO.h"

/**
* ParentInfo数据映射器 - 返回智能指针版本
* 功能：将数据库查询结果映射为PtrSampleDO对象（智能指针）
*/
class PtrParentInfoMapper : public Mapper<PtrParentInfoDO> {
public:
	PtrParentInfoDO mapper(ResultSet* resultSet) const override {
		auto pid = std::make_shared<ParentInfoDO>();
		pid->setId(resultSet->getUInt64("id"));
		pid->setName(resultSet->getString("name"));
		pid->setMobile(resultSet->getString("Mobile"));
		pid->setState(resultSet->getInt("State"));
		pid->setPassword(resultSet->getString("Password"));
		pid->setDatetime(resultSet->getString("Datetime"));
		return pid;
	}
};

#endif // !_PARENTINFO_MAPPER_

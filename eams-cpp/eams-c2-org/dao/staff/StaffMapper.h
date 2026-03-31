#pragma once
#ifndef _STAFFMAPPER_H_
#define _STAFFMAPPER_H_
#include "Mapper.h"
#include "domain/do/staff/StaffDO.h"

class StaffMapper : public Mapper<PtrStaffDO>
{
public:
	PtrStaffDO mapper(ResultSet* resultSet) const override
	{
		PtrStaffDO staffDO = std::make_shared<StaffDO>();

		// bigint unsigned
		staffDO->setId(resultSet->getUInt64("id"));
		staffDO->setWxAccessId(resultSet->getUInt64("wx_access_id"));
		staffDO->setCreator(resultSet->getUInt64("creator"));
		staffDO->setEditor(resultSet->getUInt64("editor"));
		staffDO->setOrgId(resultSet->getUInt64("org_id"));

		// tinyint → 直接用 getInt 赋值给 int 类型
		staffDO->setGender(resultSet->getInt("gender"));
		staffDO->setDegree(resultSet->getInt("degree"));
		staffDO->setState(resultSet->getInt("state"));
		staffDO->setIsManager(resultSet->getInt("is_manager"));
		staffDO->setDeleted(resultSet->getInt("deleted"));
		staffDO->setIsInner(resultSet->getInt("is_inner"));

		// 字符串/小数
		staffDO->setName(resultSet->getString("name"));
		staffDO->setIdCard(resultSet->getString("id_card"));
		staffDO->setHeadImg(resultSet->getString("head_img"));
		staffDO->setMobile(resultSet->getString("mobile"));
		staffDO->setEmail(resultSet->getString("email"));
		staffDO->setBirthday(resultSet->getString("birthday"));
		staffDO->setSchool(resultSet->getString("school"));
		staffDO->setRemark(resultSet->getString("remark"));
		staffDO->setHireDate(resultSet->getString("hire_date"));
		staffDO->setFireDate(resultSet->getString("fire_date"));
		staffDO->setIntro(resultSet->getString("intro"));
		staffDO->setAddTime(resultSet->getString("add_time"));
		staffDO->setEditTime(resultSet->getString("edit_time"));
		staffDO->setPassword(resultSet->getString("password"));
		staffDO->setClassFee(resultSet->getDouble("class_fee"));
		staffDO->setAssistantFee(resultSet->getDouble("assistant_fee"));

		return staffDO;
	}
};

using PtrStaffMapper = std::shared_ptr<StaffMapper>;

#endif // !_STAFFMAPPER_H_
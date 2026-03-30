#pragma once
#ifndef _STAFFMAPPER_H_
#define _STAFFMAPPER_H_
#include "Mapper.h"
#include "domain/do/staff/StaffDO.h"

// 员工结果集映射器：将ResultSet转换为PtrStaffDO
class StaffMapper : public Mapper<PtrStaffDO>
{
public:
	PtrStaffDO mapper(ResultSet* resultSet) const override
	{
		PtrStaffDO staffDO = std::make_shared<StaffDO>();

		// ====================== 方案二修改核心 ======================
		// bigint unsigned 字段 → 使用 getUInt64 转为 uint64_t
		staffDO->setId(resultSet->getUInt64("id"));
		staffDO->setWxAccessId(resultSet->getUInt64("wx_access_id"));
		staffDO->setCreator(resultSet->getUInt64("creator"));
		staffDO->setEditor(resultSet->getUInt64("editor"));
		staffDO->setOrgId(resultSet->getUInt64("org_id"));

		// tinyint 字段 → 强转 char
		staffDO->setGender((char)resultSet->getInt("gender"));
		staffDO->setDegree((char)resultSet->getInt("degree"));
		staffDO->setState((char)resultSet->getInt("state"));
		staffDO->setIsManager((char)resultSet->getInt("is_manager"));
		staffDO->setDeleted((char)resultSet->getInt("deleted"));
		staffDO->setIsInner((char)resultSet->getInt("is_inner"));
		// ===========================================================

		// 字符串/日期/小数 保持不变
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
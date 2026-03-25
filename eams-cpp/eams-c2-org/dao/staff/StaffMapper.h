#pragma once
#pragma once
#ifndef _STAFFMAPPER_H_
#define _STAFFMAPPER_H_
#include "Mapper.h"
#include "domain/do/staff/StaffDO.h"  // 引入员工DO类

// 员工结果集映射器：将ResultSet转换为PtrStaffDO
class StaffMapper : public Mapper<PtrStaffDO>
{
public:
	PtrStaffDO mapper(ResultSet* resultSet) const override
	{
		// 1. 创建StaffDO智能指针对象
		PtrStaffDO staffDO = std::make_shared<StaffDO>();

		// 核心基础字段（必映射，保证数据完整）
		staffDO->setId(resultSet->getString("id"));
		staffDO->setName(resultSet->getString("name"));
		staffDO->setIdCard(resultSet->getString("id_card"));
		staffDO->setHeadImg(resultSet->getString("head_img"));
		staffDO->setDeleted(resultSet->getInt("deleted"));

		// 扩展字段（保证数据完整，映射数据库所有真实字段）
		staffDO->setMobile(resultSet->getString("mobile"));
		staffDO->setWxAccessId(resultSet->getString("wx_access_id"));
		staffDO->setEmail(resultSet->getString("email"));
		staffDO->setBirthday(resultSet->getString("birthday"));
		staffDO->setGender(resultSet->getInt("gender"));
		staffDO->setSchool(resultSet->getString("school"));
		staffDO->setDegree(resultSet->getInt("degree"));
		staffDO->setRemark(resultSet->getString("remark"));
		staffDO->setState(resultSet->getInt("state"));
		staffDO->setIsManager(resultSet->getInt("is_manager"));
		staffDO->setHireDate(resultSet->getString("hire_date"));
		staffDO->setFireDate(resultSet->getString("fire_date"));
		staffDO->setIntro(resultSet->getString("intro"));
		staffDO->setAddTime(resultSet->getString("add_time"));
		staffDO->setEditTime(resultSet->getString("edit_time"));
		staffDO->setCreator(resultSet->getString("creator"));
		staffDO->setEditor(resultSet->getString("editor"));
		staffDO->setPassword(resultSet->getString("password"));
		staffDO->setClassFee(resultSet->getDouble("class_fee"));
		staffDO->setAssistantFee(resultSet->getDouble("assistant_fee"));
		staffDO->setOrgId(resultSet->getString("org_id"));
		staffDO->setIsInner(resultSet->getInt("is_inner"));

		return staffDO;
	}
};

// 定义StaffMapper的智能指针（可选，简化DAO层调用）
using PtrStaffMapper = std::shared_ptr<StaffMapper>;

#endif // !_STAFFMAPPER_H_
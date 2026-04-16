#pragma once
#ifndef _STAFF_MAPPER_H_
#define _STAFF_MAPPER_H_

#include "Mapper.h"
#include "domain/do/staff/StaffDO.h"

class StaffMapper : public Mapper<StaffDO>
{
public:
	StaffDO mapper(ResultSet* resultSet) const override
	{
		StaffDO data;

		if (!resultSet->isNull("id")) data.setId(resultSet->getUInt64("id"));
		if (!resultSet->isNull("name")) data.setName(resultSet->getString("name"));
		if (!resultSet->isNull("mobile")) data.setMobile(resultSet->getString("mobile"));
		if (!resultSet->isNull("wx_access_id")) data.setWxAccessId(resultSet->getInt64("wx_access_id"));
		if (!resultSet->isNull("email")) data.setEmail(resultSet->getString("email"));
		if (!resultSet->isNull("birthday")) data.setBirthday(resultSet->getString("birthday"));
		if (!resultSet->isNull("gender")) data.setGender(resultSet->getInt("gender"));
		if (!resultSet->isNull("id_card")) data.setIdCard(resultSet->getString("id_card"));
		if (!resultSet->isNull("school")) data.setSchool(resultSet->getString("school"));
		if (!resultSet->isNull("degree")) data.setDegree(resultSet->getInt("degree"));
		if (!resultSet->isNull("remark")) data.setRemark(resultSet->getString("remark"));
		if (!resultSet->isNull("state")) data.setState(resultSet->getInt("state"));
		if (!resultSet->isNull("is_manager")) data.setIsManager(resultSet->getBoolean("is_manager"));
		if (!resultSet->isNull("head_img")) data.setHeadImg(resultSet->getString("head_img"));
		if (!resultSet->isNull("hire_date")) data.setHireDate(resultSet->getString("hire_date"));
		if (!resultSet->isNull("fire_date")) data.setFireDate(resultSet->getString("fire_date"));
		if (!resultSet->isNull("intro")) data.setIntro(resultSet->getString("intro"));
		if (!resultSet->isNull("add_time")) data.setAddTime(resultSet->getString("add_time"));
		if (!resultSet->isNull("edit_time")) data.setEditTime(resultSet->getString("edit_time"));
		if (!resultSet->isNull("creator")) data.setCreator(resultSet->getInt64("creator"));
		if (!resultSet->isNull("editor")) data.setEditor(resultSet->getInt64("editor"));
		if (!resultSet->isNull("deleted")) data.setDeleted(resultSet->getBoolean("deleted"));
		if (!resultSet->isNull("password")) data.setPassword(resultSet->getString("password"));
		if (!resultSet->isNull("class_fee")) data.setClassFee(resultSet->getDouble("class_fee"));
		if (!resultSet->isNull("assistant_fee")) data.setAssistantFee(resultSet->getDouble("assistant_fee"));
		if (!resultSet->isNull("org_id")) data.setOrgId(resultSet->getInt64("org_id"));
		if (!resultSet->isNull("is_inner")) data.setIsInner(resultSet->getBoolean("is_inner"));

		return data;
	}
};

#endif // !_STAFF_MAPPER_H_

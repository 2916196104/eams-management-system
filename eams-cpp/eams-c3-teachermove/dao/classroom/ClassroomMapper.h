#pragma once
#ifndef _CLASSROOM_MAPPER_H_
#define _CLASSROOM_MAPPER_H_

#include "Mapper.h"
#include "domain/do/classroom/ClassroomDO.h"

class ClassroomMapper : public Mapper<ClassroomDO>
{
public:
	ClassroomDO mapper(ResultSet* resultSet) const override
	{
		ClassroomDO data;

		if (!resultSet->isNull("id")) data.setId(resultSet->getUInt64("id"));
		if (!resultSet->isNull("name")) data.setName(resultSet->getString("name"));
		if (!resultSet->isNull("address")) data.setAddress(resultSet->getString("address"));
		if (!resultSet->isNull("area")) data.setArea(resultSet->getInt("area"));
		if (!resultSet->isNull("remark")) data.setRemark(resultSet->getString("remark"));
		if (!resultSet->isNull("creator")) data.setCreator(resultSet->getInt64("creator"));
		if (!resultSet->isNull("editor")) data.setEditor(resultSet->getInt64("editor"));
		if (!resultSet->isNull("add_time")) data.setAddTime(resultSet->getString("add_time"));
		if (!resultSet->isNull("edit_time")) data.setEditTime(resultSet->getString("edit_time"));
		if (!resultSet->isNull("deleted")) data.setDeleted(resultSet->getBoolean("deleted"));
		if (!resultSet->isNull("school_id")) data.setSchoolId(resultSet->getInt64("school_id"));
		if (!resultSet->isNull("org_id")) data.setOrgId(resultSet->getInt64("org_id"));

		return data;
	}
};

#endif // !_CLASSROOM_MAPPER_H_

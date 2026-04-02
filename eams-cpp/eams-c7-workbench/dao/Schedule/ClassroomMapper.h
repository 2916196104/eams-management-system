#pragma once
#ifndef _CLASSROOMMAPPER_H_
#define _CLASSROOMMAPPER_H_

#include "Mapper.h"
#include "domain/do/Schedule/ClassroomDO.h"

class ClassroomMapper :public Mapper<PtrClassroomDO>
{
public:
	PtrClassroomDO mapper(ResultSet* resultSet) const override
	{
		PtrClassroomDO clsroom = std::make_shared<ClassroomDO>();
		clsroom->setId(resultSet->getInt64("id")); // BIGINT UNSIGNED
		clsroom->setClsName(resultSet->getString("name"));
		clsroom->setClsAddress(resultSet->getString("address"));
		return clsroom;
	}
	
};

#endif 
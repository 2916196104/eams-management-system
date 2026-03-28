#pragma once

#ifndef _CLASSLISTMAPPER_H_
#define _CLASSLISTMAPPER_H_

#include"Mapper.h"
#include"../../domain/do/ClassDO.h"

class ClassListMapper :public Mapper<ClassDO> {
public:
	ClassDO mapper(ResultSet* resultSet) const override{
		ClassDO data;
		data.setId(resultSet->getString("id"));
		data.setName(resultSet->getString("name"));
		data.setGrade_id(resultSet->getInt("grade_id"));
		return data;
	}
};

#endif //!_CLASSLISTMAPPER_H_
#pragma once
#ifndef _CONFLICTIDDO_H_
#define _CONFLICTIDDO_H_
#include"Mapper.h"
#include"../../domain/do/ConflictIdDO.h"

/*
≥ÂÕªid¡–±ÌMapper
*/
class ConflictIdDOMapper : public Mapper<ConflictIdDO> {
public:
	ConflictIdDO mapper(ResultSet* resultSet) const override {
		ConflictIdDO data;
		data.setId(resultSet->getString("id"));
		return data;
	}
};

#endif // !_CONFLICTIDDO_H_
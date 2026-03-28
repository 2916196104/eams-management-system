#pragma once
#ifndef ROLLCALLRECORDMAPPER_H
#define ROLLCALLRECORDMAPPER_H
#include "Mapper.h"
#include "../../../domain/do/LessonStudentDO.h"

class RollcallrecordMapper : public Mapper<RollcallrecordViewDO>
{
public:
	RollcallrecordViewDO mapper(ResultSet* resultSet) const override
	{
		RollcallrecordViewDO data;
		//data.setId(resultSet->getInt(1));
		data.setStudentName(resultSet->getString(1));
		data.setSign_time(resultSet->getString(2));
		data.setSign_state(resultSet->getInt(3));
		
		return data;
	}
};


class PtrRollcallrecordMapper : public Mapper<PtrRollcallrecordViewDO>
{
public:
	PtrRollcallrecordViewDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<RollcallrecordViewDO>();
		data->setStudentName(resultSet->getString(1));
		data->setSign_time(resultSet->getString(2));
		data->setSign_state(resultSet->getInt(3));
		return data;
	}
};


#endif
#pragma once
#ifndef INTENDSTUDENTMAPPER_H
#define INTENDSTUDENTMAPPER_H
#include "../../../domain/do/StudentDO.h"

class IntendstudentMapper : public Mapper<StudentDO>
{
public:
	StudentDO mapper(ResultSet* resultSet) const override
	{
		StudentDO data;
		data.setId(resultSet->getUInt64(1));
		data.setName(resultSet->getString(2));
		//data.setWxAccessId(resultSet->getUInt64(3));
		data.setDeleted(resultSet->getInt(3));
		data.setGender(resultSet->getInt(4));
		data.setBirthday(resultSet->getString(5));
		data.setIdcard(resultSet->getString(6));
		data.setRemark(resultSet->getString(7));
		
		return data;
	}
};


class PtrIntendstudentMapper : public Mapper<PtrStudentDO>
{
public:
	PtrStudentDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<StudentDO>();
		data->setId(resultSet->getUInt64(1));
		data->setName(resultSet->getString(2));
		//data->setWxAccessId(resultSet->getUInt64(3));
		data->setDeleted(resultSet->getInt(3));
		data->setGender(resultSet->getInt(4));
		data->setBirthday(resultSet->getString(5));
		data->setIdcard(resultSet->getString(6));
		data->setRemark(resultSet->getString(7));
		return data;
	}
};

#endif
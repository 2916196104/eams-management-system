#pragma once
#ifndef _REGISTERMAPPER_H_
#define _REGISTERMAPPER_H_

#include "Mapper.h"
#include "../../domain/do/Course/RegisterDO.h"

class RegisterMapper : public Mapper<RegisterDO>
{
public:
	RegisterDO mapper(ResultSet* resultSet) const override
	{
		RegisterDO data;
		data.setId(resultSet->getInt64(1));
		data.setStudentId(resultSet->getInt64(2));
		data.setCourseId(resultSet->getInt64(3));
		data.setSubjectId(resultSet->getInt64(4));
		data.setStartDate(resultSet->getString(5));
		data.setExpireDate(resultSet->getString(6));
		data.setCountLessonTotal(resultSet->getInt(7));
		data.setAmount(resultSet->getDouble(8));
		data.setDiscountAmount(resultSet->getDouble(9));
		data.setPaidAmount(resultSet->getDouble(10));
		data.setRemark(resultSet->getString(11));
		return data;
	}
};

class PtrRegisterMapper : public Mapper<PtrRegisterDO>
{
public:
	PtrRegisterDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<RegisterDO>();
		data->setId(resultSet->getInt64(1));
		data->setStudentId(resultSet->getInt64(2));
		data->setCourseId(resultSet->getInt64(3));
		data->setSubjectId(resultSet->getInt64(4));
		data->setStartDate(resultSet->getString(5));
		data->setExpireDate(resultSet->getString(6));
		data->setCountLessonTotal(resultSet->getInt(7));
		data->setAmount(resultSet->getDouble(8));
		data->setDiscountAmount(resultSet->getDouble(9));
		data->setPaidAmount(resultSet->getDouble(10));
		data->setRemark(resultSet->getString(11));
		return data;
	}
};

#endif
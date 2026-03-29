#pragma once
#ifndef CLASSDETAILMAPPER_H_
#define CLASSDETAILMAPPER_H_
#include"BaseDAO.h"
#include"Mapper.h"
#include"../../domain/do/ViewDO/ClassDetailDO.h"

class ClassDetailMapper :public Mapper<ClassDetailDO>
{
public:
	ClassDetailDO mapper(ResultSet* resultSet)const override
	{
		ClassDetailDO data;
		data.setClassName(resultSet->getString(1));
		data.setStaffName(resultSet->getString(2));
		data.setCourseName(resultSet->getString(3));
		data.setStartDate(resultSet->getString(4));
		data.setEndDate(resultSet->getString(5));
		data.setPlanedStudentCount(resultSet->getInt(6));
		data.setRemark(resultSet->getString(7));
		data.setBeOver(resultSet->getInt(8));
		data.setCourseLessons(resultSet->getInt(9));
		return data;
	}
};
class PtrClassDetailMapper :public Mapper<PtrClassDetailDO>
{
public:
	PtrClassDetailDO mapper(ResultSet* resultSet)const override
	{
		auto data = std::make_shared<ClassDetailDO>();
		data->setClassName(resultSet->getString(1));
		data->setStaffName(resultSet->getString(2));
		data->setCourseName(resultSet->getString(3));
		data->setStartDate(resultSet->getString(4));
		data->setEndDate(resultSet->getString(5));
		data->setPlanedStudentCount(resultSet->getInt(6));
		data->setRemark(resultSet->getString(7));
		data->setBeOver(resultSet->getInt(8));
		data->setCourseLessons(resultSet->getInt(9));
		return data;
	}
};
#endif // !CLASSDETAIL_H_

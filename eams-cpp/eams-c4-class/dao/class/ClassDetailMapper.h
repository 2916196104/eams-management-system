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
		data.setRoomName(resultSet->getString(3));
		data.setCourseName(resultSet->getString(4));
		data.setStartDate(resultSet->getString(5));
		data.setEndDate(resultSet->getString(6));
		data.setPlanedStudentCount(resultSet->getInt(7));
		data.setRemark(resultSet->getString(8));
		data.setBeOver(resultSet->getInt(9));
		data.setCourseLessons(resultSet->getInt(10));
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
		data->setRoomName(resultSet->getString(3));
		data->setCourseName(resultSet->getString(4));
		data->setStartDate(resultSet->getString(5));
		data->setEndDate(resultSet->getString(6));
		data->setPlanedStudentCount(resultSet->getInt(7));
		data->setRemark(resultSet->getString(8));
		data->setBeOver(resultSet->getInt(9));
		data->setCourseLessons(resultSet->getInt(10));
		return data;
	}
};
#endif // !CLASSDETAIL_H_

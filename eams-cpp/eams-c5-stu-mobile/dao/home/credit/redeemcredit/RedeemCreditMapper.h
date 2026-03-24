#pragma once


#ifndef _REDEEMCREDIT_MAPPER_
#define _REDEEMCREDIT_MAPPER_

#include "Mapper.h"
#include "../../../../domain/do/home/credit/redeemcredit/RedeemCreditDO.h"
 
class StudentCreditMapper : public Mapper<StudentCreditDO>
{
public:
	StudentCreditDO mapper(ResultSet* resultSet) const override
	{
		StudentCreditDO data;
		data.setCredit(resultSet->getInt(1));
		return data;
	}
};

class PtrStudentCreditMapper : public Mapper<PtrStudentCreditDO>
{
public:
	PtrStudentCreditDO mapper(ResultSet* resultSet) const override
	{
		auto data= std::make_shared<StudentCreditDO>();
		data->setCredit(resultSet->getInt(1));
		return data;
	}
};

class CreditMallMapper : public Mapper<CreditMallDO>
{
public:
	CreditMallDO mapper(ResultSet* resultSet) const override
	{
		CreditMallDO data;
		data.setMaritalId(resultSet->getUInt64(1));
		data.setCredit(resultSet->getInt(2));
		data.setState(resultSet->getBoolean(3));
		data.setName(resultSet->getString(4));
		return data;
	}
};

class PtrCreditMallMapper : public Mapper<PtrCreditMallDO>
{
public:
	PtrCreditMallDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<CreditMallDO>();
		data->setMaritalId(resultSet->getUInt64(1));
		data->setCredit(resultSet->getInt(2));
		data->setState(resultSet->getBoolean(3));
		data->setName(resultSet->getString(4));
		return data;
	}
};


class PtrMaterialMapper : public Mapper<PtrMaterialDO>
{
public:
	PtrMaterialDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<MaterialDO>();
		data->setSchoolId(resultSet->getUInt64(1));
		return data;
	}

};
#endif
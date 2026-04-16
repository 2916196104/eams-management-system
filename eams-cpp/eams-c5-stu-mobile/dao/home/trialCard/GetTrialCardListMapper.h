#pragma once
#ifndef _GETTRIALCARDLIST_MAPPER_H_
#define _GETTRIALCARDLIST_MAPPER_H_

#include "Mapper.h"
#include "domain/do/home/trialCard/GetTrialCardListDO.h"

class GetTrialCardListMapper : public Mapper<GetTrialCardListDO>
{
public:
	GetTrialCardListDO mapper(ResultSet* resultSet) const override
	{
		GetTrialCardListDO getTrialCardListDO;
		getTrialCardListDO.setName(resultSet->getString(1));
		getTrialCardListDO.setLessonCount(resultSet->getInt(2));
		getTrialCardListDO.setRemainingQuantity(resultSet->getInt(3));
		getTrialCardListDO.setEndTime(resultSet->getString(4));
		getTrialCardListDO.setCourseName(resultSet->getString(5));
		return getTrialCardListDO;
	}
};

class PtrGetTrialCardListMapper : public Mapper<PtrGetTrialCardListDO>
{
public:
	PtrGetTrialCardListDO mapper(ResultSet* resultSet) const override
	{
		PtrGetTrialCardListDO ptrGetTrialCardListDO = std::make_shared<GetTrialCardListDO>();
		ptrGetTrialCardListDO->setName(resultSet->getString(1));
		ptrGetTrialCardListDO->setLessonCount(resultSet->getInt(2));
		ptrGetTrialCardListDO->setRemainingQuantity(resultSet->getInt(3));
		ptrGetTrialCardListDO->setEndTime(resultSet->getString(4));
		ptrGetTrialCardListDO->setCourseName(resultSet->getString(5));
		return ptrGetTrialCardListDO;
	}
};

#endif // _GETTRIALCARDLISTDO_H_
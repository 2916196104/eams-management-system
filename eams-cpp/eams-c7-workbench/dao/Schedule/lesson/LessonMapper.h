#pragma once
#ifndef _LESSON_MAPPER_H_
#define _LESSON_MAPPER_H_
#include "Mapper.h"
#include "domain/do/Schedule/lesson/LessonDO.h"
#include "domain/do/Schedule/lesson/ConflictInfo.h"

class LessonMapper : public Mapper<LessonDO>
{
public:
	LessonDO mapper(ResultSet* resultSet) const override
	{
		LessonDO data;
		data.setId(resultSet->getInt64(1));
		data.setTitle(resultSet->getString(2));
		data.setSn(resultSet->getInt(3));
		data.setCourseId(resultSet->getInt64(4));
		data.setScheduleId(resultSet->getInt64(5));
		data.setClassId(resultSet->getInt64(6));
		data.setRoomId(resultSet->getInt64(7));
		data.setDate(resultSet->getString(8));
		data.setStartTime(resultSet->getString(9));
		data.setEndTime(resultSet->getString(10));
		data.setCreator(resultSet->getInt64(11));
		data.setEditor(resultSet->getInt64(12));
		data.setAddTime(resultSet->getString(13));
		data.setEditTime(resultSet->getString(14));
		data.setDeleted(resultSet->getInt(15));
		data.setDecCount(resultSet->getInt(16));
		data.setRemark(resultSet->getString(17));
		data.setTeachType(resultSet->getInt(18));
		data.setOnTrial(resultSet->getInt(19));
		data.setTrialResult(resultSet->getString(20));
		data.setState(resultSet->getInt(21));
		data.setCloseTime(resultSet->getString(22));
		data.setCloseOperator(resultSet->getInt64(23));
		data.setTeacherId(resultSet->getInt64(24));
		data.setBookable(resultSet->getInt(25));
		data.setSchoolId(resultSet->getInt64(26));
		data.setOrgId(resultSet->getInt64(27));
		return data;
	}
};

class ConflictInfoMapper : public Mapper<ConflictInfo>
{
public:
	ConflictInfo mapper(ResultSet* resultSet) const override
	{
		ConflictInfo info;
		info.title = resultSet->getString(1);
		info.date = resultSet->getString(2);
		info.startTime = resultSet->getString(3);
		info.endTime = resultSet->getString(4);
		return info;
	}
};

class IntMapper : public Mapper<int>
{
public:
	int mapper(ResultSet* resultSet) const override
	{
		return resultSet->getInt(1);
	}
};

#endif

#pragma once
#ifndef _COURSERECORD_MAPPER_H_
#define _COURSERECORD_MAPPER_H_

#include "Mapper.h"
#include "../../domain/do/CourseRecordDO.h"

class CourseRecordMapper : public Mapper<CourseRecordDO>
{
public:
	CourseRecordDO mapper(ResultSet* resultSet) const override
	{
		CourseRecordDO data;
		data.setId(resultSet->getUInt64(1));
		data.setTitle(resultSet->getString(2));
		data.setSn(resultSet->getInt(3));
		data.setCourseId(resultSet->getUInt64(4));
		data.setScheduleId(resultSet->getUInt64(5));
		data.setClassId(resultSet->getUInt64(6));
		data.setRoomId(resultSet->getUInt64(7));
		data.setDate(resultSet->getString(8));
		data.setStartTime(resultSet->getString(9));
		data.setEndTime(resultSet->getString(10));
		data.setCreator(resultSet->getUInt64(11));
		data.setEditor(resultSet->getUInt64(12));
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
		data.setCloseOperator(resultSet->getUInt64(23));
		data.setTeacherId(resultSet->getUInt64(24));
		data.setBookable(resultSet->getInt(25));
		data.setSchoolId(resultSet->getUInt64(26));
		data.setOrgId(resultSet->getUInt64(27));
		return data;
	}
};

#endif // !_COURSERECORD_MAPPER_H_

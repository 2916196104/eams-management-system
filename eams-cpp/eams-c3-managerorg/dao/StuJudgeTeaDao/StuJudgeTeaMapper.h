#pragma once
#ifndef _STUJUDGETEA_MAPPER_
#define _STUJUDGETEA_MAPPER_

#include "Mapper.h"
#include "domain/do/StuJudgeTea/TeachEvaluationDO.h"

/**
 * —ß∆¿ΩÃ±Ì◊÷∂Œ∆•≈‰”≥…‰
 */
class StuJudgeTeaMapper : public Mapper<StuJudgeTeaDO>
{
public:
	StuJudgeTeaDO mapper(ResultSet* resultSet) const override
	{
		StuJudgeTeaDO data;
		data.setId(resultSet->getUInt64(1));
		data.setLessonId(resultSet->getUInt64(2));
		data.setTeacherId(resultSet->getUInt64(3));
		data.setScore1(resultSet->getUInt(4));
		data.setScore2(resultSet->getUInt(5));
		data.setScore3(resultSet->getUInt(6));
		data.setScore4(resultSet->getUInt(7));
		data.setContent(resultSet->getString(8));
		data.setAddTime(resultSet->getString(9));
		data.setStudentId(resultSet->getUInt64(10));
		data.setAnonymity(resultSet->getBoolean(11));
		data.setOrgId(resultSet->getUInt64(12));
		return data;
	}
};

#endif // !_STUJUDGETEA_MAPPER_
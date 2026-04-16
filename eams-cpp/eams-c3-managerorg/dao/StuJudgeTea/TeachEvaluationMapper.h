#pragma once
#ifndef _STUJUDGETEA_MAPPER_
#define _STUJUDGETEA_MAPPER_

#include "Mapper.h"
#include "domain/do/StuJudgeTea/TeachEvaluationDO.h"


class StuJudgeTeaMapper : public Mapper<PtrStuJudgeTeaDO>
{
public:
	PtrStuJudgeTeaDO mapper(ResultSet* resultSet) const override
	{
		PtrStuJudgeTeaDO data=std::make_shared<StuJudgeTeaDO>();
		data->setId(resultSet->getUInt64("id"));
		data->setLessonId(resultSet->getUInt64("lesson_id"));
		if (data->getLessonId() != 0)
		{
			PtrLessonDO le = std::make_shared<LessonDO>();
			le->setId(data->getLessonId());
			le->setTitle(resultSet->getString("lesson_title"));
			data->setLesson(le);
		}
		data->setTeacherId(resultSet->getUInt64("teacher_id"));
		if (data->getTeacherId() != 0)
		{
			PtrStaffDO te = std::make_shared<StaffDO>();
			te->setId(data->getTeacherId());
			te->setName(resultSet->getString("teacher_name"));
			data->setStaff(te);
		}
		data->setScore1(resultSet->getUInt("score1"));
		data->setScore2(resultSet->getUInt("score2"));
		data->setScore3(resultSet->getUInt("score3"));
		data->setScore4(resultSet->getUInt("score4"));
		data->setContent(resultSet->getString("content"));
		data->setAddTime(resultSet->getString("add_time"));
		data->setStudentId(resultSet->getUInt64("student_id"));
		if (data->getStudentId() != 0)
		{
			PtrUserDO st = std::make_shared<UserDO>();
			st->setId(data->getStudentId());
			st->setName(resultSet->getString("student_name"));
			data->setUser(st);
		}
		data->setAnonymity(resultSet->getInt("anonymity"));
		data->setOrgId(resultSet->getUInt64("org_id"));
		if (data->getOrgId() != 0)
		{
			PtrOrgDO org = std::make_shared<OrgDO>();
			org->setId(data->getOrgId());
			org->setName(resultSet->getString("org_name"));
			data->setOrg(org);
		}
		return data;
	}
};

#endif // !_STUJUDGETEA_MAPPER_

/*
 @Author: abinng
 @Date: 2026/03/22 14:43:13
 @File: ScoreMapper.h
*/
#pragma once
#ifndef _SCOREMAPPER_H_
#define _SCOREMAPPER_H_

#include "Mapper.h"
#include "domain/do/score/ScoreDO.h"

class ScoreViewMapper : public Mapper<PtrScoreViewDO> {
public:
    PtrScoreViewDO mapper(ResultSet* resultSet) const override
    {
        PtrScoreViewDO score = std::make_shared<ScoreViewDO>();
        score->setId(resultSet->getUInt64("id"));
        score->setGradeId(resultSet->getUInt64("grade_id"));
        score->setGradeTitle(resultSet->getString("grade_title"));
        score->setStudentId(resultSet->getUInt64("student_id"));
        score->setStudentName(resultSet->getString("student_name"));
        score->setScore(resultSet->getInt("score"));
        score->setAddTime(resultSet->getString("add_time"));
        return score;
    }
};

#endif // !_SCOREMAPPER_H_
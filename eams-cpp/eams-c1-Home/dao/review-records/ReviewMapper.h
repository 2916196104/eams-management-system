/*
 @Author: abinng
 @Date: 2026/03/23 17:01:36
 @File: ReviewMapper.h
*/
#pragma once
#ifndef _REVIEW_MAPPER_H_
#define _REVIEW_MAPPER_H_ 

#include "Mapper.h"
#include "domain/do/review-records/ReviewDO.h"

class ReviewMapper : public Mapper<PtrReviewViewDO> {
public:
    PtrReviewViewDO mapper(ResultSet* resultSet) const override
    {
        PtrReviewViewDO review = std::make_shared<ReviewViewDO>();
        review->setId(resultSet->getUInt64("id"));
        review->setLessonId(resultSet->getUInt64("lesson_id"));
        review->setLessonTitle(resultSet->getString("lesson_title"));
        review->setEvaluateTeacher(resultSet->getUInt64("evaluate_teacher"));
        review->setEvaluation(resultSet->getString("evaluation"));
        review->setScore(resultSet->getInt("score"));
        review->setEvaluateTime(resultSet->getString("evaluate_time"));
        return review;
    }
};

#endif // !_REVIEW_MAPPER_H_
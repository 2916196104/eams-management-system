/*
 @Author: abinng
 @Date: 2026/03/23 16:16:13
 @File: ReviewService.h
*/
#pragma once
#ifndef _REVIEW_SERVICE_H_
#define _REVIEW_SERVICE_H_ 

#include "domain/dto/review-records/reviewDTO.h"
#include "domain/query/review-records/reviewquery.h"

class ReviewService 
{
public:
    ReviewRecordPageDTO::Wrapper listAll(const ReviewRecordQuery::Wrapper& query);
};


#endif // !_REVIEW_SERVICE_H_
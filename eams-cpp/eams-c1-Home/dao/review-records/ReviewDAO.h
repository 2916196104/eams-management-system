/*
 @Author: abinng
 @Date: 2026/03/23 17:34:16
 @File: ReviewDAO.h
*/
#pragma once
#ifndef _REVIEW_DAO_H_
#define _REVIEW_DAO_H_

#include "BaseDAO.h"
#include "domain/do/review-records/ReviewDO.h"
#include "domain/query/review-records/reviewquery.h"

/**
 * 课时学员表数据库操作类
 */
class ReviewDAO : public BaseDAO {
public:
    // 统计记录总数
    uint64_t count(const ReviewRecordQuery::Wrapper& query);
    // 通过查询条件查询数据
    std::list<PtrReviewViewDO> selectByQuery(const ReviewRecordQuery::Wrapper& query);

};




#endif // !_REVIEW_DAO_H_
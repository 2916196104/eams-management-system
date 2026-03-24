/*
 @Author: abinng
 @Date: 2026/03/23 16:16:17
 @File: ReviewService.cpp
*/
// #include "stdafx.h"
#include "ReviewService.h"

#include "dao/review-records/ReviewDAO.h"
#include "domain/do/review-records/ReviewDO.h"

ReviewRecordPageDTO::Wrapper ReviewService::listAll(const ReviewRecordQuery::Wrapper& query)
{
    // 构建返回分页DTO对象
    auto page = ReviewRecordPageDTO::createShared();
    // 1. 获取分页数据
    page->pageIndex = query->pageIndex;
    page->pageSize = query->pageSize;

    // 2. 获取数据总数
    ReviewDAO dao;

    int64_t total = dao.count(query);
    page->total = total;
    page->calcPages();

    uint64_t offset = (query->pageIndex.getValue(1) - 1) * query->pageSize.getValue(10);
    page->rows = oatpp::List<ReviewRecordDTO::Wrapper>::createShared();
    if (total == 0 || offset > total) { // 没有记录或者当前页没有记录
        return page;                    // 设置记录为空，直接返回
    }
    auto result = dao.selectByQuery(query);
    // 返回的std::list类型的结果为空
    if (result.empty()) {
        return page; // 设置记录为空，直接返回
    }
    for (auto& one : result) {
        auto dto = ReviewRecordDTO::createShared();
        ZO_STAR_DOMAIN_DO_TO_DTO_1(dto, one, 
            id, Id, 
            lesson_id, LessonId, 
            lesson_title, LessonTitle, 
            evaluate_teacher, EvaluateTeacher,
            evaluation, Evaluation,
            score, Score,
            evaluate_time, EvaluateTime
        );
        page->rows->emplace_back(std::move(dto));
    }
    return page;
}

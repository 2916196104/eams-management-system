#include "stdafx.h"
#include "ScoreService.h"
#include "dao/score/ScoreDAO.h"
#include "domain/do/score/ScoreDO.h"

ScorePageDTO::Wrapper ScoreService::listAll(const ScoreQuery::Wrapper& query) 
{
    // 构建返回分页DTO对象
    auto page = ScorePageDTO::createShared();
    // 1. 获取分页数据
    page->pageIndex = query->pageIndex;
    page->pageSize = query->pageSize;

    // 2. 获取数据总数
    ScoreDAO dao;

    int64_t total = dao.count(query);
    page->total = total;
    page->calcPages();

    uint64_t offset = (query->pageIndex.getValue(1) - 1) * query->pageSize.getValue(10);
    if (total == 0 || offset >= total) {    // 没有记录或者当前页没有记录(没这一页)
        page->rows = oatpp::List<ScoreDTO::Wrapper>::createShared();
        return page;    // 直接返回
    }
    auto result = dao.selectByQuery(query);
    if (result.empty()) {
        page->rows = oatpp::List<ScoreDTO::Wrapper>::createShared();
        return page;    // 直接返回
    }
    page->rows = oatpp::List<ScoreDTO::Wrapper>::createShared();
    for (auto &one : result) {
        auto scoreDTO = ScoreDTO::createShared();
        ZO_STAR_DOMAIN_DO_TO_DTO_1(scoreDTO, one, id, Id, grade_id, GradeId, grade_title, GradeTitle, student_id,
                                 StudentId, student_name, StudentName, score, Score, add_time, AddTime);
        page->rows->push_back(scoreDTO);
    }
    return page;
}

#include "stdafx.h"
#include "HomeworkService.h"
#include "../../../dao/home/homework/HomeworkDAO.h"

HomeworkPageDTO::Wrapper HomeworkService::listAll(const HomeworkQuery::Wrapper& query)
{
    auto pages = HomeworkPageDTO::createShared();
    pages->pageIndex = query->pageIndex;
    pages->pageSize = query->pageSize;

    HomeworkDAO dao;
    uint64_t count = dao.count(query);
    if (count <= 0) return pages;

    pages->total = count;
    pages->calcPages();

    auto result = dao.selectWithPage(query);
    for (auto& sub : result)
    {
        auto dto = HomeworkDTO::createShared();
        ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, class_name, ClassName);
        ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, title, Title);
        ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, submit_status, SubmitStatus);
        pages->addData(dto);
    }
    return pages;
}
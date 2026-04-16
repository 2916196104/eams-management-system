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

        if (sub.getSubmitStatus() == 1) dto->submit_status = ZH_WORDS_GETTER("c5.home.homework.field.sub_1");
        else dto->submit_status = ZH_WORDS_GETTER("c5.home.homework.field.sub_0");
        pages->addData(dto);
    }
    return pages;
}
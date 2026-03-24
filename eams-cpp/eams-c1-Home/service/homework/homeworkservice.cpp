#include "stdafx.h"
#include "homeworkservice.h"
#include "dao/homework/homeworkdao.h"

HomeworkPageJsonVO::Wrapper HomeworkService::queryPage(const HomeworkQuery::Wrapper& query)
{
    HomeworkDAO dao;
    auto count = dao.count(query);
    
    auto dto = HomeworkPageDTO::createShared();
    dto->rows = oatpp::List<HomeworkDTO::Wrapper>::createShared();
    
    if (count > 0)
    {
        auto pageData = dao.selectPage(query);
        for (auto& item : pageData)
        {
            dto->addData(item);
        }
    }
    
    dto->total = count;
    dto->pageIndex = query->pageIndex;
    dto->pageSize = query->pageSize;

    auto result = HomeworkPageJsonVO::createShared();
    result->success(dto);
    return result;
}

HomeworkDetailJsonVO::Wrapper HomeworkService::queryDetail(uint64_t id)
{
    HomeworkDAO dao;
    auto detail = dao.selectDetail(id);

    auto result = HomeworkDetailJsonVO::createShared();
    if (detail) {
        result->success(detail);
    } else {
        result->fail(detail);
        result->message = ZH_WORDS_GETTER("homework.detail.notfound");
    }
    return result;
}

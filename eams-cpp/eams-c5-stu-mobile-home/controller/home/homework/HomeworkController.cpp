#include "stdafx.h"
#include "HomeworkController.h"
#include "../../../service/home/homework/HomeworkService.h"

HomeworkPageJsonVO::Wrapper HomeworkController::executeQueryHomework(const HomeworkQuery::Wrapper& query)
{
    auto result = HomeworkService().listAll(query);
    auto jvo = HomeworkPageJsonVO::createShared();
    jvo->success(result);
    return jvo;
}
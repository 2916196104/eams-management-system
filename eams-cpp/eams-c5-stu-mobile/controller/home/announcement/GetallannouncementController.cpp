
#include"stdafx.h"
#include"GetallannouncementController.h"
StringJsonVO::Wrapper GetallannouncementController::executequerygetallannouncement(const PageQuery::Wrapper& query)
{
    //创建一个响应结果
    auto vo = StringJsonVO::createShared();
    vo->success("success");
    return vo;

}
//AnnouncementPageJsonVO::Wrapper GetallannouncementController::executequerygetallannouncement(const PageQuery::Wrapper& query);
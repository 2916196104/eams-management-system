#include"stdafx.h"
#include"GetdisplayedannouncementController.h"
StringJsonVO::Wrapper GetdisplayedannouncementController::executequerygetdisplayedannouncement(const PageQuery::Wrapper& query)
{
    //创建一个响应结果
    auto vo = StringJsonVO::createShared();
    vo->success("success");
    return vo;

}
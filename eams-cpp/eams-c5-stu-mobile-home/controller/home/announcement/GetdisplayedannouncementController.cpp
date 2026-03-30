#include "stdafx.h"
#include "GetdisplayedannouncementController.h"
#include "../../../service/home/announcement/AnnouncementService.h"
AnnouncementJsonVO::Wrapper GetdisplayedannouncementController::executequerygetdisplayedannouncement(const AnnouncementQuery::Wrapper& query)
{
    //创建一个响应结果
	// 查询数据
	auto result = AnnouncementService().listone(query);
	// 响应结果
	auto jvo = AnnouncementJsonVO::createShared();
	jvo->success(result);
	return jvo;

}
//AnnouncementJsonVO::Wrapper GetdisplayedannouncementController::executequerygetallannouncement(const PageQuery::Wrapper& query);
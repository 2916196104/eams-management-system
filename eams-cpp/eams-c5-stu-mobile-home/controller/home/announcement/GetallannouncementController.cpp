#include "stdafx.h"
#include "GetallannouncementController.h"
#include "../../../service/home/announcement/AnnouncementService.h"
AnnouncementPageJsonVO::Wrapper GetallannouncementController::executequerygetallannouncement(const AnnouncementQuery::Wrapper& query)
{
    //创建一个响应结果
	auto result = AnnouncementService().listAll(query);
	// 响应结果
	auto jvo = AnnouncementPageJsonVO::createShared();
	jvo->success(result);
	return jvo;

}
//AnnouncementPageJsonVO::Wrapper GetallannouncementController::executequerygetallannouncement(const PageQuery::Wrapper& query);
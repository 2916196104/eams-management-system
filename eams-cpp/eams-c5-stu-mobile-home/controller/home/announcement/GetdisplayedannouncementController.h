#pragma once
#ifndef _GETDISPLAYEDANNOUNCEMENTCONTROLLER_H_
#define _GETDISPLAYEDANNOUNCEMENTCONTROLLER_H_

#include "domain/vo/BaseJsonVO.h"
#include "domain/query/PageQuery.h"
#include "domain/query/home/announcement/AnnouncementQuery.h"
#include "domain/dto/home/announcement/AnnouncementDTO.h"
#include "domain/vo/home/announcement/GetannouncementVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("Announcement.tag.t1")
class GetdisplayedannouncementController : public oatpp::web::server::api::ApiController {

    //定义控制器访问入口
    API_ACCESS_DECLARE(GetdisplayedannouncementController);
public://定义接口
    ENDPOINT_INFO(Getdisplayedannouncement) {
        info->summary = ZH_WORDS_GETTER("Announcement.getdisplayedannouncement.summary");
        //支持授权
        API_DEF_ADD_AUTH();
        // 定义响应参数格式
        API_DEF_ADD_RSP_JSON_WRAPPER(AnnouncementJsonVO);

        API_DEF_ADD_TAG(API_TAG);
        // 定义请求参数格式
        API_DEF_ADD_PAGE_PARAMS();
        //只需要获取显示通知公告
        //似乎只要筛选出最新的那个
        API_DEF_ADD_QUERY_PARAMS(String, "add_time", ZH_WORDS_GETTER("Announcement.getdisplayedannouncement.search1"), ZH_WORDS_GETTER("c5.home.Announcement.getdisplayedannouncement.searchname1"), false);

        //API_DEF_ADD_QUERY_PARAMS(String, "name", ZH_WORDS_GETTER("getdisplayedannouncement.search1"), ZH_WORDS_GETTER("getdisplayedannouncement.name1"), false);
        //API_DEF_ADD_QUERY_PARAMS(String, "teacher_info", ZH_WORDS_GETTER("getdisplayedannouncement.search2"), "Roin" + ZH_WORDS_GETTER("getdisplayedannouncement.teachername1"), false);
    }
    //接口等待后期更改
    ENDPOINT(API_M_GET, "/c5home/announcement/displayed/get", Getdisplayedannouncement, QUERIES(QueryParams, params), API_HANDLER_AUTH_PARAME) {
        //解析查询参数
        API_HANDLER_QUERY_PARAM(query, AnnouncementQuery, params);
        //响应结果
        API_HANDLER_RESP_VO(executequerygetdisplayedannouncement(query));

    }
    // TODO - more endpoints here
private://定义接口执行函数
    AnnouncementJsonVO::Wrapper executequerygetdisplayedannouncement(const AnnouncementQuery::Wrapper& query);
    //StringJsonVO::Wrapper executequerygetdisplayedannouncement(const PageQuery::Wrapper& query);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif // !_GETDISPLAYEDANNOUNCEMENTCONTROLLER_H_

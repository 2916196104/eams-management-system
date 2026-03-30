#pragma once
#ifndef _GETALLANNOUNCEMENTCONTROLLERMENT_H_
#define _GETALLANNOUNCEMENTCONTROLLERMENT_H_

#include "domain/vo/BaseJsonVO.h"
#include "domain/query/PageQuery.h"
#include "domain/query/home/announcement/AnnouncementQuery.h"
#include "domain/dto/home/announcement/AnnouncementDTO.h"
#include "domain/vo/home/announcement/GetannouncementVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("Announcement.tag.t1")
class GetallannouncementController : public oatpp::web::server::api::ApiController {

    //定义控制器访问入口
    API_ACCESS_DECLARE(GetallannouncementController);
public://定义接口
    ENDPOINT_INFO(Getallannouncement) {
        info->summary = ZH_WORDS_GETTER("Announcement.getallannouncement.summary");//暂时这么搞，中文词典后期要统一
        //支持授权
        API_DEF_ADD_AUTH();
        // 定义响应参数格式
        API_DEF_ADD_RSP_JSON_WRAPPER(AnnouncementPageJsonVO);
        API_DEF_ADD_TAG(API_TAG);
        // 定义请求参数格式
        API_DEF_ADD_PAGE_PARAMS();
        ////获取所有通知公告似乎不需要加筛选，先放着
        //API_DEF_ADD_QUERY_PARAMS(String, "title", ZH_WORDS_GETTER("getallannouncement.search1"), ZH_WORDS_GETTER("getallannouncement.titlename1"), false);
        //API_DEF_ADD_QUERY_PARAMS(String, "type", ZH_WORDS_GETTER("getallannouncement.search2"), ZH_WORDS_GETTER("getallannouncement.teachername1"), false);
    }
    //接口等待后期更改
    ENDPOINT(API_M_GET, "c5/home/announcement/all/get", Getallannouncement, QUERIES(QueryParams, params), API_HANDLER_AUTH_PARAME) {
        //解析查询参数
        API_HANDLER_QUERY_PARAM(query, AnnouncementQuery, params);
        //响应结果
        API_HANDLER_RESP_VO(executequerygetallannouncement(query));

    }
    // TODO - more endpoints here
private://定义接口执行函数
    AnnouncementPageJsonVO::Wrapper executequerygetallannouncement(const AnnouncementQuery::Wrapper& query);
    //StringJsonVO::Wrapper executequerygetallannouncement(const PageQuery::Wrapper& query);
};
#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif // !_GETALLANNOUNCEMENTCONTROLLERMENT_H_

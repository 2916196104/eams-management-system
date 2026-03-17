#pragma once
#ifndef _GETTIMEABLECONTROLLER_H_
#define _GETTIMEABLECONTROLLER_H_

#include "ApiHelper.h"
#include "ServerInfo.h"
#include "Macros.h"
#include"domain/vo/BaseJsonVo.h"
#include"domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

class GetallannouncementController : public oatpp::web::server::api::ApiController {

    //定义控制器访问入口
    API_ACCESS_DECLARE(GetallannouncementController);
public://定义接口
    ENDPOINT_INFO(querytest) {
        info->summary = ZH_WORDS_GETTER("getallannouncement.summary");
        //支持授权
        API_DEF_ADD_AUTH();
        // 定义响应参数格式
        API_DEF_ADD_RSP_JSON_WRAPPER(StringJsonVO);
        // 定义请求参数格式
        API_DEF_ADD_PAGE_PARAMS();
        //asd之后需要加入中文词典
        API_DEF_ADD_QUERY_PARAMS(String, "title", ZH_WORDS_GETTER("getallannouncement.search1"), ZH_WORDS_GETTER("getallannouncement.titlename1"), false);
        API_DEF_ADD_QUERY_PARAMS(String, "type", ZH_WORDS_GETTER("getallannouncement.search2"), "Roin" + ZH_WORDS_GETTER("getallannouncement.typename1"), false);
    }
    //接口等待后期更改
    ENDPOINT(API_M_GET, "/course/list/get", querytest, QUERIES(QueryParams, params), API_HANDLER_AUTH_PARAME) {
        //解析查询参数
        API_HANDLER_QUERY_PARAM(query, PageQuery, params);
        //响应结果
        API_HANDLER_RESP_VO(executequerygetallannouncement(query));

    }
    // TODO - more endpoints here
private://定义接口执行函数
    StringJsonVO::Wrapper executequerygetallannouncement(const PageQuery::Wrapper& query);
};

#include OATPP_CODEGEN_END(ApiController)

#endif // !_GETTIMEABLECONTROLLER_H_
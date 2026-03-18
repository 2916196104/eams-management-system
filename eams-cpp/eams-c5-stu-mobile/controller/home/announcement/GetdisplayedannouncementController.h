#pragma once
#ifndef _GETDISPLAYEDANNOUNCEMENTCONTROLLER_H_
#define _GETDISPLAYEDANNOUNCEMENTCONTROLLER_H_

#include "domain/vo/BaseJsonVO.h"
#include "domain/query/PageQuery.h"
// 替换为Homework相关Query/DTO/VO头文件（路径按项目实际结构调整）
#include "domain/query/home/announcement/GetdisplayedannouncementQuery.h"
#include "domain/dto/home/announcement/GetannouncementDTO.h"
#include "domain/vo/home/announcement/GetannouncementVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

class GetdisplayedannouncementController : public oatpp::web::server::api::ApiController {

    //定义控制器访问入口
    API_ACCESS_DECLARE(GetdisplayedannouncementController);
public://定义接口
    ENDPOINT_INFO(querytest) {
        info->summary = ZH_WORDS_GETTER("getdisplayedannouncement.summary");
        //支持授权
        API_DEF_ADD_AUTH();
        // 定义响应参数格式
        API_DEF_ADD_RSP_JSON_WRAPPER(StringJsonVO);
        // 定义请求参数格式
        API_DEF_ADD_PAGE_PARAMS();
        //只需要获取显示通知公告
        API_DEF_ADD_QUERY_PARAMS(String, "name", ZH_WORDS_GETTER("getdisplayedannouncement.search1"), ZH_WORDS_GETTER("getdisplayedannouncement.searchname1"), false);

        //API_DEF_ADD_QUERY_PARAMS(String, "name", ZH_WORDS_GETTER("getdisplayedannouncement.search1"), ZH_WORDS_GETTER("getdisplayedannouncement.name1"), false);
        //API_DEF_ADD_QUERY_PARAMS(String, "teacher_info", ZH_WORDS_GETTER("getdisplayedannouncement.search2"), "Roin" + ZH_WORDS_GETTER("getdisplayedannouncement.teachername1"), false);
    }
    //接口等待后期更改
    ENDPOINT(API_M_GET, "/app/sCenter/announcement/displayed/get", querytest, QUERIES(QueryParams, params), API_HANDLER_AUTH_PARAME) {
        //解析查询参数
        API_HANDLER_QUERY_PARAM(query, PageQuery, params);
        //响应结果
        API_HANDLER_RESP_VO(executequerygetdisplayedannouncement(query));

    }
    // TODO - more endpoints here
private://定义接口执行函数
    StringJsonVO::Wrapper executequerygetdisplayedannouncement(const PageQuery::Wrapper& query);
};

#include OATPP_CODEGEN_END(ApiController)

#endif // !_GETDISPLAYEDANNOUNCEMENTCONTROLLER_H_

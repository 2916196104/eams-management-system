#pragma once
#ifndef _GETTIMEABLECONTROLLER_H_
#define _GETTIMEABLECONTROLLER_H_

#include "domain/vo/BaseJsonVO.h"
#include "domain/query/PageQuery.h"
// 替换为ClassStudent相关Query/DTO/VO头文件
#include "domain/query/schedule/TimeableQuery.h"
#include "domain/dto/schedule/TimeableDTO.h"
#include "domain/vo/schedule/TimeableVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("Timeable.tags.t1")

class GettimeableController : public oatpp::web::server::api::ApiController {

    //定义控制器访问入口
    API_ACCESS_DECLARE(GettimeableController);
public://定义接口
    ENDPOINT_INFO(ScheduleTimeable) {
        info->summary = ZH_WORDS_GETTER("gettimeable.summary");//暂时这么搞，中文词典后期要统一
        //支持授权
        API_DEF_ADD_AUTH();
        // 定义响应参数格式
        API_DEF_ADD_RSP_JSON_WRAPPER(ScheduleTimeableJsonVO);
        //定义标签
        API_DEF_ADD_TAG(API_TAG);
        // 定义请求参数格式
        API_DEF_ADD_PAGE_PARAMS();
        //asd之后需要加入中文词典
        API_DEF_ADD_QUERY_PARAMS(String, "name", ZH_WORDS_GETTER("gettimeable.search1"), ZH_WORDS_GETTER("course.name1"), false);
        API_DEF_ADD_QUERY_PARAMS(String,"teacher_info", ZH_WORDS_GETTER("gettimeable.search2"), "Roin"+ZH_WORDS_GETTER("course.teachername1"), false);
    }
    //接口等待后期更改
    ENDPOINT(API_M_GET, "/course/list/get", ScheduleTimeable, QUERIES(QueryParams, params),API_HANDLER_AUTH_PARAME){
        //解析查询参数
        API_HANDLER_QUERY_PARAM(query,ScheduleTimeableQuery, params);
        //响应结果
         API_HANDLER_RESP_VO(executeQueryTest(query));
        //API_HANDLER_RESP_VO(executequerygettimeable(query));

    }
    // TODO - more endpoints here
private://定义接口执行函数
    StringJsonVO::Wrapper executeQueryTest(const PageQuery::Wrapper& query);
    //ScheduleTimeableJsonVO::Wrapper executequerygettimeable(const ScheduleTimeableQuery::Wrapper& query);
};

#undef API_TAG

#include OATPP_CODEGEN_END(ApiController)

#endif // !_GETTIMEABLECONTROLLER_H_

#pragma once
#ifndef _GETTIMEABLECONTROLLER_H_
#define _GETTIMEABLECONTROLLER_H_

#include "domain/vo/BaseJsonVO.h"
#include "domain/query/PageQuery.h"
// 替换为ClassStudent相关Query/DTO/VO头文件
#include "domain/query/schedule/GetTimeableQuery.h"
#include "domain/dto/schedule/GetTimeableDTO.h"
#include "domain/vo/schedule/GetTimeableVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("Timeable.tags.t1")

class GettimeableController : public oatpp::web::server::api::ApiController {

    //定义控制器访问入口
    API_ACCESS_DECLARE(GettimeableController);
public://定义接口
    ENDPOINT_INFO(ScheduleTimeable) {
        info->summary = ZH_WORDS_GETTER("Timeable.gettimeable.summary");//暂时这么搞，中文词典后期要统一
        //支持授权
        API_DEF_ADD_AUTH();
        // 定义响应参数格式
        API_DEF_ADD_RSP_JSON_WRAPPER(GetTimeableJsonVO);
        //定义标签
        API_DEF_ADD_TAG(API_TAG);
        // 定义请求参数格式
        API_DEF_ADD_PAGE_PARAMS();
        API_DEF_ADD_QUERY_PARAMS(String, "student_id", ZH_WORDS_GETTER("Timeable.gettimeable.search1"), "101", true);
        //API_DEF_ADD_QUERY_PARAMS(String, "class_id", ZH_WORDS_GETTER("gettimeable.search3"), "101", false);
        //按上课日期查询
        API_DEF_ADD_QUERY_PARAMS(String, "date", ZH_WORDS_GETTER("Timeable.gettimeable.search2"), "2026-9-5", true);
        /*API_DEF_ADD_QUERY_PARAMS(String, "name", ZH_WORDS_GETTER("gettimeable.search1"), ZH_WORDS_GETTER("course.name1"), false);
        API_DEF_ADD_QUERY_PARAMS(String,"teacher_info", ZH_WORDS_GETTER("gettimeable.search2"), "Roin"+ZH_WORDS_GETTER("course.teachername1"), false);*/
    }
    //接口等待后期更改
    ENDPOINT(API_M_GET, "c5schedule/list/get", ScheduleTimeable, QUERIES(QueryParams, params),API_HANDLER_AUTH_PARAME){
        //解析查询参数
        API_HANDLER_QUERY_PARAM(query,GetTimeableQuery, params);
        //响应结果
        //API_HANDLER_RESP_VO(executeQueryTest(query));
        API_HANDLER_RESP_VO(executequerygettimeable(query));

    }
    // TODO - more endpoints here
private://定义接口执行函数
    //StringJsonVO::Wrapper executeQueryTest(const PageQuery::Wrapper& query);
    GetTimeablePageJsonVO::Wrapper executequerygettimeable(const GetTimeableQuery::Wrapper& query);
};

#undef API_TAG

#include OATPP_CODEGEN_END(ApiController)

#endif // !_GETTIMEABLECONTROLLER_H_

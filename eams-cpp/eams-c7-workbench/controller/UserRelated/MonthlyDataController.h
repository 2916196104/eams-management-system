#pragma once
#ifndef _MONTHLYDATACONTROLLER_H_
#define _MONTHLYDATACONTROLLER_H_

//#include "oatpp/web/server/api/ApiController.hpp"
//#include "oatpp/core/macro/codegen.hpp"
#include "domain/vo/BaseJsonVO.h"
#include "domain/vo/UserRelated/MonthlyDataVO .h"
#include "domain/query/UserRelated/MonthlyDataQuery .h"
//#include "ApiHelper.h"
//#include "domain/query/PageQuery.h"
//#include "ServerInfo.h"
//#include "Macros.h"

/*
* 教师数据控制器
*/
#include OATPP_CODEGEN_BEGIN(ApiController) ///< Begin ApiController codegen section

class MonthlyDataController : public oatpp::web::server::api::ApiController {
public:

    //MyController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper) /* Inject object mapper */)
    //    : oatpp::web::server::api::ApiController(objectMapper)
    //{
    //}

    //ENDPOINT("GET", "/", root) {
    //    return createResponse(Status::CODE_200, "Hello World!");
    //}

    //// TODO - more endpoints here
    API_ACCESS_DECLARE(MonthlyDataController);
public:
    ENDPOINT_INFO(queryMonthlyDataList) {
        //info->summary = ZH_WORDS_GETTER("select_class.summary");
         API_DEF_ADD_AUTH();//1
         API_DEF_ADD_TAG(ZH_WORDS_GETTER("monthly_data.tag"));//3
        API_DEF_ADD_TITLE(ZH_WORDS_GETTER("monthly_data.B"));//2
        API_DEF_ADD_RSP_JSON(MonthlyDataListJsonVO::Wrapper);//4
    }
    ENDPOINT(API_M_GET, "/c7/user-related/monthlydata", queryMonthlyDataList,QUERIES(QueryParams,params),API_HANDLER_AUTH_PARAME) {
        API_HANDLER_QUERY_PARAM(query, MonthlyDataQuery, params);
        API_HANDLER_RESP_VO(executeQueryMonthlyDataList(query));
    }
    //API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("monthly_data.B"), queryMonthlyDataPage, MonthlyDataQuery, MonthlyDataPageJsonVO::Wrapper, ZH_WORDS_GETTER("monthly_data.tag"));
    //API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET, "/c7/user-related/monthlydata", queryMonthlyDataPage, QUERIES(QueryParams, queryParams),
    //    API_HANDLER_QUERY_PARAM(query, MonthlyDataQuery, queryParams); API_HANDLER_RESP_VO(executeQueryMonthlyDataPage(query)););
    //API_DEF_ENDPOINT_INFO_AUTH(
    //    ZH_WORDS_GETTER("monthly_data.B"), queryMonthlyDataList, MonthlyDataListJsonVO::Wrapper, ZH_WORDS_GETTER("monthly_data.tag")
    //);
    //API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/c7/user-related/monthlydata", queryMonthlyDataList, QUERY(String, name), executeQueryMonthlyDataList(query));
private:
    //StringJsonVO::Wrapper executeQuerySelectTeacher(const PageQuery::Wrapper& query);
    //MonthlyDataPageJsonVO::Wrapper executeQueryMonthlyDataPage(const MonthlyDataQuery::Wrapper& query);
    MonthlyDataListJsonVO::Wrapper executeQueryMonthlyDataList(const MonthlyDataQuery::Wrapper& query);
};

#include OATPP_CODEGEN_END(ApiController) ///< End ApiController codegen section
#endif
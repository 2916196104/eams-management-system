#pragma once
#ifndef _MONTHLYDATACONTROLLER_H_
#define _MONTHLYDATACONTROLLER_H_
#include "domain/vo/BaseJsonVO.h"
#include "domain/vo/UserRelated/MonthlyDataVO.h"
#include "domain/query/UserRelated/MonthlyDataQuery.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

class MonthlyDataController : public oatpp::web::server::api::ApiController {
public:
    API_ACCESS_DECLARE(MonthlyDataController);
public:
    ENDPOINT_INFO(queryMonthlyDataList) {
        API_DEF_ADD_AUTH();//1
        API_DEF_ADD_TAG(ZH_WORDS_GETTER("monthly_data.tag"));//3
        API_DEF_ADD_TITLE(ZH_WORDS_GETTER("monthly_data.B"));//2
        API_DEF_ADD_RSP_JSON(MonthlyDataListJsonVO::Wrapper);//4
    }
    ENDPOINT(API_M_GET, "/c7-workbench/monthlydata", queryMonthlyDataList, QUERIES(QueryParams, params), API_HANDLER_AUTH_PARAME) {
        API_HANDLER_QUERY_PARAM(query, MonthlyDataQuery, params);
        API_HANDLER_RESP_VO(executeQueryMonthlyDataList(query));
    }
private:
    MonthlyDataListJsonVO::Wrapper executeQueryMonthlyDataList(const MonthlyDataQuery::Wrapper& query);
};

#include OATPP_CODEGEN_END(ApiController) 
#endif
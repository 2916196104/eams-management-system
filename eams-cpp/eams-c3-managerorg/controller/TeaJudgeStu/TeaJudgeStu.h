#pragma once
#ifndef __TEA_JUDGE_STU_H__  // 规范：全大写+下划线，修正原大小写混合宏
#define __TEA_JUDGE_STU_H__

// 补充：通用VO基类
#include "domain/vo/BaseJsonVO.h"
#include "domain/GlobalInclude.h"
#include "oatpp/web/server/api/ApiController.hpp"


#include "domain/vo/TeaJudgeStu/TeaJudgeStuVO.h" 
#include "domain/query/TeaJudgeStu/TeaJudgeStuQuery.h" 
#include "domain/dto/TeaJudgeStu/TeaJudgeStuDTO.h" 

#include OATPP_CODEGEN_BEGIN(ApiController)


#define API_TAG ZH_WORDS_GETTER("TeaJudgeStu.tags")


class TeaJudgeStu : public oatpp::web::server::api::ApiController{
    API_ACCESS_DECLARE(TeaJudgeStu);
public:
    API_DEF_ENDPOINT_INFO_QUERY_AUTH(
        ZH_WORDS_GETTER("TeaJudgeStu.query"),
        queryPageTeaJudgeStu,                                 
        TeaJudgeStuQuery,               
        TeaJudgeStuPageJsonVO::Wrapper, 
        API_TAG                                              
    );

    API_HANDLER_ENDPOINT_OPTION_AUTH(
        API_M_GET,                                     
        "c3-org/TeaJudgeStu/get-teacher-review-list",                       
        queryPageTeaJudgeStu, 
        QUERIES(QueryParams, queryParams), 
        API_HANDLER_QUERY_PARAM(query, TeaJudgeStuQuery, queryParams);
        API_HANDLER_RESP_VO(execQueryPageTeaJudgeStu(query));
    );

private: 

    TeaJudgeStuPageJsonVO::Wrapper execQueryPageTeaJudgeStu(const TeaJudgeStuQuery::Wrapper& query);
};

#include OATPP_CODEGEN_END(ApiController)
#undef API_TAG
#endif 
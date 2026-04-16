#pragma once
#ifndef _HOMEWORK_CONTROLLER_H_
#define _HOMEWORK_CONTROLLER_H_

#include "domain/vo/BaseJsonVO.h"
#include "domain/query/home/homework/HomeworkQuery.h"
#include "domain/dto/home/homework/HomeworkDTO.h"
#include "domain/vo/home/homework/HomeworkVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("c5.home.homework.tag")

class HomeworkController : public oatpp::web::server::api::ApiController
{
    API_ACCESS_DECLARE(HomeworkController);
public:
    ENDPOINT_INFO(Homework) {
        info->summary = ZH_WORDS_GETTER("c5.home.homework.query-all.summary");
        API_DEF_ADD_AUTH();
        API_DEF_ADD_TAG(API_TAG);
        API_DEF_ADD_RSP_JSON(HomeworkPageJsonVO::Wrapper);
        API_DEF_ADD_PAGE_PARAMS();

        API_DEF_ADD_QUERY_PARAMS(Int64, "student_id", ZH_WORDS_GETTER("c5.home.homework.field.student_id"), 1, true);
    }

    ENDPOINT(API_M_GET, "/c5/home/homework/list", Homework, QUERIES(QueryParams, params), API_HANDLER_AUTH_PARAME)
    {
        API_HANDLER_QUERY_PARAM(query, HomeworkQuery, params);
        API_HANDLER_RESP_VO(executeQueryHomework(query));
    }

private:
    HomeworkPageJsonVO::Wrapper executeQueryHomework(const HomeworkQuery::Wrapper& query);
};
#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)
#endif
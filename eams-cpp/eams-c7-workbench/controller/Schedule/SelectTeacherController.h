#pragma once
#ifndef _SELECTTEACHERCONTROLLER_H_
#define _SELECTTEACHERCONTROLLER_H_
#include "domain/vo/BaseJsonVO.h"
#include "domain/vo/Schedule/SelectTeacherVO.h"
#include "domain/query/Schedule/SelectTeacherQuery.h"
#include OATPP_CODEGEN_BEGIN(ApiController) 

class SelectTeacherController : public oatpp::web::server::api::ApiController {
public:
    API_ACCESS_DECLARE(SelectTeacherController);
public:
    API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("select_teacher.B"), querySelectTeacherPage, SelectTeacherQuery, SelectTeacherPageJsonVO::Wrapper, ZH_WORDS_GETTER("select_teacher.tag"));
    API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET, "/c7-workbench/selectteacher", querySelectTeacherPage, QUERIES(QueryParams, queryParams),
        API_HANDLER_QUERY_PARAM(query, SelectTeacherQuery, queryParams); API_HANDLER_RESP_VO(executeQueryTeacherPage(query)););
private:
    SelectTeacherPageJsonVO::Wrapper executeQueryTeacherPage(const SelectTeacherQuery::Wrapper& query);
};

#include OATPP_CODEGEN_END(ApiController) ///< End ApiController codegen section
#endif
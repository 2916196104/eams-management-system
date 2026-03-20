#pragma once
#ifndef _SELECTTEACHERCONTROLLER_H_
#define _SELECTTEACHERCONTROLLER_H_

//#include "oatpp/web/server/api/ApiController.hpp"
//#include "oatpp/core/macro/codegen.hpp"
#include "domain/vo/BaseJsonVO.h"
#include "domain/vo/schedule/SelectTeacherVO .h"
#include "domain/query/schedule/SelectTeacherQuery .h"
//#include "ApiHelper.h"
//#include "domain/query/PageQuery.h"
//#include "ServerInfo.h"
//#include "Macros.h"

/*
* 教师数据控制器
*/
#include OATPP_CODEGEN_BEGIN(ApiController) ///< Begin ApiController codegen section

class SelectTeacherController : public oatpp::web::server::api::ApiController {
public:

    //MyController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper) /* Inject object mapper */)
    //    : oatpp::web::server::api::ApiController(objectMapper)
    //{
    //}

    //ENDPOINT("GET", "/", root) {
    //    return createResponse(Status::CODE_200, "Hello World!");
    //}

    //// TODO - more endpoints here
    API_ACCESS_DECLARE(SelectTeacherController);
public:
    //ENDPOINT_INFO(querySelectTeacher) {
    //    info->summary = ZH_WORDS_GETTER("select_teacher.summary");
    //    API_DEF_ADD_AUTH();
    //    API_DEF_ADD_PAGE_PARAMS();
    //    API_DEF_ADD_RSP_JSON(StringJsonVO::Wrapper);
    //    //info->addConsumes<Object<UserDto>>("application/json");
    //    //info->addResponse<Object<UserDto>>(Status::CODE_200, "application/json");
    //}
    //ENDPOINT(API_M_GET, "/select_teacher", querySelectTeacher,QUERIES(QueryParams,params),API_HANDLER_AUTH_PARAME) {
    //    API_HANDLER_QUERY_PARAM(query, PageQuery, params);
    //    API_HANDLER_RESP_VO(executeQuerySelectTeacher(query));
    //}
    API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("select_teacher.B"), querySelectTeacherPage, SelectTeacherQuery, SelectTeacherPageJsonVO::Wrapper, ZH_WORDS_GETTER("select_teacher.tag"));
    API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET, "/c7/workbench/selectteacher", querySelectTeacherPage, QUERIES(QueryParams, queryParams),
        API_HANDLER_QUERY_PARAM(query, SelectTeacherQuery, queryParams); API_HANDLER_RESP_VO(executeQueryTeacherPage(query)););
private:
    //StringJsonVO::Wrapper executeQuerySelectTeacher(const PageQuery::Wrapper& query);
    SelectTeacherPageJsonVO::Wrapper executeQueryTeacherPage(const SelectTeacherQuery::Wrapper& query);
};

#include OATPP_CODEGEN_END(ApiController) ///< End ApiController codegen section
#endif
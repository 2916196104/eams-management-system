#pragma once

#include "ApiHelper.h"
#include "domain/query/GradeTable/GradeListQuery.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/vo/GradeTable/GradeListVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController) ///< Begin ApiController codegen section

class GradeListController : public oatpp::web::server::api::ApiController
{
    API_ACCESS_DECLARE(GradeListController);

public:
    /* swagger info for query + page endpoint */
    API_DEF_ENDPOINT_INFO_QUERY_AUTH(
        ZH_WORDS_GETTER("grade_table.grade_list.get_grade_list_title"), /* TODO */
        GetGradeList,
        GradeListQuery,
        GradeListPageJsonVO::Wrapper,
        ZH_WORDS_GETTER("grade_table.tag")
    );

    API_HANDLER_ENDPOINT_QUERY_AUTH(
        API_M_GET,
        "/gradelist",
        GetGradeList,
        GradeListQuery,
        ExecGradeListQuery(query, authObject->getPayload())
    );

private:
    GradeListPageJsonVO::Wrapper ExecGradeListQuery(
        const GradeListQuery::Wrapper& query,
        const PayloadDTO& payload
    );
};

#include OATPP_CODEGEN_END(ApiController) ///< End ApiController codegen section
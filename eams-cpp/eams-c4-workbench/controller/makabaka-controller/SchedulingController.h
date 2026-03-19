#pragma once
#include "ApiHelper.h"
#include "domain/query/makabaka-query/RepeatedSchedulingQuery.h"
#include "domain/query/makabaka-query/FreeSchedulingQuery.h"
#include "domain/vo/makabaka-vo/SchedulingVO.h"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("schedule.api.tag")

class SchedulingController : public oatpp::web::server::api::ApiController {

    API_ACCESS_DECLARE(SchedulingController);

public:

    API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("schedule.api.createRepeat"),
        createRepeat,
        JsonVO<SchedulingVO::Wrapper>::Wrapper,
        API_TAG)

    API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/scheduling/repeat/create",
        createRepeat,
        BODY_DTO(RepeatedSchedulingQuery::Wrapper, query),
        execCreateRepeat(query)
    )

    API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("schedule.api.createFree"),
        createFree,
        JsonVO<SchedulingVO::Wrapper>::Wrapper,
        API_TAG)

    API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/scheduling/free/create",
        createFree,
        BODY_DTO(FreeSchedulingQuery::Wrapper, query),
        execCreateFree(query)
    )

private:

    oatpp::Object<JsonVO<SchedulingVO::Wrapper>>
        execCreateRepeat(const RepeatedSchedulingQuery::Wrapper& query);

    oatpp::Object<JsonVO<SchedulingVO::Wrapper>>
        execCreateFree(const FreeSchedulingQuery::Wrapper& query);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)
#pragma once
#ifndef _GETMYCUSTOMERSCONTROLLER_H_
#define _GETMYCUSTOMERSCONTROLLER_H_

#include "domain/vo/BaseJsonVO.h"
#include "ApiHelper.h"
#include "domain/query/MyCustomers/MyCustomersQuery.h"
#include "domain/vo/MyCustomers/MyCustomersVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("cus.tag")
class GetMyCustomersController : public oatpp::web::server::api::ApiController
{
    API_ACCESS_DECLARE(GetMyCustomersController);

public:
    API_DEF_ENDPOINT_INFO_QUERY_AUTH(
        ZH_WORDS_GETTER("cus.get-list.summary"),
        getMyCustomers,
        MyCustomersQuery,
        MyCustomersPageJsonVO::Wrapper,
        API_TAG
    );

    API_HANDLER_ENDPOINT_QUERY_AUTH(
        API_M_GET,
        "/c7-workbench/MyCustomers/List",
        getMyCustomers,
        MyCustomersQuery,
        executeGetMyCustomersList(query, authObject->getPayload())
    );

private:
    MyCustomersPageJsonVO::Wrapper executeGetMyCustomersList(
        const MyCustomersQuery::Wrapper& query,
        const PayloadDTO& payload
    );
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif // _GETMYCUSTOMERSCONTROLLER_H_
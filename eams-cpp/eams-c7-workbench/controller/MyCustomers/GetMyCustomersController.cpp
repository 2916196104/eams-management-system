#include "stdafx.h"
#include "GetMyCustomersController.h"

MyCustomersPageJsonVO::Wrapper GetMyCustomersController::executeGetMyCustomersList(
    const MyCustomersQuery::Wrapper& query,
    const PayloadDTO& payload
)
{
    auto vo = MyCustomersPageJsonVO::createShared();
    return vo;
}
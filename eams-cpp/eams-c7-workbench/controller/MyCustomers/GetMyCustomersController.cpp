#include "stdafx.h"
#include "GetMyCustomersController.h"
#include "../../service/Mycustomers/MyCustomersService.h"

MyCustomersPageJsonVO::Wrapper GetMyCustomersController::executeGetMyCustomersList(
    const MyCustomersQuery::Wrapper& query,
    const PayloadDTO& payload)
{
    MyCustomersService service;
    auto dto = service.listMyCustomers(query);
    return MyCustomersPageJsonVO::createPageResult(dto);
}
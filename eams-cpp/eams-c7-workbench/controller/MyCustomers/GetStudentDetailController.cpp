#include "stdafx.h"
#include "GetStudentDetailController.h"
#include "service/Mycustomers/MyCustomersService.h"

MyCustomerDetailJsonVO::Wrapper GetStudentDetailController::executeGetMyCustomersDetails(const Int64& id, const PayloadDTO& payload)
{
    MyCustomersService service;
    auto dto = service.getStudentDetail(id);
    return MyCustomerDetailJsonVO::createDetailResult(dto);
}
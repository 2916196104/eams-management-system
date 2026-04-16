#include "stdafx.h"
#include "credit_mallController.h"
#include "../../service/home/credit_mallService.h"
#include "../../domain/bo/PdfReportBO.h"
#include "../ApiDeclarativeServicesHelper.h"
#include "ExcelComponent.h"
#include "SimpleDateTimeFormat.h"
#include "PdfComponent.h"

// 补充Oat++必要的类型别名
using namespace oatpp;
using namespace oatpp::web::server::api;
using namespace oatpp::web::protocol::http::outgoing;
using namespace oatpp::web::protocol::http::incoming;

// 按ID查询单个礼品：返回空VO
credit_mallVO::Wrapper CreditMallController::execQueryCreditMallById(const String& id)
{
    auto result = CreditMallService().getById(id);
    auto vo = credit_mallVO::createShared();
    vo->success(result);
    return vo;
}

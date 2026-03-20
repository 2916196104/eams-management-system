#pragma once

#ifndef _STAFF_CONTROLLER_ 
#define _STAFF_CONTROLLER_ 

#include "domain/vo/BaseJsonVO.h"
#include "ApiHelper.h"
#include "ServerInfo.h"
#include "domain/dto/staff/StaffDTO.h"
#include "domain/query/PageQuery.h"
// 1 定义API控制器使用宏
#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("sample.tags")

/*
 * 员工控制器
 */
class StaffController : public oatpp::web::server::api::ApiController // 1 继承控制器
{
  // 2 定义控制器访问入口
  API_ACCESS_DECLARE(StaffController);
  // 3 定义接口
public:
    //定义获取代班记录接口
    ENDPOINT_INFO(getDutyRecord) {
        info->summary = ZH_WORDS_GETTER("getDutyRecord.summary");

        //支持授权
        API_DEF_ADD_AUTH();
        //定义响应参数格式
        API_DEF_ADD_RSP_JSON(StringJsonVO::Wrapper);
        //定义请求参数格式
        API_DEF_QUERY_PARAM_BUILD(DutyRecordQueryDTO);

    }
    ENDPOINT(API_M_GET, "/org/employee/getDutyRecord", getDutyRecord, QUERIES(QueryParams, params), API_HANDLER_AUTH_PARAME) {
        //解析查询参数
        API_HANDLER_QUERY_PARAM(query, DutyRecordQueryDTO, params);
        //相应结果
        API_HANDLER_RESP_VO(executegetDutyRecord(query));
        //return createResponse(Status::CODE_200, ZH_WORDS_GETTER("getDutyRecord.resp"));
    }

private: // 定义接口执行函数
    StringJsonVO::Wrapper executegetDutyRecord(const DutyRecordQueryDTO::Wrapper& query);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController) //<- End Codegen
#endif // !_POSITION_CONTROLLER_

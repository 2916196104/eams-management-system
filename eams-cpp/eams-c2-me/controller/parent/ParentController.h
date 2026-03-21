#pragma once

#ifndef _PARENT_CONTROLLER_ 
#define _PARENT_CONTROLLER_ 

#include "domain/vo/BaseJsonVO.h"
#include "domain/dto/parent/ParentDTO.h"
#include "domain/vo/ParentVO.h"
#include "domain/query/PageQuery.h"
#include "ApiHelper.h"
#include "ServerInfo.h"
#include "dao/parentDao.h"

// 1 定义API控制器使用宏
#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("sample.tags")

/*
 * 家长控制器
 */
class ParentController : public oatpp::web::server::api::ApiController // 1 继承控制器
{
  // 2 定义控制器访问入口
  API_ACCESS_DECLARE(ParentController);

  // 3 定义接口
public:
    API_DEF_ENDPOINT_INFO_QUERY_AUTH(
        ZH_WORDS_GETTER("help.querylist"), // 接口标题
        getList, // 端点函数名
        ListQuery, // Query类型（自动生成参数文档）
        UsageGuideJsonVO::Wrapper, // 响应类型
        ZH_WORDS_GETTER("help.querylist") // 标签
    );

    API_DEF_ENDPOINT_INFO_QUERY_AUTH(
        ZH_WORDS_GETTER("help.querydetail"), // 接口标题
        getDetail, // 端点函数名
        DetailQuery, // Query类型（自动生成参数文档）
        UsageDetailJsonVO::Wrapper, // 响应类型
        ZH_WORDS_GETTER("help.querydetail") // 标签
    );
      
    API_HANDLER_ENDPOINT_QUERY_AUTH(
        API_M_GET, // HTTP方法：GET
        "/me/parent/getList", // 路径
        getList, // 函数名
        ListQuery, // Query类型（自动解析参数）
        executeQueryAll(query) // 调用执行方法
    );

    API_HANDLER_ENDPOINT_AUTH(
        API_M_GET,
        "/me/parent/getDetail",
        getDetail,
        QUERY(String, id), // 接收单个查询参数
        executeQueryOne(id) // 调用执行方法
    );

private: // 定义接口执行函数
    
    UsageGuideJsonVO::Wrapper executeQueryAll(const ListQuery::Wrapper& query);
    UsageDetailJsonVO::Wrapper executeQueryOne(const String& id);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController) //<- End Codegen
#endif // !_POSITION_CONTROLLER_

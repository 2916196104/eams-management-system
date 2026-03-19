#pragma once

#ifndef _PARENT_CONTROLLER_ 
#define _PARENT_CONTROLLER_ 

#include "domain/vo/BaseJsonVO.h"
#include "ApiHelper.h"
#include "ServerInfo.h"
#include "domain/vo/parent/ParentVO.h"

// 1 定义API控制器使用宏
#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("parent.tag")

/*
 * 家长控制器
 */
class ParentController : public oatpp::web::server::api::ApiController // 1 继承控制器
{
  // 2 定义控制器访问入口
  API_ACCESS_DECLARE(ParentController);
public:
  // 3.1 定义获取家长信息接口描述
  API_DEF_ENDPOINT_INFO_AUTH(
	ZH_WORDS_GETTER("parent.query-one.summary"), queryParentInfo, ParentJsonVO::Wrapper, API_TAG,
	API_DEF_ADD_QUERY_PARAMS(UInt64, "phone", ZH_WORDS_GETTER("parent.field.phone"), 1891235678, true);
  );
  // 3.2 定义获取家长信息接口处理
  API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/c2/me/parent", queryParentInfo, QUERY(UInt64, phone), execQueryOne(phone));
private: // 定义接口执行函数
  ParentJsonVO::Wrapper execQueryOne(const oatpp::UInt64& phone);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController) //<- End Codegen
#endif // !_POSITION_CONTROLLER_

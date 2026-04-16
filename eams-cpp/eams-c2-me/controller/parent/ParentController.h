#pragma once

#ifndef _PARENT_CONTROLLER_ 
#define _PARENT_CONTROLLER_ 

#include "domain/vo/BaseJsonVO.h"
#include "ApiHelper.h"
#include "ServerInfo.h"
#include "domain/vo/parent/ParentInfoVO.h"
#include "domain/query/parent/ParentInfoQuery.h"

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
	// 3 定义接口
public:
  // 定义获取家长详细信息接口描述
 // API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("parent.query.summary"), queryOne, ParentJsonVO::Wrapper, API_TAG,
	//API_DEF_ADD_QUERY_PARAMS(String, "phone", ZH_WORDS_GETTER("parent.field.phone"), "13712345678", true);
 // );
  API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("parent.query.summary"), queryInfo, ParentInfoJsonVO::Wrapper, API_TAG);
  // 定义查询家长信息接口端点
  API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/me/get-parentinfo", queryInfo, BODY_DTO(ParentInfoDTO::Wrapper, dto), execQueryInfo(dto));

  // 定义修改家长姓名接口描述
  API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("parent.modify-name.summary"), modifyName, StringJsonVO::Wrapper, API_TAG,
	API_DEF_ADD_QUERY_PARAMS(String, "name", ZH_WORDS_GETTER("parent.modify-name.param"), "name", true);
  );
  // 定义修改家长姓名接口处理
  API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/me/modify-name", modifyName, BODY_DTO(ParentInfoDTO::Wrapper, dto), execModifyName(dto, authObject->getPayload()));

  // 定义修改家长密码接口描述
  API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("parent.modify-password.summary"), modifyPassword, StringJsonVO::Wrapper, API_TAG,
	API_DEF_ADD_QUERY_PARAMS(String, "oldPassword", ZH_WORDS_GETTER("parent.modify-password.old-password"), "", true);
	API_DEF_ADD_QUERY_PARAMS(String, "newPassword", ZH_WORDS_GETTER("parent.modify-password.new-password"), "", true);
	API_DEF_ADD_QUERY_PARAMS(String, "verifyPassword", ZH_WORDS_GETTER("parent.modify-password.verify-password"), "", true);
  );
  API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/me/modify-password", modifyPassword, BODY_DTO(ParentInfoDTO::Wrapper, dto), execModifyPassword(dto));

private: // 定义接口执行函数
  // 查询家长信息
  //ParentJsonVO::Wrapper executeQuery(const oatpp::String& phone);
  ParentInfoJsonVO::Wrapper execQueryInfo(const ParentInfoDTO::Wrapper &dto);
  // 修改家长姓名
  ParentInfoJsonVO::Wrapper execModifyName(const ParentInfoDTO::Wrapper& dto, const PayloadDTO &payload);
  // 修改家长密码
  ParentInfoJsonVO::Wrapper execModifyPassword(const ParentInfoDTO::Wrapper& dto);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController) //<- End Codegen
#endif // !_POSITION_CONTROLLER_















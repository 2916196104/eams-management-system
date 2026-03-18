#pragma once

#ifndef _STAFF_CONTROLLER_ 
#define _STAFF_CONTROLLER_ 

#include "domain/vo/BaseJsonVO.h"
#include "ApiHelper.h"
#include "ServerInfo.h"
#include "domain/dto/staff/StaffDTO.h"

// 1 定义API控制器使用宏
#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("staff.tag")

/*
 * 员工控制器
 */
class StaffController : public oatpp::web::server::api::ApiController // 1 继承控制器
{
  // 2 定义控制器访问入口
  API_ACCESS_DECLARE(StaffController);
  // 3 定义接口
public:
	// 定义设置角色接口描述(支持批量)
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("staff.setRole"), setRole, ListJsonVO<String>::Wrapper, API_TAG);
	// 定义设置角色接口处理(支持批量)
	API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/setRole", setRole, BODY_DTO(List<String>, ids), execSetRole(ids, authObject->getPayload()));

	// 定义在职状态接口描述(支持批量)
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("staff.setOnJob"), setOnJob, ListJsonVO<String>::Wrapper, API_TAG);
	// 定义在职状态接口处理(支持批量)
	API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/setOnJob", setOnJob, BODY_DTO(List<String>, ids), execSetJob(ids, authObject->getPayload()));

	// 定义转出机构接口描述(支持批量)
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("staff.setInstitution"), setInstitution, ListJsonVO<String>::Wrapper, API_TAG);
	// 定义转出机构接口处理(支持批量)
	API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/setInstitution", setInstitution, BODY_DTO(List<String>, ids), execSetInstitution(ids, authObject->getPayload()));
private: // 定义接口执行函数
	// 设置角色
	ListJsonVO<String>::Wrapper execSetRole(const List<String>& ids, const PayloadDTO& payload);
	// 在职状态
	ListJsonVO<String>::Wrapper execSetJob(const List<String>& ids, const PayloadDTO& payload);
	// 转出机构
	ListJsonVO<String>::Wrapper execSetInstitution(const List<String>& ids, const PayloadDTO& payload);
private: // 定义接口执行函数
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController) //<- End Codegen
#endif // !_POSITION_CONTROLLER_

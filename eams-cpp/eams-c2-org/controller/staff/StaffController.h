#pragma once

#ifndef _STAFF_CONTROLLER_ 
#define _STAFF_CONTROLLER_ 

#include "domain/vo/BaseJsonVO.h"
#include "ApiHelper.h"
#include "ServerInfo.h"
#include "Macros.h"
#include"domain/query/PageQuery.h"
#include "domain/dto/staff/StaffDTO.h" 


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
	

	// 定义修改头像接口
	ENDPOINT_INFO(modifyAvatar) {
		info->summary = ZH_WORDS_GETTER("modifyAvatar.summary");
		// 支持授权
		API_DEF_ADD_AUTH();
		// 定义响应参数格式
		API_DEF_ADD_RSP_JSON(StringJsonVO::Wrapper);
		//声明接收文件表单，定义参数请求格式
		API_DEF_ADD_FILE_FORM(AvatarUploadDTO::Wrapper);

	}
	ENDPOINT(API_M_POST, "/org/employee/modifyAvatar", modifyAvatar, BODY_DTO(AvatarUploadDTO::Wrapper,dto), API_HANDLER_AUTH_PARAME) {
		// 直接调用处理函数
		API_HANDLER_RESP_VO(executeModifyAvatar(dto));
		//return createResponse(Status::CODE_200, ZH_WORDS_GETTER("modifyAvatar.resp"));
	}
private: // 定义接口执行函数
	StringJsonVO::Wrapper executeModifyAvatar(const AvatarUploadDTO::Wrapper& dto);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController) //<- End Codegen
#endif // !_STAFF_CONTROLLER_

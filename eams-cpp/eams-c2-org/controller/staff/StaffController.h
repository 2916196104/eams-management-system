#pragma once

#ifndef _STAFF_CONTROLLER_ 
#define _STAFF_CONTROLLER_ 

#include "domain/vo/BaseJsonVO.h"
#include "ApiHelper.h"
#include "ServerInfo.h"
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
	//定义修改密码接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("staff.change-psword.summary"), changePassword, StringJsonVO::Wrapper,ZH_WORDS_GETTER("staff.tags.t1"));
	//定义修改密码接口
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "org/app/common/staff/changePassword", changePassword, BODY_DTO(StaffChangePasswordDTO::Wrapper, dto), executeStaffPassWordChange(dto));

	//定义员工列表导出接口描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("staff.export-list.summary"), exportList, StaffExportQueryDto, StringJsonVO::Wrapper, ZH_WORDS_GETTER("staff.tags.t1"));

	//定义员工列表导出接口
	ENDPOINT(API_M_GET, "org/app/common/staff/list", exportList, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_QUERY_PARAM(exportQuery, StaffExportQueryDto, queryParams);
		API_HANDLER_RESP_VO(executeStaffListExport(exportQuery));
	}

private: // 定义接口执行函数
	StringJsonVO::Wrapper executeStaffPassWordChange(const StaffChangePasswordDTO::Wrapper& dto);
	StringJsonVO::Wrapper executeStaffListExport(const StaffExportQueryDto::Wrapper& exportQuery);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController) //<- End Codegen
#endif // !_POSITION_CONTROLLER_

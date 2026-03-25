#pragma once

#ifndef _STAFF_CONTROLLER_ 
#define _STAFF_CONTROLLER_ 

#include "domain/vo/BaseJsonVO.h"
#include "ApiHelper.h"
#include "ServerInfo.h"
#include "Macros.h"
#include "domain/query/PageQuery.h"
#include "../../domain/dto/staff/StaffDTO.h"

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
	// 定义接口:获取员工列表
	// 接口描述
	ENDPOINT_INFO(getEmpList) {
		// 接口描述
		info->summary = ZH_WORDS_GETTER("staff.getEmpList.controller.summary");

		// 支持授权(文档描述时显示锁)
		// 同时要向ENDPOINT加入参数五
		API_DEF_ADD_AUTH();

		// 定义响应参数格式
		API_DEF_ADD_RSP_JSON(StringJsonVO::Wrapper);// 文档中会展示响应参数格式

		// 定义请求参数格式
		// 分页参数："查询页码"、"每页的条数"
		API_DEF_ADD_PAGE_PARAMS();// 这个宏用于定义"分页相关"的查询参数文档(会向文档中加入"查询页码"、"每页的条数"参数)
		// 其他参数："姓名/手机号"、"状态"
		API_DEF_ADD_QUERY_PARAMS(String, "name", ZH_WORDS_GETTER("staff.getEmpList.controller.empName"), ZH_WORDS_GETTER("getEmpList.controller.zhangsan"), false);
		API_DEF_ADD_QUERY_PARAMS(String, "phone", ZH_WORDS_GETTER("staff.getEmpList.controller.phone"), "13800138000", false);
		API_DEF_ADD_QUERY_PARAMS(Int32, "status", ZH_WORDS_GETTER("staff.getEmpList.controller.status"), 1, false);

		API_DEF_ADD_TAG(API_TAG);
	}
	
	// 接口定义(路由注册)
	// 需要的查询参数有多个，所以参数四用QUERIES(变量类型, 变量名)
	ENDPOINT(API_M_GET, "/org/staff/getEmpList", getEmpList, QUERIES(QueryParams, params), API_HANDLER_AUTH_PARAME) {
		// 解析报文参数:params-->PageQuery类型的query变量
		API_HANDLER_QUERY_PARAM(query, StaffPageQuery, params); // PageQuery类是专为分页查询的数据对象,详情看其定义

		// 响应业务处理函数的处理结果(executeGetEmpList会返回VO，之后传参)
		API_HANDLER_RESP_VO(executeGetEmpList(query));

	}



	// 定义接口:保存员工

	// 3.1 定义新增接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("staff.saveEmp.controller.summary"), saveEmp, StringJsonVO::Wrapper, API_TAG);


	// 3.2 定义新增接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/org/staff/saveEmp", saveEmp, BODY_DTO(StaffSaveDTO::Wrapper, dto), executeSaveEmp(dto));
	

private: // 定义接口执行函数
	// 获取员工列表
	StringJsonVO::Wrapper executeGetEmpList(const StaffPageQuery::Wrapper& query);

	// 保存员工(新增员工+更新员工)
	StringJsonVO::Wrapper executeSaveEmp(const StaffSaveDTO::Wrapper& dto);

};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController) //<- End Codegen
#endif // !_POSITION_CONTROLLER_

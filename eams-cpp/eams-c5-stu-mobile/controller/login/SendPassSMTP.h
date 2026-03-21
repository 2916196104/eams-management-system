#pragma once
#pragma once
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "domain/vo/BaseJsonVO.h"
#include "domain/query/PageQuery.h"
#include "ServerInfo.h"
#include "Macros.h"

//引入头文件用来使用架构宏定义-类似stl
#include "ApiHelper.h"

#include OATPP_CODEGEN_BEGIN(ApiController) ///< Begin ApiController codegen section

class SendPassSMTPControl :public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(SendPassSMTPControl);
public:		//定义接口
	ENDPOINT_INFO(SendSMTP) {
		//使用中文字典
		info->summary = ZH_WORDS_GETTER("spsmtp.summary");
		//使用宏定义调用接口，支持授权,与API_HANDLER_AUTH_PARAME一起联合使用
		API_DEF_ADD_AUTH();
		//定义响应参数格式
		API_DEF_ADD_RSP_JSON(StringJsonVO::Wrapper);
		//或使用API_DEF_ADD_RSP_JSON_WRAPPER(StringJsonVO);来代替
		API_DEF_ADD_TAG(ZH_WORDS_GETTER("credit_mall.tags.t4"));
		//定义请求参数格式使用宏定义API_DEF_ADD_PAGE_PARAMS();来代替
		API_DEF_ADD_QUERY_PARAMS(String, "phone", ZH_WORDS_GETTER("spsmtp.phone"), "13999999999", false);

	}

	ENDPOINT(API_M_POST, "/c5/login/sendpass", SendSMTP, QUERIES(QueryParams, params), API_HANDLER_AUTH_PARAME) {
		//调用框架宏定义来快速解析参数类型，宏定义使用方法：	API_HANDLER_QUERY_PARAM（存储变量，参数类型，变量)
		API_HANDLER_QUERY_PARAM(query, PageQuery, params);

		//API_HANDLER_RESP_VO(vo指针)使用宏定义来代替return createResponse(Status::CODE_200, "Hello World!");		响应结果
		API_HANDLER_RESP_VO(executeSendSMTP(query));
	}


private:	 //定义接口执行函数
	StringJsonVO::Wrapper executeSendSMTP(const PageQuery::Wrapper& query);
};




#include OATPP_CODEGEN_END(ApiController) ///< End ApiController codegen section
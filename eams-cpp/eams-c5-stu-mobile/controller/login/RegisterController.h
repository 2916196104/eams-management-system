#pragma once
#ifndef REGISTERCONTROLLER_H
#define REGISTERCONTROLLER_H

#include <oatpp-swagger/Controller.hpp>

#include OATPP_CODEGEN_BEGIN(ApiController) 
#include "ApiHelper.h"
#include "domain/vo/register/RegisterVO.h"
#include "domain/query/register/RegisterQuery.h"

// 注册控制器
class RegisterController : public oatpp::web::server::api::ApiController
{
	// 定义访问入口
	API_ACCESS_DECLARE(RegisterController);
public:
    ENDPOINT_INFO(Register) { // 端点名称改为Register
		// 定义接口标题
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("login.register.summary"));
		// 定义默认授权参数（可选定义，如果定义了，下面ENDPOINT里面需要加入API_HANDLER_AUTH_PARAME）
		API_DEF_ADD_AUTH();
		// 定义响应参数格式
		API_DEF_ADD_RSP_JSON_WRAPPER(NoDataJsonVO);
		// 定义标签
		API_DEF_ADD_TAG("login");
		// 定义其他查询参数描述
		API_DEF_ADD_QUERY_PARAMS(String, "name", ZH_WORDS_GETTER("login.register.field.name.info"), "", true);
		API_DEF_ADD_QUERY_PARAMS(String, "mobile", ZH_WORDS_GETTER("login.register.field.telephoneNumber.info"), "", true);
		API_DEF_ADD_QUERY_PARAMS(String, "vertificationCode", ZH_WORDS_GETTER("login.register.field.vertificationCode.info"), "", true);
		API_DEF_ADD_QUERY_PARAMS(String, "password", ZH_WORDS_GETTER("login.register.field.password.info"), "", true);
    }

    ENDPOINT("POST", "/c5/login/register", Register, QUERIES(QueryParams, params), API_HANDLER_AUTH_PARAME) {
        API_HANDLER_QUERY_PARAM(query, RegisterQuery, params);
        API_HANDLER_RESP_VO(executeRegister(query));
    }
private:
	NoDataJsonVO::Wrapper executeRegister(const RegisterQuery::Wrapper& query);

};

#include OATPP_CODEGEN_END(ApiController);
#endif // REGISTERCONTROLLER_H
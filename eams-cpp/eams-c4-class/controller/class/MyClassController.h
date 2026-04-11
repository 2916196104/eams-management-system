#pragma once

#ifndef _STUDENT_FILE_CONTROLLER_
#define _STUDENT_FILE_CONTROLLER_

#include "domain/vo/lxianyu-vo/ClassVo.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/query/lxianyu-query/ClassQuery.h"
#include "domain/dto/lxianyu-dto/ClassDTO.h"

using namespace oatpp;

// 0 定义API控制器使用宏
#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

#define API_TAG ZH_WORDS_GETTER("Class.get.tag")	

class MyClassController : public oatpp::web::server::api::ApiController // 1 继承控制器
{
	API_ACCESS_DECLARE(MyClassController);
public:
	//接口描述
	ENDPOINT_INFO(queryMyClass) {
		info->summary = ZH_WORDS_GETTER("Class.get.summary");
		//接口参数
		API_DEF_ADD_PAGE_PARAMS();
		API_DEF_ADD_TAG(API_TAG);
		API_DEF_ADD_AUTH();
		//接口返回参数
		API_DEF_ADD_RSP_JSON_WRAPPER(MyClassPageJsonVO);

	}
	// 3.2 定义查询接口处理
	ENDPOINT(API_M_GET, "/c4class/query-myclass", queryMyClass, QUERIES(QueryParams, params), API_HANDLER_AUTH_PARAME) {
		// 解析查询参数为Query领域模型
		API_HANDLER_QUERY_PARAM(query, MyClassPageQuery, params);
		// 呼叫执行函数响应结果
		API_HANDLER_RESP_VO(execQueryMyClass(query));
	}

private:
	MyClassPageJsonVO::Wrapper execQueryMyClass(const MyClassPageQuery::Wrapper& query);
};
#undef API_TAG
// 0 取消API控制器使用宏
#include OATPP_CODEGEN_END(ApiController) //<- End Codegen
#endif // _STUDENT_FILE_CONTROLLER_
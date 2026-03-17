#pragma once
#include <oatpp-swagger/Controller.hpp>
#ifndef _CLASSCONTROLLER_H_
#define _CLASSCONTROLLER_H_

#include"ApiHelper.h"
#include"domain/vo/BaseJsonVO.h"
#include"domain/query/PageQuery.h"	

#include OATPP_CODEGEN_BEGIN(ApiController)


/**
* 班级控制器
*/

class ClassController : public oatpp::web::server::api::ApiController{
	//定义控制器访问入口
	API_ACCESS_DECLARE(ClassController);
public:		
	ENDPOINT_INFO(queryClass, ) {
		info->summary = "查询班级学员列表";
		API_DEF_ADD_AUTH();
		API_DEF_ADD_RSP_JSON_WRAPPER(StringJsonVO);
		API_DEF_ADD_PAGE_PARAMS();
	}
	
	//定义接口
	ENDPOINT(API_M_GET, "/class", queryClass, QUERIES(QueryParams, params),API_HANDLER_AUTH_PARAME) {
		//解析查询参数
		API_HANDLER_QUERY_PARAM(query, PageQuery, params);
		//响应结果
		API_HANDLER_RESP_VO(executeQueryClass(query));
		return createResponse(Status::CODE_200, "Hello World!");
	}
private:	//定义接口执行函数
	StringJsonVO::Wrapper executeQueryClass(const PageQuery::Wrapper& query);
};

#include OATPP_CODEGEN_END(ApiController)


#endif // !_CLASSCONTROLLER_H_

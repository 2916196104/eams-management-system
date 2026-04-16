#pragma once

#ifndef _CLASSLISTCONTROLLER_H_
#define _CLASSLISTCONTROLLER_H_
#include"domain/query/makabaka-query/class/classQuery.h"
#include"domain/vo/makabaka-vo/class/classVO.h"
#include"domain/vo/BaseJsonVO.h"
using namespace oatpp;

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("class.tag")	

class ClassListController :public oatpp::web::server::api::ApiController {
	//构造函数：继承父类的ObjectMapper（用于序列化/反序列化）
	API_ACCESS_DECLARE(ClassListController);
public:
	//定义班级查询接口(条件+分页)
	//定义描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("class.query.summary"), getClassList, ClassQuery, ClassPageJsonVO::Wrapper, API_TAG);
	//定义班级查询端点
	API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET, "/c4-workbench/class/list", getClassList, QUERIES(QueryParams, queryParams), 
		API_HANDLER_QUERY_PARAM(query, ClassQuery, queryParams); 
		auto result = executeGetClassList(query);
		return createDtoResponse(Status::CODE_200, result);
	);
private:
	//查询班级列表
	ClassPageJsonVO::Wrapper executeGetClassList(const ClassQuery::Wrapper& query);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif //!_CLASSLISTCONTROLLER_H_
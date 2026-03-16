#pragma once


#ifndef _CLASSCONTROLLER_H_
#define _CLASSCONTROLLER_H_

#include "oatpp/web/server/api/ApiController.hpp"
#include "domain/GlobalInclude.h"
#include"domain/vo/class/ClassVO.h"
#include"domain/query/class/ClassQuery.h"
#include OATPP_CODEGEN_BEGIN(ApiController)


class ClassController : public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(ClassController);
public:		//定义接口
	ENDPOINT_INFO(queryClassList) {
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("class.list"));
		API_DEF_ADD_AUTH();
		API_DEF_ADD_RSP_JSON_WRAPPER(ClassPageJsonVO);
		// 定义分页查询参数描述
		API_DEF_ADD_PAGE_PARAMS();
		// 班级列表查询参数
		API_DEF_ADD_QUERY_PARAMS(String, "teacher_id", ZH_WORDS_GETTER("class.teacher"), "", false);   // 班级负责人/老师ID
		API_DEF_ADD_QUERY_PARAMS(String, "name", ZH_WORDS_GETTER("class.name"), "", false);             // 班级名（模糊）
		API_DEF_ADD_QUERY_PARAMS(String, "course_id", ZH_WORDS_GETTER("class.course"), "", false);     // 课程ID
		API_DEF_ADD_QUERY_PARAMS(String, "school_id", ZH_WORDS_GETTER("class.school"), "", false);     // 学校ID
		API_DEF_ADD_QUERY_PARAMS(String, "org_id", ZH_WORDS_GETTER("class.org"), "", false);           // 组织ID
		API_DEF_ADD_QUERY_PARAMS(String, "be_over", ZH_WORDS_GETTER("class.beOver"), "", false);      // 是否完结：0 未完结，1 已完结
	}


	ENDPOINT(API_M_GET, "/classList", queryClassList, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
		// 解析查询参数为Query领域模型
		API_HANDLER_QUERY_PARAM(userQuery, ClassQuery, queryParams);
		// 呼叫执行函数响应结果
		API_HANDLER_RESP_VO(execQueryClassList(userQuery));
	}

	ENDPOINT_INFO(queryClassDetail) {
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("class.detail"));
		API_DEF_ADD_AUTH();
		API_DEF_ADD_RSP_JSON_WRAPPER(ClassVO);
		//// 定义分页查询参数描述
		//API_DEF_ADD_PAGE_PARAMS();
		// 班级列表查询参数
		API_DEF_ADD_QUERY_PARAMS(String, "teacher_id", ZH_WORDS_GETTER("class.teacher"), "", true);   // 班级负责人/老师ID
		API_DEF_ADD_QUERY_PARAMS(String, "name", ZH_WORDS_GETTER("class.name"), "", false);             // 班级名（模糊）
		API_DEF_ADD_QUERY_PARAMS(String, "course_id", ZH_WORDS_GETTER("class.course"), "", false);     // 课程ID
		API_DEF_ADD_QUERY_PARAMS(String, "school_id", ZH_WORDS_GETTER("class.school"), "", false);     // 学校ID
		API_DEF_ADD_QUERY_PARAMS(String, "org_id", ZH_WORDS_GETTER("class.org"), "", false);           // 组织ID
		API_DEF_ADD_QUERY_PARAMS(String, "be_over", ZH_WORDS_GETTER("class.beOver"), "", false);      // 是否完结：0 未完结，1 已完结
	}

	ENDPOINT(API_M_GET, "/classdetail", queryClassDetail, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
		// 解析查询参数为Query领域模型
		API_HANDLER_QUERY_PARAM(userQuery, ClassDTO, queryParams);
		// 呼叫执行函数响应结果
		API_HANDLER_RESP_VO(execQueryClassDetail(userQuery));
	}

private:	//定义接口执行函数
	ClassPageJsonVO::Wrapper execQueryClassList(const ClassQuery::Wrapper& query) {
		return ClassPageJsonVO::createShared();
	}
	ClassVO::Wrapper execQueryClassDetail(const ClassDTO::Wrapper& query) {
		return ClassVO::createShared();
	}
};

#include OATPP_CODEGEN_END(ApiController)

#endif
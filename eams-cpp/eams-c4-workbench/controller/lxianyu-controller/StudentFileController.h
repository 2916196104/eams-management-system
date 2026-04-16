#pragma once

#ifndef _STUDENT_FILE_CONTROLLER_
#define _STUDENT_FILE_CONTROLLER_

#include "domain/vo/lxianyu-vo/StudentFileVO.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/query/lxianyu-query/StudentFileQuery.h"
#include "domain/dto/lxianyu-dto/StudentFileDTO.h"

using namespace oatpp;

// 0 定义API控制器使用宏
#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

#define API_TAG ZH_WORDS_GETTER("StudentFile.get.file")	

class StudentFileController : public oatpp::web::server::api::ApiController // 1 继承控制器
{
	API_ACCESS_DECLARE(StudentFileController);
public:
	//接口描述
	ENDPOINT_INFO(queryList) {
		info->summary = ZH_WORDS_GETTER("StudentFile.get.summary");
		//接口参数
		API_DEF_ADD_PAGE_PARAMS();
		API_DEF_ADD_TAG(API_TAG);
		API_DEF_ADD_AUTH();
		//接口返回参数
		API_DEF_ADD_RSP_JSON_WRAPPER(StudentFilePageJsonVO);
		// 定义其他查询参数描述
		API_DEF_ADD_QUERY_PARAMS(String, "name", ZH_WORDS_GETTER("StudentFile.dossier.name"), "xiaoming", false);
		API_DEF_ADD_QUERY_PARAMS(String, "sex", ZH_WORDS_GETTER("StudentFile.dossier.sex"), "boy", false);
		API_DEF_ADD_QUERY_PARAMS(String, "mobile", ZH_WORDS_GETTER("StudentFile.dossier.mobile"), "12345678", false);
		API_DEF_ADD_QUERY_PARAMS(String, "reclass", ZH_WORDS_GETTER("StudentFile.dossier.reclass"), "6", false);

	}
	// 3.2 定义查询接口处理
	ENDPOINT(API_M_GET, "/c4-workbench/query-studentfile", queryList, QUERIES(QueryParams, params), API_HANDLER_AUTH_PARAME) {
		// 解析查询参数为Query领域模型
		API_HANDLER_QUERY_PARAM(query, StudentFilePageQuery, params);
		// 呼叫执行函数响应结果
		API_HANDLER_RESP_VO(execQueryList(query));
	}


	//接口描述
	ENDPOINT_INFO(queryTimeTable) {
		info->summary = ZH_WORDS_GETTER("StudentFile.get.stclass");
		//接口参数
		API_DEF_ADD_PAGE_PARAMS();
		API_DEF_ADD_TAG(API_TAG);
		API_DEF_ADD_AUTH();
		//接口返回参数
		API_DEF_ADD_RSP_JSON_WRAPPER(StudentTimeTablePageJsonVO);

	}
	// 3.2 定义查询接口处理
	ENDPOINT(API_M_GET, "/c4-workbench/query-timetable", queryTimeTable, QUERIES(QueryParams, params), API_HANDLER_AUTH_PARAME) {
		// 解析查询参数为Query领域模型
		API_HANDLER_QUERY_PARAM(query, StudentTimeTablePageQuery, params);
		// 呼叫执行函数响应结果
		API_HANDLER_RESP_VO(execQueryTimeTable(query));
	}

	// 3.1 定义ID查询接口描述
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("StudentFile.get.details"), queryStudentById, StudentFileProJsonVO::Wrapper, API_TAG,
		API_DEF_ADD_QUERY_PARAMS(String, "id", ZH_WORDS_GETTER("StudentFile.dissior2.id"), "d934050a8bb373e8f8eed0bf7507ec17", true);
	);
	// 3.2 定义ID查询接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/c4-workbench/query-by-id", queryStudentById, QUERY(String, id), execQueryStudentById(id));

private:
	StudentFilePageJsonVO::Wrapper execQueryList(const StudentFilePageQuery::Wrapper& query);
	StudentTimeTablePageJsonVO::Wrapper execQueryTimeTable(const StudentTimeTablePageQuery::Wrapper& query);
	StudentFileProJsonVO::Wrapper execQueryStudentById(const String& id);
};

#undef API_TAG

// 0 取消API控制器使用宏
#include OATPP_CODEGEN_END(ApiController) //<- End Codegen
#endif // _STUDENT_FILE_CONTROLLER_
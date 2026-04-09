#pragma once

#include "domain/vo/BaseJsonVO.h"
#include"../../domain/dto/StudentRecord/student_courseDTO.h"
#include"../../domain/vo/StudentRecord/student_courseVO.h"
#include "../../../lib-oatpp/include/ApiHelper.h"
#include"../../domain/query/StudentRecord/studentinformation.h"

#ifndef _STUDENT_COURSECONTROLLER_H_
#define _STUDENT_COURSECONTROLLER_H_

namespace StudentRecord {
	// 定义API控制器使用宏
#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen
#define API_TAG ZH_WORDS_GETTER("StudentRecord.test.tag")
	class CourseControllor : public oatpp::web::server::api::ApiController {
		// 控制器访问入口
		API_ACCESS_DECLARE(CourseControllor);
		// 定义接口
	public:
		// 定义查询接口描述
		ENDPOINT_INFO(CourseProgress) {
			// 定义标签
			API_DEF_ADD_TAG(API_TAG);
			// 定义接口标题
			API_DEF_ADD_TITLE(ZH_WORDS_GETTER("StudentRecord.test.summary1"));
			// 定义默认授权参数（可选定义，如果定义了，下面ENDPOINT里面需要加入API_HANDLER_AUTH_PARAME）
			API_DEF_ADD_AUTH();
			// 定义响应参数格式
			API_DEF_ADD_RSP_JSON_WRAPPER(CourseProgressPageJsonVO);
			// 定义分页查询参数描述
			API_DEF_ADD_PAGE_PARAMS();
			// 定义其他查询参数描述
			API_DEF_ADD_QUERY_PARAMS(String, "name", ZH_WORDS_GETTER("StudentRecord.sample.field.name"), "1", false);
			API_DEF_ADD_QUERY_PARAMS(String, "id", ZH_WORDS_GETTER("StudentRecord.sample.field.id"), "1", true);
		}
		// 3.2 定义查询接口处理
		ENDPOINT(API_M_GET, "/c7-workbench/CourseProgress", CourseProgress, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
			// 解析查询参数为Query领域模型
			API_HANDLER_QUERY_PARAM(userQuery, StudentQuery, queryParams);
			// 呼叫执行函数响应结果
			API_HANDLER_RESP_VO(execCourseProgressPageQuery(userQuery));
		}

		// 定义查询接口描述
		ENDPOINT_INFO(CourseRecord) {
			// 定义标签
			API_DEF_ADD_TAG(API_TAG);
			// 定义接口标题
			API_DEF_ADD_TITLE(ZH_WORDS_GETTER("StudentRecord.test.summary2"));
			// 定义默认授权参数（可选定义，如果定义了，下面ENDPOINT里面需要加入API_HANDLER_AUTH_PARAME）
			API_DEF_ADD_AUTH();
			// 定义响应参数格式
			API_DEF_ADD_RSP_JSON_WRAPPER(CourseRecordPageJsonVO);
			// 定义分页查询参数描述
			API_DEF_ADD_PAGE_PARAMS();
			// 定义其他查询参数描述
			API_DEF_ADD_QUERY_PARAMS(String, "name", ZH_WORDS_GETTER("StudentRecord.sample.field.name"), "li ming", false);
			API_DEF_ADD_QUERY_PARAMS(String, "id", ZH_WORDS_GETTER("StudentRecord.sample.field.id"), "7965", true);
		}
		// 3.2 定义查询接口处理
		ENDPOINT(API_M_GET, "/c7/workbanch/CourseRecord", CourseRecord, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
			// 解析查询参数为Query领域模型
			API_HANDLER_QUERY_PARAM(userQuery, StudentQuery, queryParams);
			// 呼叫执行函数响应结果
			API_HANDLER_RESP_VO(execCourseRecordPageQuery(userQuery));
		}

		// 定义查询接口描述
		ENDPOINT_INFO(StudentSighnUP) {
			// 定义标签
			API_DEF_ADD_TAG(API_TAG);
			// 定义接口标题
			API_DEF_ADD_TITLE(ZH_WORDS_GETTER("StudentRecord.test.summary3"));
			// 定义默认授权参数（可选定义，如果定义了，下面ENDPOINT里面需要加入API_HANDLER_AUTH_PARAME）
			API_DEF_ADD_AUTH();
			// 定义响应参数格式
			API_DEF_ADD_RSP_JSON_WRAPPER(StudentSighnUPPageJsonVO);
			// 定义分页查询参数描述
			API_DEF_ADD_PAGE_PARAMS();
			// 定义其他查询参数描述
			API_DEF_ADD_QUERY_PARAMS(String, "name", ZH_WORDS_GETTER("StudentRecord.sample.field.name"), "li ming", false);
			API_DEF_ADD_QUERY_PARAMS(String, "id", ZH_WORDS_GETTER("StudentRecord.sample.field.id"), "7965", true);
		}
		// 3.2 定义查询接口处理
		ENDPOINT(API_M_GET, "/c7/workbanch/StudentSighnUP", StudentSighnUP, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
			// 解析查询参数为Query领域模型
			API_HANDLER_QUERY_PARAM(userQuery, StudentQuery, queryParams);
			// 呼叫执行函数响应结果
			API_HANDLER_RESP_VO(execStudentSighnUPPageQuery(userQuery));
		}
	private:
		//返回课程进度分页查询数据
		CourseProgressPageJsonVO::Wrapper execCourseProgressPageQuery(StudentQuery::Wrapper userQuery);
		CourseRecordPageJsonVO::Wrapper execCourseRecordPageQuery(StudentQuery::Wrapper userQuery);
		StudentSighnUPPageJsonVO::Wrapper execStudentSighnUPPageQuery(StudentQuery::Wrapper userQuery);
	};

#include OATPP_CODEGEN_END(ApiController) 
}
#endif
#undef API_TAG
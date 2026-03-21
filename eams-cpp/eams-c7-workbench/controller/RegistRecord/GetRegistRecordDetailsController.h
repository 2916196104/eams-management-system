#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/12/01 17:39:36

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

	  https://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#ifndef _GETREGISTRECORDDETAILSCONTROLLER_
#define _GETREGISTRECORDDETAILSCONTROLLER_

#include "domain/vo/BaseJsonVO.h"
#include "domain/query/PageQuery.h"
#include "ApiHelper.h"
#include "ServerInfo.h"
#include "Macros.h"
#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

class GetRegistRecordDetailsController : public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(GetRegistRecordDetailsController);
public://定义接口
	ENDPOINT(API_M_GET, "/RegistRecordDetails", querydetails, QUERIES(QueryParams, params), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_QUERY_PARAM(query, PageQuery, params);
		API_HANDLER_RESP_VO(executeQueryRegistRecordDetails(query));
	}

	ENDPOINT_INFO(querydetails) {
		info->summary = ZH_WORDS_GETTER("translation.RegistRecordDetails");
		API_DEF_ADD_QUERY_PARAMS(String, "studentName", ZH_WORDS_GETTER("translation.studentName"), "", true);
		API_DEF_ADD_QUERY_PARAMS(String, "courseName", ZH_WORDS_GETTER("translation.courseName"), "", true);
		API_DEF_ADD_QUERY_PARAMS(String, "subjectName", ZH_WORDS_GETTER("translation.subjectName"), "", true);
		API_DEF_ADD_QUERY_PARAMS(String, "startDate", ZH_WORDS_GETTER("translation.startDate"), "2026-01-01", true);
		API_DEF_ADD_QUERY_PARAMS(Int32, "courseFee", ZH_WORDS_GETTER("translation.courseFee"), 0, true);
		API_DEF_ADD_QUERY_PARAMS(Int32, "amount", ZH_WORDS_GETTER("translation.amount"), 0, true);
		API_DEF_ADD_QUERY_PARAMS(Int32, "paidAmount", ZH_WORDS_GETTER("translation.paidAmount"), 0, true);
		API_DEF_ADD_QUERY_PARAMS(Int32, "debt", ZH_WORDS_GETTER("translation.debt"), 0, true);
		API_DEF_ADD_QUERY_PARAMS(String, "expireDate", ZH_WORDS_GETTER("translation.expireDate"), "2026-01-01", true);
		API_DEF_ADD_QUERY_PARAMS(String, "addTime", ZH_WORDS_GETTER("translation.addTime"), "2026-01-01", true);
		API_DEF_ADD_QUERY_PARAMS(String, "tag", ZH_WORDS_GETTER("translation.tag"), "", false);
		API_DEF_ADD_QUERY_PARAMS(Int32, "countLessonTotal", ZH_WORDS_GETTER("translation.countLessonTotal"), 0, true);
		API_DEF_ADD_QUERY_PARAMS(Int32, "doneLesson", ZH_WORDS_GETTER("translation.doneLesson"), 0, true);
		API_DEF_ADD_QUERY_PARAMS(String, "refund", ZH_WORDS_GETTER("translation.refund"), "", false);
		//支持授权
		API_DEF_ADD_AUTH();
		//定义响应参数格式
		API_DEF_ADD_RSP_JSON(StringJsonVO::Wrapper);
		//定义请求参数格式
		API_DEF_ADD_PAGE_PARAMS();
	}
private://定义执行函数
	StringJsonVO::Wrapper executeQueryRegistRecordDetails(const PageQuery::Wrapper& query);
};




#include OATPP_CODEGEN_END(ApiController) //<- End Codegen




#endif // _USERCONTROLLER_H_

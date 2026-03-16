#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/03/08 21:10:30

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
#ifndef _CLASSCONTRULLER_H_
#define _CLASSCONTROLLER_H_

#include "ApiHelper.h"
#include "ServerInfo.h"
#include "Macros.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/query/PageQuery.h"
#include "domain/vo/class/classVO.h"
#include "domain/query/class/classQuery.h"
#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("home.class.tag")
//班级模块控制器
class classController : public oatpp::web::server::api::ApiController
{
	// 定义控制器访问入口
	API_ACCESS_DECLARE(classController);
public: // 定义接口
	//1.1 定义获取班级列表控制器
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("home.class.get_class_list"), queryClassList, classListJsonVO::Wrapper, API_TAG,
		API_DEF_ADD_QUERY_PARAMS(UInt32, "student_id",ZH_WORDS_GETTER("home.class.student.id"),1,true);
	);

	//1.2 定义获取班级列表接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/home/class/list/query-by-student_id", queryClassList,QUERY(UInt32,student_id), execQueryClassList(student_id));

	//2.1 定义获取班级详情控制器
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("home.class.get_class_info"), queryClassInfo, classInfoJsonVO::Wrapper, API_TAG,
		API_DEF_ADD_QUERY_PARAMS(UInt32, "class_id", ZH_WORDS_GETTER("home.class.id"), 1, false);
	);

	//2.2 定义获取班级详情接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/home/class/info/query-by-class_id", queryClassInfo, QUERY(UInt32, class_id), execQueryClassInfo(class_id));

	//3.1 定义获取班级分页列表控制器（条件+分页）
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("home.class.get_class_page"), queryClassPage, classQuery, classPageJsonVO::Wrapper, API_TAG);
	
	// 3.2 定义获取职位列表（条件+分页）接口处理
	API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET, "/home/class/page/query-by-student_id", queryClassPage, QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(query, classQuery, queryParams); API_HANDLER_RESP_VO(execQueryClassPage(query)););

	//4.1 定义获取学生列表控制器
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("home.class.get_student_list"), queryStudentList, studentListJsonVO::Wrapper, API_TAG,
		API_DEF_ADD_QUERY_PARAMS(UInt32, "class_id", ZH_WORDS_GETTER("home.class.id"), 1, false);
	);

	//4.2 定义获取学生列表接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/home/class/student/list/query-by-class_id", queryStudentList, QUERY(UInt32, class_id), execQueryStudentList(class_id));

private: // 定义接口执行函数
	classListJsonVO::Wrapper execQueryClassList(const UInt32 &student_id);

	classInfoJsonVO::Wrapper execQueryClassInfo(const UInt32 &class_id);

	classPageJsonVO::Wrapper execQueryClassPage(const classQuery::Wrapper &query);

	studentListJsonVO::Wrapper execQueryStudentList(const UInt32& class_id);
};

#include OATPP_CODEGEN_END(ApiController)

#endif // !_CLASSCONTROLLER_H_
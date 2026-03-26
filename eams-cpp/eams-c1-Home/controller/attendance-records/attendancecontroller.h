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
#ifndef _ATTENDANCECONTROLLER_H_
#define _ATTENDANCECONTROLLER_H_

#include "ApiHelper.h"
#include "ServerInfo.h"
#include "Macros.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/query/PageQuery.h"
#include "domain/vo/attendance-records/attendanceVO.h"
#include "domain/query/attendance-records/attendanceQuery.h"
#define API_TAG ZH_WORDS_GETTER("attendance_records.tag")
#include OATPP_CODEGEN_BEGIN(ApiController)
//上课记录模块控制器
class attendanceController : public oatpp::web::server::api::ApiController
{
	// 定义控制器访问入口
	API_ACCESS_DECLARE(attendanceController);
public: // 定义接口
	//1.1 定义获取上课记录分页控制器
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(
		ZH_WORDS_GETTER("attendance_records.get_attendance_records_page"), queryAttendanceRecordsPage, attendance_recordsQuery, attendance_recordsPageJsonVO::Wrapper, API_TAG
	);
	//1.2 定义获取上课记录分页接口处理
	API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET, "/home/attendance_records/page/query-by-student_id", queryAttendanceRecordsPage, QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(query, attendance_recordsQuery, queryParams);API_HANDLER_RESP_VO(execQueryAttendanceRecordsPage(query)););

	//2.1 定义评价课次控制器
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("attendance_records.evaluate_attendance_records"), evaluateAttendanceRecords, attendance_recordsEvaluateJsonVO::Wrapper, API_TAG,
		API_DEF_ADD_QUERY_PARAMS(UInt32, "student_id", ZH_WORDS_GETTER("attendance_records.student_id"), 1, true);
	);
	// 2.2 定义评价课次接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/home/attendance_records/evaluate", evaluateAttendanceRecords, QUERY(UInt32, student_id), execEvaluateAttendanceRecords(student_id));


private: // 定义接口执行函数
	attendance_recordsPageJsonVO::Wrapper execQueryAttendanceRecordsPage(const attendance_recordsQuery::Wrapper& query);

	attendance_recordsEvaluateJsonVO::Wrapper execEvaluateAttendanceRecords(const UInt32& student_id);
};

#include OATPP_CODEGEN_END(ApiController)

#endif // !_ATTENDANCECONTROLLER_H_
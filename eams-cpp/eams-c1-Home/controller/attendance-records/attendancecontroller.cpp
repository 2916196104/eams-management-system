/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/03/08 21:19:14

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
#include "stdafx.h"
#include "attendancecontroller.h"
#include "../../service/attendance-records/attendanceService.h"
//实现接口执行函数
attendance_recordsPageJsonVO::Wrapper attendanceController::execQueryAttendanceRecordsPage(const attendance_recordsQuery::Wrapper& query) {
	// 查询数据
	auto result = Lesson_StudentService().listAll(query);
	// 响应结果
	auto jvo = attendance_recordsPageJsonVO::createShared();
	jvo->success(result);
	return jvo;
}

attendance_recordsEvaluateJsonVO::Wrapper attendanceController::execEvaluateAttendanceRecords(const UInt32& student_id) {
	auto dto = attendance_recordsEvaluateDTO::createShared();
	auto res = Teach_EvaluationService().saveData(dto);
	auto jvo = attendance_recordsEvaluateJsonVO::createShared();
	//jvo->success(res);
	return jvo;
}
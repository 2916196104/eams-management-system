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
#include "classcontroller.h"
#include "SimpleDateTimeFormat.h"
#include "../../service/class/classService.h"

classInfoJsonVO::Wrapper classController::execQueryClassInfo(const UInt32 &class_id) {
	auto res = ClassService().getById(class_id);
	if (res == nullptr) {
		auto jvo = classInfoJsonVO::createShared();
		jvo->fail(nullptr);
		return jvo;
	}
	auto jvo = classInfoJsonVO::createShared();
	jvo->success(res);
	return jvo;
}

classPageJsonVO::Wrapper classController::execQueryClassPage(const classQuery::Wrapper& query) {
	auto res = ClassService().listAll(query);
	// ÏìÓ¦½á¹û
	auto jvo = classPageJsonVO::createShared();
	jvo->success(res);
	return jvo;
}

studentListJsonVO::Wrapper classController::execQueryStudentList(const UInt32& class_id) {
	auto res = StudentService().listByClassId(class_id);
	auto jvo = studentListJsonVO::createShared();
	jvo->success(res);
	return jvo;
}


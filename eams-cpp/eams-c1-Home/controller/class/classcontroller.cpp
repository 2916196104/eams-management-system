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
//实现接口执行函数
classListJsonVO::Wrapper classController::execQueryClassList(const UInt32 &student_id) {
	return {};
}

classInfoJsonVO::Wrapper classController::execQueryClassInfo(const UInt32 &class_id) {
	return {};
}

classPageJsonVO::Wrapper classController::execQueryClassPage(const classQuery::Wrapper& query) {
	return {};
}

studentListJsonVO::Wrapper classController::execQueryStudentList(const UInt32& class_id) {
	return {};
}


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
#include "homeworkcontroller.h"
#include "service/homework/homeworkservice.h"

HomeworkPageJsonVO::Wrapper HomeworkController::execQueryPage(const HomeworkQuery::Wrapper& query)
{
	HomeworkService service;
	return service.queryPage(query);
}

HomeworkDetailJsonVO::Wrapper HomeworkController::execQueryDetail(const UInt64& id)
{
	HomeworkService service;
	return service.queryDetail(id);
}

HomeworkSubmitJsonVO::Wrapper HomeworkController::execQuerySubmit(const HomeworkSubmitDTO::Wrapper& dto)
{
	HomeworkService service;
	return service.submitHomework(dto);
}

HomeworkDeleteJsonVO::Wrapper HomeworkController::execQueryDelete(const HomeworkDeleteQuery::Wrapper& query)
{
	HomeworkService service;
	return service.deleteHomework(query);
}
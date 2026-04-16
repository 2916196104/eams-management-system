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
#include "scorecontroller.h"
#include "service/score/ScoreService.h"
//实现接口执行函数

// 实现获取成绩列表（条件+分页）接口执行函数
ScorePageJsonVO::Wrapper ScoreController::execQueryScore(const ScoreQuery::Wrapper& query)
{
	// 创建service层对象，调用查询函数
    ScoreService service;
    auto result = service.listAll(query);

	// 创建返回的vo对象
    auto jvo = ScorePageJsonVO::createShared();

	jvo->success(result);
	return jvo;
    //return {};
}

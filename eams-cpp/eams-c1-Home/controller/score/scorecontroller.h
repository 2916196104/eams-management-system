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
#ifndef _SCORECONTRULLER_H_
#define _SCORECONTROLLER_H_

#include "ApiHelper.h"
#include "ServerInfo.h"
#include "Macros.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/query/score/scorequery.h"
#include "domain/vo/score/scoreVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG_SCORE ZH_WORDS_GETTER("score.tag")
//成绩模块控制器
class ScoreController : public oatpp::web::server::api::ApiController
{
	// 定义控制器访问入口
	API_ACCESS_DECLARE(ScoreController);
public: // 定义接口
	// 定义获取成绩列表（条件+分页）接口描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(
		ZH_WORDS_GETTER("score.query-score.summary"), queryScore, ScoreQuery, ScorePageJsonVO::Wrapper, API_TAG_SCORE
	);
	// 定义获取成绩列表（条件+分页）接口处理
	API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/app/sCenter/student/gradeRecord", queryScore, ScoreQuery, execQueryScore(query));

private: // 定义接口执行函数
	// 定义获取成绩列表（条件+分页）接口执行函数
	ScorePageJsonVO::Wrapper execQueryScore(const ScoreQuery::Wrapper& query);
};

#include OATPP_CODEGEN_END(ApiController)

#endif // !_SCORECONTROLLER_H_
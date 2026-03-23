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
#include "TestController.h"

StringJsonVO::Wrapper TestController::executeQueryTest(const PageQuery::Wrapper& query)
{
	// 创建一个响应结果
	auto vo = StringJsonVO::createShared();
	// vo->success("操作成功"); 代码里面有中文错误写法有中文从中文词典中读取
	vo->success(ZH_WORDS_GETTER("test.resp"));
	return vo;
}

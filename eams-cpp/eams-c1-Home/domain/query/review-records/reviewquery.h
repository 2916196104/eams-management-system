#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/03/14 19:23:55

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
#ifndef _REVIEWQUERY_H_
#define _REVIEWQUERY_H_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 定义查询类
 */
// 查询某个学生的点评记录
class ReviewRecordQuery : public PageQuery
{
	DTO_INIT(ReviewRecordQuery, PageQuery);
	// 学生id
	API_DTO_FIELD_REQUIRE(Int64, student_id, ZH_WORDS_GETTER("review_records.student_id"), true);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_REVIEWQUERY_H_
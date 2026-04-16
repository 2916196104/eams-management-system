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
#ifndef _CLASSQUERY_H_
#define _CLASSQUERY_H_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 定义班级分页查询类
 */
class classQuery : public PageQuery
{
	DTO_INIT(classQuery, PageQuery);
	// 班级id
	API_DTO_FIELD_REQUIRE(UInt32, student_id, ZH_WORDS_GETTER("class.student.id"), true);
};
/*
class classinfoQuery : public oatpp::DTO
{
	DTO_INIT(classinfoQuery, DTO);
	// 班级id
	API_DTO_FIELD_REQUIRE(UInt32, classroom_id, ZH_WORDS_GETTER("class.id"), true);
	// 班级负责人id
	API_DTO_FIELD_DEFAULT(UInt32, teacher_id, ZH_WORDS_GETTER("class.teacher_id"));
	// 课程id
	API_DTO_FIELD_REQUIRE(UInt32, course_id, ZH_WORDS_GETTER("class.course_id"), true);
};
*/
#include OATPP_CODEGEN_END(DTO)

#endif // !_CLASSQUERY_H_
#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/03/14 19:15:19

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
#ifndef _SCOREDTO_H_
#define _SCOREDTO_H_

#include "../../GlobalInclude.h"
#include "domain/dto/PageDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 数据传输对象
 */
// 成绩DTO
class ScoreDTO : public oatpp::DTO
{
	DTO_INIT(ScoreDTO, DTO);
	// 唯一标识
	API_DTO_FIELD_DEFAULT(UInt64, id, ZH_WORDS_GETTER("score.id"));
	// 考核项id
	API_DTO_FIELD_DEFAULT(UInt64, grade_id, ZH_WORDS_GETTER("score.grade_id"));
	// 考核项名称
	API_DTO_FIELD_DEFAULT(String, grade_title, ZH_WORDS_GETTER("score.grade_title"));
	// 学生id
	API_DTO_FIELD_DEFAULT(UInt64, student_id, ZH_WORDS_GETTER("score.student_id"));
	// 学生姓名
	API_DTO_FIELD_DEFAULT(String, student_name, ZH_WORDS_GETTER("score.student_name"));
	// 分数
	API_DTO_FIELD_DEFAULT(Int8, score, ZH_WORDS_GETTER("score.score"));
	// 添加时间
	API_DTO_FIELD_DEFAULT(String, add_time, ZH_WORDS_GETTER("score.add_time"));
};

// 成绩分页DTO
class ScorePageDTO : public PageDTO<ScoreDTO::Wrapper>
{
	DTO_INIT(ScorePageDTO, PageDTO<ScoreDTO::Wrapper>)
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_SCOREDTO_H_
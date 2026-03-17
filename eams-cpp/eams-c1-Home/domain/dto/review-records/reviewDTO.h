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
#ifndef _REVIEWDTO_H_
#define _REVIEWDTO_H_

#include "../../GlobalInclude.h"
#include "domain/dto/PageDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 数据传输对象
 */
// 点评记录DTO
class ReviewRecordDTO : public oatpp::DTO
{
	DTO_INIT(ReviewRecordDTO, oatpp::DTO);
	// 唯一标识
	API_DTO_FIELD_DEFAULT(UInt64, id, ZH_WORDS_GETTER("review_records.id"));
	// 评价人
	API_DTO_FIELD_DEFAULT(String, creator_name, ZH_WORDS_GETTER("review_records.creator_name"));
	// 评价内容
	API_DTO_FIELD_DEFAULT(String, content, ZH_WORDS_GETTER("review_records.content"));
	// 评分星级
	API_DTO_FIELD_DEFAULT(Int8, score, ZH_WORDS_GETTER("review_records.score"));
	// 评价时间
	API_DTO_FIELD_DEFAULT(String, add_time, ZH_WORDS_GETTER("review_records.add_time"));
};

// 点评记录分页DTO
class ReviewRecordPageDTO : public PageDTO<ReviewRecordDTO::Wrapper>
{
	DTO_INIT(ReviewRecordPageDTO, PageDTO<ReviewRecordDTO::Wrapper>);
};


#include OATPP_CODEGEN_END(DTO)

#endif // !_REVIEWDTO_H_
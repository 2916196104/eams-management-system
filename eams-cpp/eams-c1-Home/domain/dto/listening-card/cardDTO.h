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
#ifndef _CARDDTO_H_
#define _CARDDTO_H_
#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)


 /**
  * 试听卡数据传输对象
  */
class ListeningCardDTO :public oatpp::DTO
{
	DTO_INIT(ListeningCardDTO, DTO);
	//试听卡对应的课程名
	API_DTO_FIELD_REQUIRE(String, course, ZH_WORDS_GETTER("ListeningCard.course"), true);
	//试听卡名称
	API_DTO_FIELD_REQUIRE(String, name, ZH_WORDS_GETTER("ListeningCard.name"), true);
	//试听卡领取的截止时间
	API_DTO_FIELD_REQUIRE(String,deadline, ZH_WORDS_GETTER("ListeningCard.deadline"), true);
	//试听卡有效日期
	API_DTO_FIELD_REQUIRE(String, effective_date, ZH_WORDS_GETTER("ListeningCard.effective_date"), true);
	//试听卡剩余量
	API_DTO_FIELD_REQUIRE(String, surplus, ZH_WORDS_GETTER("ListeningCard.surplus"), true);
	//试听卡次数
	API_DTO_FIELD_REQUIRE(String, cnt, ZH_WORDS_GETTER("ListeningCard.cnt"), true);
	//试听卡领取时间
	API_DTO_FIELD_REQUIRE(String, receive_time, ZH_WORDS_GETTER("ListeningCard.receive_time"),false);
};

/**
  * 试听卡分页数据传输对象
  */
class ListeningCardPageDTO :public PageDTO<ListeningCardDTO::Wrapper>
{
	DTO_INIT(ListeningCardPageDTO, PageDTO<ListeningCardDTO::Wrapper>);
};
#include OATPP_CODEGEN_END(DTO)

#endif // !_CARDDTO_H_
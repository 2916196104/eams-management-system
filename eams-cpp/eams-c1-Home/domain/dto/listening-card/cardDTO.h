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
	API_DTO_FIELD_REQUIRE(String, course, ZH_WORDS_GETTER("listening-card.course"), true);
	//试听卡名称
	API_DTO_FIELD_REQUIRE(String, name, ZH_WORDS_GETTER("listening-card.name"), true);
	//试听卡领取的截止时间
	API_DTO_FIELD_REQUIRE(String,deadline, ZH_WORDS_GETTER("listening-card.deadline"), true);
	//试听卡有效日期
	API_DTO_FIELD_REQUIRE(String, effective_date, ZH_WORDS_GETTER("listening-card.effective_date"), true);
	//试听卡剩余量
	API_DTO_FIELD_REQUIRE(String, surplus, ZH_WORDS_GETTER("listening-card.surplus"), true);
	//试听卡次数
	API_DTO_FIELD_REQUIRE(String, cnt, ZH_WORDS_GETTER("listening-card.cnt"), true);
	//试听卡领取时间
	API_DTO_FIELD_REQUIRE(String, receive_time, ZH_WORDS_GETTER("listening-card.receive_time"),false);
};

/**
  * 试听卡分页数据传输对象
  */
class ListeningCardPageDTO :public PageDTO<ListeningCardDTO::Wrapper>
{
	DTO_INIT(ListeningCardPageDTO, PageDTO<ListeningCardDTO::Wrapper>);
};

/**
  * 领取试听卡数据传输对象
  */
class receiveCardDTO :public oatpp::DTO {
	DTO_INIT(receiveCardDTO, DTO);
	//用户名
	API_DTO_FIELD_REQUIRE(String, userName, ZH_WORDS_GETTER("listening-card.userName"), true);
	//试听卡名称
	API_DTO_FIELD_REQUIRE(String, cardName, ZH_WORDS_GETTER("listening-card.name"), true);
};

 /**
  * 课程体验卡DTO
  */
class cardDTO : public oatpp::DTO {
    DTO_INIT(cardDTO, DTO);

    // 主键ID
    API_DTO_FIELD_DEFAULT(UInt64, id, ZH_WORDS_GETTER("listening-card.field.card.id"));
    // 课程ID
    API_DTO_FIELD_DEFAULT(UInt64, courseId, ZH_WORDS_GETTER("listening-card.field.card.courseId"));
    // 课程名称
	API_DTO_FIELD_DEFAULT(String, courseName, ZH_WORDS_GETTER("listening-card.field.card.courseName"));
    // 体验卡名称
    API_DTO_FIELD_DEFAULT(String, title, ZH_WORDS_GETTER("listening-card.field.card.title"));
    // 发行数量
    API_DTO_FIELD_DEFAULT(Int32, quantity, ZH_WORDS_GETTER("listening-card.field.card.quantity"));
    // 剩余数量
    API_DTO_FIELD_DEFAULT(Int32, remainingQuantity, ZH_WORDS_GETTER("listening-card.field.card.remainingQuantity"));
    // 课时数
    API_DTO_FIELD_DEFAULT(UInt32, lessonCount, ZH_WORDS_GETTER("listening-card.field.card.lessonCount"));
    // 领取后有效天数
    API_DTO_FIELD_DEFAULT(Int32, expireDays, ZH_WORDS_GETTER("listening-card.field.card.expireDays"));
    // 发行结束日期
    API_DTO_FIELD_DEFAULT(String, endDate, ZH_WORDS_GETTER("listening-card.field.card.endDate"));
    // 启用状态（1：启用，0：禁用）
    API_DTO_FIELD_DEFAULT(Int8, state, ZH_WORDS_GETTER("listening-card.field.card.state"));
	// 编辑时间 
	API_DTO_FIELD_DEFAULT(String, editTime, ZH_WORDS_GETTER("listening-card.field.card.editTime"));
	// 编辑者姓名
	API_DTO_FIELD_DEFAULT(String, editorName, ZH_WORDS_GETTER("listening-card.field.card.editorName"));
	// 领取记录数
	API_DTO_FIELD_DEFAULT(Int32, recordCount, ZH_WORDS_GETTER("listening-card.field.card.recordCount"));
};

/**
 * 试听卡规则DTO
*/
class cardRuleDTO : public oatpp::DTO {
    DTO_INIT(cardRuleDTO, DTO);
	// 规则ID
	API_DTO_FIELD_DEFAULT(UInt64, id, ZH_WORDS_GETTER("listening-card.field.rule.id"));
	// 规则组ID
	API_DTO_FIELD_DEFAULT(UInt64, settingId, ZH_WORDS_GETTER("listening-card.field.rule.settingId"));
	// 规则名称
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("listening-card.field.rule.name"));
	// 规则码
	API_DTO_FIELD_DEFAULT(String, code, ZH_WORDS_GETTER("listening-card.field.rule.code"));
	// 规则值
	API_DTO_FIELD_DEFAULT(String, value, ZH_WORDS_GETTER("listening-card.field.rule.value"));
	// 规则值类型
	API_DTO_FIELD_DEFAULT(String, valueType, ZH_WORDS_GETTER("listening-card.field.rule.valueType"));
	// 规则说明
	API_DTO_FIELD_DEFAULT(String, info, ZH_WORDS_GETTER("listening-card.field.rule.info"));
	// 规则排序
	API_DTO_FIELD_DEFAULT(Int32, sortNum, ZH_WORDS_GETTER("listening-card.field.rule.sortNum"));
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_CARDDTO_H_
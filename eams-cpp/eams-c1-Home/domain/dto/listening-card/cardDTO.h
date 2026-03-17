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
 * 数据传输对象
 */

 /**
  * 课程体验卡DTO
  */
class cardDTO : public oatpp::DTO {
    DTO_INIT(cardDTO, DTO);

    // 主键ID
    API_DTO_FIELD_DEFAULT(UInt64, id, ZH_WORDS_GETTER("home.listening-card.field.id"));
    // 课程ID
    API_DTO_FIELD_DEFAULT(UInt64, courseId, ZH_WORDS_GETTER("home.listening-card.field.courseId"));
    // 课程名称
	API_DTO_FIELD_DEFAULT(String, courseName, ZH_WORDS_GETTER("home.listening-card.field.courseName"));
    // 体验卡名称
    API_DTO_FIELD_DEFAULT(String, title, ZH_WORDS_GETTER("home.listening-card.field.title"));
    // 发行数量
    API_DTO_FIELD_DEFAULT(Int32, quantity, ZH_WORDS_GETTER("home.listening-card.field.quantity"));
    // 剩余数量
    API_DTO_FIELD_DEFAULT(Int32, remainingQuantity, ZH_WORDS_GETTER("home.listening-card.field.remainingQuantity"));
    // 课时数
    API_DTO_FIELD_DEFAULT(UInt32, lessonCount, ZH_WORDS_GETTER("home.listening-card.field.lessonCount"));
    // 领取后有效天数
    API_DTO_FIELD_DEFAULT(Int32, expireDays, ZH_WORDS_GETTER("home.listening-card.field.expireDays"));
    // 发行结束日期
    API_DTO_FIELD_DEFAULT(String, endDate, ZH_WORDS_GETTER("home.listening-card.field.endDate"));
    // 启用状态（1：启用，0：禁用）
    API_DTO_FIELD_DEFAULT(Int8, state, ZH_WORDS_GETTER("home.listening-card.field.state"));
    // 创建人
    API_DTO_FIELD_DEFAULT(Int64, creator, ZH_WORDS_GETTER("home.listening-card.field.creator"));
    // 编辑人
    API_DTO_FIELD_DEFAULT(Int64, editor, ZH_WORDS_GETTER("home.listening-card.field.editor"));
};

/**
 * 试听卡规则DTO（从setting_option表读取的公共规则）
 */
class cardRuleDTO : public oatpp::DTO {
    DTO_INIT(cardRuleDTO, DTO);
    // 规则内容（一段文字）
    API_DTO_FIELD_DEFAULT(String, content, ZH_WORDS_GETTER("home.listening-card.field.ruleContent"));
    // 规则描述
    API_DTO_FIELD_DEFAULT(String, description, ZH_WORDS_GETTER("home.listening-card.field.ruleDescription"));
};

/**
 * 试听卡列表请求DTO（无分页参数）
 */
/*****************   暂时无用（可拓展） *******************/
//class cardListRequestDTO : public oatpp::DTO {
//    DTO_INIT(cardListRequestDTO, DTO);
//
//    // 课程ID筛选（可选）
//    API_DTO_FIELD_DEFAULT(UInt64, courseId, ZH_WORDS_GETTER("trialcard.field.courseId"));
//    // 启用状态筛选（可选）
//    API_DTO_FIELD_DEFAULT(Int8, state, ZH_WORDS_GETTER("trialcard.field.state"));
//    // 组织ID筛选（可选）
//    API_DTO_FIELD_DEFAULT(Int64, orgId, ZH_WORDS_GETTER("common.field.orgId"));
//    // 关键字搜索（可选）
//    API_DTO_FIELD_DEFAULT(String, keyword, ZH_WORDS_GETTER("common.field.keyword"));
// };

#include OATPP_CODEGEN_END(DTO)

#endif // !_CARDDTO_H_
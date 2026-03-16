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
#ifndef _EXCHANGEDTO_H_
#define _EXCHANGEDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 数据传输对象
 */
 // 基于表 credit_mall
class GoodsDTO : public oatpp::DTO
{
	DTO_INIT(GoodsDTO, oatpp::DTO);

	API_DTO_FIELD_DEFAULT(Int64, deleted, ZH_WORDS_GETTER("exchange.field.deleted"));
	API_DTO_FIELD_DEFAULT(Int64, id, ZH_WORDS_GETTER("exchange.field.id"));
	API_DTO_FIELD_DEFAULT(Int64, schoolId, ZH_WORDS_GETTER("exchange.field.school_id"));
	API_DTO_FIELD_DEFAULT(String, addTime, ZH_WORDS_GETTER("exchange.field.add_time"));
	API_DTO_FIELD_DEFAULT(String, editTime, ZH_WORDS_GETTER("exchange.field.edit_time"));
	API_DTO_FIELD_DEFAULT(Int64, creator, ZH_WORDS_GETTER("exchange.field.creator"));
	API_DTO_FIELD_DEFAULT(Int64, editor, ZH_WORDS_GETTER("exchange.field.editor"));
	API_DTO_FIELD_DEFAULT(Int64, materialId, ZH_WORDS_GETTER("exchange.field.material_id"));
	API_DTO_FIELD_DEFAULT(Int64, categoryId, ZH_WORDS_GETTER("exchange.field.category_id"));
	API_DTO_FIELD_DEFAULT(String, categoryName, ZH_WORDS_GETTER("exchange.field.category_name"));
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("exchange.field.name"));
	API_DTO_FIELD_DEFAULT(Int64, credit, ZH_WORDS_GETTER("exchange.field.credit"));
	API_DTO_FIELD_DEFAULT(Int64, saleNum, ZH_WORDS_GETTER("exchange.field.sale_num"));
	API_DTO_FIELD_DEFAULT(Int64, viewNum, ZH_WORDS_GETTER("exchange.field.view_num"));
	API_DTO_FIELD_DEFAULT(String, cover, ZH_WORDS_GETTER("exchange.field.cover"));
	API_DTO_FIELD_DEFAULT(String, content, ZH_WORDS_GETTER("exchange.field.content"));
	API_DTO_FIELD_DEFAULT(Int64, state, ZH_WORDS_GETTER("exchange.field.state"));
	API_DTO_FIELD_DEFAULT(Int64, orgId, ZH_WORDS_GETTER("exchange.field.org_id"));
	API_DTO_FIELD_DEFAULT(String, schoolName, ZH_WORDS_GETTER("exchange.field.school_name")); // org表中的
	API_DTO_FIELD_DEFAULT(Int64, storage, ZH_WORDS_GETTER("exchange.field.storage")); // material表中的
};

class GoodsPageDTO : public PageDTO<GoodsDTO::Wrapper>
{
	DTO_INIT(GoodsPageDTO, PageDTO<GoodsDTO::Wrapper>);
};


// 基于表 credit_exchange
class AcceptGoodsDTO : public oatpp::DTO
{
	DTO_INIT(AcceptGoodsDTO, oatpp::DTO);

	API_DTO_FIELD_DEFAULT(String, addTime, ZH_WORDS_GETTER("exchange.field.add_time"));
	API_DTO_FIELD_DEFAULT(String, editTime, ZH_WORDS_GETTER("exchange.field.edit_time"));
	API_DTO_FIELD_DEFAULT(Int64, creator, ZH_WORDS_GETTER("exchange.field.creator"));
	API_DTO_FIELD_DEFAULT(Int64, editor, ZH_WORDS_GETTER("exchange.field.editor"));
	API_DTO_FIELD_DEFAULT(Int64, deleted, ZH_WORDS_GETTER("exchange.field.deleted"));
	API_DTO_FIELD_DEFAULT(Int64, id, ZH_WORDS_GETTER("exchange.field.id"));
	API_DTO_FIELD_DEFAULT(Int64, creditMallId, ZH_WORDS_GETTER("exchange.field.credit_mall_id"));
	API_DTO_FIELD_DEFAULT(Int64, studentId, ZH_WORDS_GETTER("exchange.field.student_id"));
	API_DTO_FIELD_DEFAULT(Int64, schoolId, ZH_WORDS_GETTER("exchange.field.school_id"));
	API_DTO_FIELD_DEFAULT(Int64, userId, ZH_WORDS_GETTER("exchange.field.user_id"));
	API_DTO_FIELD_DEFAULT(Int64, num, ZH_WORDS_GETTER("exchange.field.num"));
	API_DTO_FIELD_DEFAULT(String, credit, ZH_WORDS_GETTER("exchange.field.credit"));
	API_DTO_FIELD_DEFAULT(Int64, verifyState, ZH_WORDS_GETTER("exchange.field.verify_state"));
	API_DTO_FIELD_DEFAULT(Int64, verifyStaff, ZH_WORDS_GETTER("exchange.field.verify_staff"));
	API_DTO_FIELD_DEFAULT(String, verifyTime, ZH_WORDS_GETTER("exchange.field.verify_time"));
	API_DTO_FIELD_DEFAULT(String, verifyRemark, ZH_WORDS_GETTER("exchange.field.verify_remark"));
	API_DTO_FIELD_DEFAULT(String, creditMallName, ZH_WORDS_GETTER("exchange.field.name")); // credit_mall 数据库中的name
	API_DTO_FIELD_DEFAULT(String, cover, ZH_WORDS_GETTER("exchange.field.cover")); // credit_mall中
	API_DTO_FIELD_DEFAULT(String, studentName, ZH_WORDS_GETTER("exchange.field.student_name")); // student表
	API_DTO_FIELD_DEFAULT(String, schoolName, ZH_WORDS_GETTER("exchange.field.school_name")); // org表
	API_DTO_FIELD_DEFAULT(String, mobile, ZH_WORDS_GETTER("exchange.field.mobile")); // org表
	API_DTO_FIELD_DEFAULT(String, verifyStaffName, ZH_WORDS_GETTER("exchange.field.verify_staff_name")); // staff表
};

class AcceptGoodsPageDTO : public PageDTO<AcceptGoodsDTO::Wrapper>
{
	DTO_INIT(AcceptGoodsPageDTO, PageDTO<AcceptGoodsDTO::Wrapper>);
};


// 基于表 setting_option
class SettingDTO : public oatpp::DTO
{
	DTO_INIT(SettingDTO, oatpp::DTO);
	API_DTO_FIELD_DEFAULT(Int64, id, ZH_WORDS_GETTER("exchange.setting.id"));
	API_DTO_FIELD_DEFAULT(Int64, settingId, ZH_WORDS_GETTER("exchange.setting.setting_id"));
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("exchange.setting.name"));
	API_DTO_FIELD_DEFAULT(String, code, ZH_WORDS_GETTER("exchange.setting.code"));
	API_DTO_FIELD_DEFAULT(String, value, ZH_WORDS_GETTER("exchange.setting.value"));
	API_DTO_FIELD_DEFAULT(String, valueType, ZH_WORDS_GETTER("exchange.setting.value_type"));
	API_DTO_FIELD_DEFAULT(String, info, ZH_WORDS_GETTER("exchange.setting.info"));
	API_DTO_FIELD_DEFAULT(Int64, sortNum, ZH_WORDS_GETTER("exchange.setting.sort_num"));
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_EXCHANGEDTO_H_
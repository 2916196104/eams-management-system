#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 10:59:38

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
#ifndef _credit_mall_DTO_
#define _credit_mall_DTO_
#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class PayloadDTO;

/**
 * 积分商城礼品新增数据传输对象
 */
class credit_mallAddDTO : public oatpp::DTO
{
	DTO_INIT(credit_mallAddDTO, DTO);

	// 所属学校
	DTO_FIELD(UInt64, school_id);
	DTO_FIELD_INFO(school_id) {
		info->description = ZH_WORDS_GETTER("credit_mall.field.school_id");
	}

	// 物料分类
	DTO_FIELD(UInt64, material_id);
	DTO_FIELD_INFO(material_id) {
		info->description = ZH_WORDS_GETTER("credit_mall.field.material_id");
	}

	// 礼品分类ID
	DTO_FIELD(UInt64, category_id);
	DTO_FIELD_INFO(category_id) {
		info->description = ZH_WORDS_GETTER("credit_mall.field.category_id");
	}

	// 分类名称
	DTO_FIELD(String, category_name);
	DTO_FIELD_INFO(category_name) {
		info->description = ZH_WORDS_GETTER("credit_mall.field.category_name");
	}

	// 礼品名称
	DTO_FIELD(String, name);
	DTO_FIELD_INFO(name) {
		info->description = ZH_WORDS_GETTER("credit_mall.field.name");
	}

	// 兑换积分
	DTO_FIELD(Int32, credit);
	DTO_FIELD_INFO(credit) {
		info->description = ZH_WORDS_GETTER("credit_mall.field.credit");
	}

	// 是否可以兑换
	DTO_FIELD(Boolean, state);
	DTO_FIELD_INFO(state) {
		info->description = ZH_WORDS_GETTER("credit_mall.field.state");
	}

	// 历史兑换数量
	DTO_FIELD(UInt32, sale_num);
	DTO_FIELD_INFO(sale_num) {
		info->description = ZH_WORDS_GETTER("credit_mall.field.sale_num");
	}

	// 预览次数
	DTO_FIELD(UInt32, view_num);
	DTO_FIELD_INFO(view_num) {
		info->description = ZH_WORDS_GETTER("credit_mall.field.view_num");
	}

	// 封面
	DTO_FIELD(String, cover);
	DTO_FIELD_INFO(cover) {
		info->description = ZH_WORDS_GETTER("credit_mall.field.cover");
	}

	// 详情内容
	DTO_FIELD(String, content);
	DTO_FIELD_INFO(content) {
		info->description = ZH_WORDS_GETTER("credit_mall.field.content");
	}

	// 创建人
	DTO_FIELD(String, creator);
	DTO_FIELD_INFO(creator) {
		info->description = ZH_WORDS_GETTER("credit_mall.field.creator");
	}

	// 编辑人
	DTO_FIELD(String, editor);
	DTO_FIELD_INFO(editor) {
		info->description = ZH_WORDS_GETTER("credit_mall.field.editor");
	}

	// 添加时间
	DTO_FIELD(String, add_time);
	DTO_FIELD_INFO(add_time) {
		info->description = ZH_WORDS_GETTER("credit_mall.field.add_time");
	}

	// 编辑时间
	DTO_FIELD(String, edit_time);
	DTO_FIELD_INFO(edit_time) {
		info->description = ZH_WORDS_GETTER("credit_mall.field.edit_time");
	}

	// 删除标记
	DTO_FIELD(Boolean, deleted);
	DTO_FIELD_INFO(deleted) {
		info->description = ZH_WORDS_GETTER("credit_mall.field.deleted");
	}

	// 创建者所属组织ID
	DTO_FIELD(Int64, org_id);
	DTO_FIELD_INFO(org_id) {
		info->description = ZH_WORDS_GETTER("credit_mall.field.org_id");
	}

	// 保留CC_SYNTHESIZE宏，仅改类型为std::shared_ptr
	CC_SYNTHESIZE(std::shared_ptr<PayloadDTO>, _payload, Payload);

public:
	// 数据校验
	std::string validate()
	{
		// 必输字段校验
		if (!material_id) {
			return "物料分类(material_id)不能为空";
		}
		if (!category_id) {
			return "礼品分类ID(category_id)不能为空";
		}

		// ===== 核心修复：先通过getValue拿到原生std::string，再调用empty()/size() =====
		std::string name_str = name.getValue(""); // 空时返回空字符串
		if (name_str.empty()) { // 操作原生string，完全不碰m_ptr
			return "礼品名称(name)不能为空";
		}

		// 数值合理性校验
		if (credit && credit < 0) {
			return "兑换积分(credit)不能为负数";
		}
		if (sale_num && sale_num < 0) {
			return "历史兑换数量(sale_num)不能为负数";
		}
		if (view_num && view_num < 0) {
			return "预览次数(view_num)不能为负数";
		}

		// 字段长度校验（同样改用原生string）
		if (name_str.size() > 100) {
			return "礼品名称(name)长度不能超过100个字符";
		}
		std::string category_name_str = category_name.getValue("");
		if (category_name_str.size() > 100) {
			return "分类名称(category_name)长度不能超过100个字符";
		}
		std::string cover_str = cover.getValue("");
		if (cover_str.size() > 255) {
			return "封面(cover)长度不能超过255个字符";
		}

		// 状态字段校验（补充默认参数）
		if (state && (state.getValue(false) != true && state.getValue(false) != false)) {
			return "是否可兑换(state)只能是true或false";
		}
		if (deleted && (deleted.getValue(false) != true && deleted.getValue(false) != false)) {
			return "删除标记(deleted)只能是true或false";
		}

		return "";
	}
};

/**
 * 积分商城礼品传输对象（继承新增DTO，增加主键ID）
 */
class credit_mallDTO : public credit_mallAddDTO
{
	DTO_INIT(credit_mallDTO, credit_mallAddDTO);

	// 编号（主键）
	DTO_FIELD(String, id);
	DTO_FIELD_INFO(id) {
		info->description = ZH_WORDS_GETTER("credit_mall.field.id");
	}
};

/**
 * 积分商城礼品分页传输对象
 */
class credit_mallPageDTO : public PageDTO<credit_mallDTO::Wrapper>
{
	DTO_INIT(credit_mallPageDTO, PageDTO<credit_mallDTO::Wrapper>);
};

/**
 * 积分商城礼品导入数据传输对象
 */
class credit_mallImportDTO : public oatpp::DTO
{
	DTO_INIT(credit_mallImportDTO, DTO);

	// 导入报表文件
	API_DTO_FIELD_REQUIRE(oatpp::swagger::Binary, excel, ZH_WORDS_GETTER("credit_mall.field.excel"), true);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_credit_mall_DTO_
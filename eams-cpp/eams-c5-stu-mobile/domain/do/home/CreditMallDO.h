#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/3/19 11:00:00

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
#ifndef _CREDIT_MALL_DO_
#define _CREDIT_MALL_DO_

#include "../DoInclude.h"

/**
 * 积分商城礼品数据库实体类
 * 对应数据库表：credit_mall
 */
class CreditMallDO : public BaseDO
{
	// 主键ID（礼品唯一标识）

	MYSQL_SYNTHESIZE(string, id, Id);
	// 学校ID
	MYSQL_SYNTHESIZE(uint64_t, school_id, SchoolId);
	// 物料ID
	MYSQL_SYNTHESIZE(uint64_t, material_id, MaterialId);
	// 分类ID
	MYSQL_SYNTHESIZE(uint64_t, category_id, CategoryId);
	// 分类名称
	MYSQL_SYNTHESIZE(string, category_name, CategoryName);
	// 礼品名称
	MYSQL_SYNTHESIZE(string, name, Name);
	// 兑换所需积分
	MYSQL_SYNTHESIZE(int, credit, Credit);
	// 状态（1=可兑换，0=不可兑换）
	MYSQL_SYNTHESIZE(bool, state, State);
	// 兑换数量
	MYSQL_SYNTHESIZE(int, sale_num, SaleNum);
	// 预览数量
	MYSQL_SYNTHESIZE(int, view_num, ViewNum);
	// 封面图片URL
	MYSQL_SYNTHESIZE(string, cover, Cover);
	// 礼品详情内容
	MYSQL_SYNTHESIZE(string, content, Content);
	// 创建人
	MYSQL_SYNTHESIZE(string, creator, Creator);
	// 修改人
	MYSQL_SYNTHESIZE(string, editor, Editor);
	// 创建时间
	MYSQL_SYNTHESIZE(string, add_time, AddTime);
	// 修改时间
	MYSQL_SYNTHESIZE(string, edit_time, EditTime);
	// 删除标记（0=未删除，1=已删除）
	MYSQL_SYNTHESIZE(bool, deleted, Deleted);
	// 机构ID
	MYSQL_SYNTHESIZE(uint64_t, org_id, OrgId);

public:
	/**
	 * 构造函数：初始化表名+字段映射
	 */
	CreditMallDO() : BaseDO("credit_mall")
	{
		// 注册主键字段（PK）
		MYSQL_ADD_FIELD_PK("id", "s", id);

		// 注册普通字段（字段名, 类型标识, 成员变量）
		MYSQL_ADD_FIELD("school_id", "ll", school_id);      // ll: uint64_t类型
		MYSQL_ADD_FIELD("material_id", "ll", material_id);  // ll: uint64_t类型
		MYSQL_ADD_FIELD("category_id", "ll", category_id);  // ll: uint64_t类型
		MYSQL_ADD_FIELD("category_name", "s", category_name);// s: string类型
		MYSQL_ADD_FIELD("name", "s", name);                 // s: string类型
		MYSQL_ADD_FIELD("credit", "i", credit);             // i: int类型
		MYSQL_ADD_FIELD("state", "i", state);               // i: int类型
		MYSQL_ADD_FIELD("sale_num", "i", sale_num);         // i: int类型
		MYSQL_ADD_FIELD("view_num", "i", view_num);         // i: int类型
		MYSQL_ADD_FIELD("cover", "s", cover);               // s: string类型
		MYSQL_ADD_FIELD("content", "s", content);           // s: string类型
		MYSQL_ADD_FIELD("creator", "s", creator);           // s: string类型
		MYSQL_ADD_FIELD("editor", "s", editor);             // s: string类型
		MYSQL_ADD_FIELD("add_time", "s", add_time);         // s: string类型
		MYSQL_ADD_FIELD("edit_time", "s", edit_time);       // s: string类型
		MYSQL_ADD_FIELD("deleted", "i", deleted);           // i: int类型
		MYSQL_ADD_FIELD("org_id", "ll", org_id);            // ll: uint64_t类型
	}
};

// 智能指针别名：方便业务层使用
typedef std::shared_ptr<CreditMallDO> PtrCreditMallDO;

#endif // !_CREDIT_MALL_DO_
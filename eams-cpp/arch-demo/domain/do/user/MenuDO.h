#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2023/02/17 16:25:30

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
#ifndef _SAMPLEMENUDO_H_
#define _SAMPLEMENUDO_H_
#include "../DoInclude.h"

/**
 * 测试菜单数据库实体
 */
class MenuDO : public BaseDO
{
	// 唯一编号
	MYSQL_SYNTHESIZE(string, id, Id);
	// 菜单描述
	MYSQL_SYNTHESIZE(string, text, Text);
	// 菜单图标
	MYSQL_SYNTHESIZE(string, icon, Icon);
	// 路由地址
	MYSQL_SYNTHESIZE(string, href, Href);
	// 父菜单ID
	MYSQL_SYNTHESIZE(string, parentId, ParentId);
public:
	MenuDO() : BaseDO("sample_menu")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD_NULLABLE("text", "s", text, false);
		MYSQL_ADD_FIELD("icon", "s", icon);
		MYSQL_ADD_FIELD("href", "s", href);
		MYSQL_ADD_FIELD("parent_id", "s", parentId);
	}
	MenuDO(string id, string text, string icon, string href, string parentId) : MenuDO()
	{
		this->setId(id);
		this->setText(text);
		this->setIcon(icon);
		this->setHref(href);
		this->setParentId(parentId);
	}
};

// 定义一个菜单实体的智能指针
typedef std::shared_ptr<MenuDO> PtrMenuDO;

#endif // !_SAMPLEMENUDO_H_
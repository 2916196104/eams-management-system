#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 11:51:41

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
#ifndef _CARDDO_H_
#define _CARDDO_H_

#include "../DoInclude.h"
using namespace std;

/*
试听卡DDL
CREATE TABLE `course_trial` (
  `id` bigint unsigned NOT NULL AUTO_INCREMENT COMMENT '主键',
  `course_id` bigint unsigned NOT NULL COMMENT '课程',
  `title` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '名称',
  `quantity` int NOT NULL DEFAULT '0' COMMENT '发行数量',
  `remaining_quantity` int DEFAULT NULL COMMENT '剩余数量',
  `lesson_count` int unsigned NOT NULL DEFAULT '0' COMMENT '课时数',
  `expire_days` int NOT NULL COMMENT '领取后有效天数',
  `end_date` date NOT NULL COMMENT '发行结束日期',
  `state` tinyint(1) DEFAULT '1' COMMENT '启用状态',
  `creator` bigint DEFAULT NULL COMMENT '创建人',
  `editor` bigint DEFAULT NULL COMMENT '编辑人',
  `add_time` datetime DEFAULT NULL COMMENT '添加时间',
  `edit_time` datetime DEFAULT NULL COMMENT '编辑时间',
  `deleted` tinyint(1) DEFAULT '0' COMMENT '删除标记',
  `org_id` bigint DEFAULT NULL COMMENT '创建者所属组织ID',
  PRIMARY KEY (`id`) USING BTREE,
  KEY `course_id` (`course_id`) USING BTREE,
  KEY `org_id` (`org_id`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=18 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='课程体验卡';
*/

/**
* 试听卡DO
*/
class CardDO : public BaseDO
{
	// 主键ID
	MYSQL_SYNTHESIZE(unsigned long long, id, Id);
	// 课程ID
	MYSQL_SYNTHESIZE(unsigned long long, courseId, CourseId);
	// 课程名称（来自关联查询的字段，不直接存储在表中）
	MYSQL_SYNTHESIZE(string, courseName, CourseName);
	// 试听卡名称
	MYSQL_SYNTHESIZE(string, title, Title);
	// 发行数量
	MYSQL_SYNTHESIZE(int, quantity, Quantity);
	// 剩余数量
	MYSQL_SYNTHESIZE(int, remainingQuantity, RemainingQuantity);
	// 课时数
	MYSQL_SYNTHESIZE(int, lessonCount, LessonCount);
	// 领取后有效天数
	MYSQL_SYNTHESIZE(int, expireDays, ExpireDays);
	// 发行结束日期
	MYSQL_SYNTHESIZE(string, endDate, EndDate);
	// 启用状态
	MYSQL_SYNTHESIZE(bool, state, State);
	// 创建人
	MYSQL_SYNTHESIZE(unsigned long long, creator, Creator);
	// 编辑人
	MYSQL_SYNTHESIZE(unsigned long long, editor, Editor);
	// 添加时间
	MYSQL_SYNTHESIZE(string, addTime, AddTime);
	// 编辑时间
	MYSQL_SYNTHESIZE(string, editTime, EditTime);
	// 删除标记
	MYSQL_SYNTHESIZE(bool, deleted, Deleted);
	// 创建者所属组织ID
	MYSQL_SYNTHESIZE(unsigned long long, orgId, OrgId);
	// 编辑者名称（来自关联查询的字段，不直接存储在表中）
	MYSQL_SYNTHESIZE(string, editorName, EditorName);
	// 领取记录数（来自关联查询的字段，不直接存储在表中）
	MYSQL_SYNTHESIZE(int, recordCount, RecordCount);
public:
	CardDO() : BaseDO("course_trial") {
		MYSQL_ADD_FIELD_PK("id", "ull", id);
		MYSQL_ADD_FIELD_NULLABLE("course_id", "ull", courseId, false);
		MYSQL_ADD_FIELD("title", "s", title);
		MYSQL_ADD_FIELD("quantity", "i", quantity);
		MYSQL_ADD_FIELD_NULLABLE("remaining_quantity", "i", remainingQuantity, true);
		MYSQL_ADD_FIELD("lesson_count", "i", lessonCount);
		MYSQL_ADD_FIELD("expire_days", "i", expireDays);
		MYSQL_ADD_FIELD("end_date", "s", endDate);
		MYSQL_ADD_FIELD_NULLABLE("state", "i", state, true);
		MYSQL_ADD_FIELD_NULLABLE("creator", "ull", creator, true);
		MYSQL_ADD_FIELD_NULLABLE("editor", "ull", editor, true);
		MYSQL_ADD_FIELD_NULLABLE("add_time", "s", addTime, true);
		MYSQL_ADD_FIELD_NULLABLE("edit_time", "s", editTime, true);
		MYSQL_ADD_FIELD_NULLABLE("deleted", "i", deleted, true);
		MYSQL_ADD_FIELD_NULLABLE("org_id", "ull", orgId, true);
	}
};

// 定义一个智能指针别名方便引用
typedef std::shared_ptr<CardDO> PtrCardDO;

/*
*	设置DDL
	CREATE TABLE `setting_option` (
	  `id` bigint unsigned NOT NULL AUTO_INCREMENT COMMENT '主键',
	  `setting_id` bigint NOT NULL COMMENT '组id',
	  `name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '名称',
	  `code` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '码',
	  `value` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci DEFAULT NULL COMMENT '值',
	  `value_type` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci DEFAULT 'str' COMMENT '值数据类型',
	  `info` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci DEFAULT NULL COMMENT '说明',
	  `sort_num` int DEFAULT '0' COMMENT '排序',
	  PRIMARY KEY (`id`) USING BTREE,
	  UNIQUE KEY `code` (`code`) USING BTREE
	) ENGINE=InnoDB AUTO_INCREMENT=40 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='系统设置表';
*/
/* 
	获取试听卡规则DO
*/
class CardRuleDO : public BaseDO
{
	// 规则ID
	MYSQL_SYNTHESIZE(unsigned long long, id, Id);
	// 规则组ID
	MYSQL_SYNTHESIZE(unsigned long long, settingId, SettingId);
	// 规则名称
	MYSQL_SYNTHESIZE(string, name, Name);
	// 规则码
	MYSQL_SYNTHESIZE(string, code, Code);
	// 规则值
	MYSQL_SYNTHESIZE(string, value, Value);
	// 规则值类型
	MYSQL_SYNTHESIZE(string, valueType, ValueType);
	// 规则说明
	MYSQL_SYNTHESIZE(string, info, Info);
	// 规则排序
	MYSQL_SYNTHESIZE(int, sortNum, SortNum);
public:
	CardRuleDO() : BaseDO("setting_option") {
		MYSQL_ADD_FIELD_PK("id", "ull", id);
		MYSQL_ADD_FIELD_NULLABLE("setting_id", "ull", settingId, false);
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD("code", "s", code);
		MYSQL_ADD_FIELD_NULLABLE("value", "s", value, true);
		MYSQL_ADD_FIELD_NULLABLE("value_type", "s", valueType, true);
		MYSQL_ADD_FIELD_NULLABLE("info", "s", info, true);
		MYSQL_ADD_FIELD_NULLABLE("sort_num", "i", sortNum, true);
	}
};
// 定义一个智能指针别名方便引用
typedef std::shared_ptr<CardRuleDO> PtrCardRuleDO;

#endif // !_DO_INCLUDE_

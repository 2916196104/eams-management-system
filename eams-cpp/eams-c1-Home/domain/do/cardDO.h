#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: your_name
 @Date: 2024/05/24 10:00:00

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
#ifndef _CARD_DO_H
#define _CARD_DO_H
#include "DoInclude.h"

/**
 * 课程体验卡数据实体
 */
class cardDO : public BaseDO
{
	// 主键
	MYSQL_SYNTHESIZE(long long, id, Id);
	// 课程ID
	MYSQL_SYNTHESIZE(long long, courseId, CourseId);
	// 体验卡名称
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
	MYSQL_SYNTHESIZE(int, state, State);
	// 创建人
	MYSQL_SYNTHESIZE(long long, creator, Creator);
	// 编辑人
	MYSQL_SYNTHESIZE(long long, editor, Editor);
	// 添加时间
	MYSQL_SYNTHESIZE(string, addTime, AddTime);
	// 编辑时间
	MYSQL_SYNTHESIZE(string, editTime, EditTime);
	// 删除标记
	MYSQL_SYNTHESIZE(int, deleted, Deleted);
	// 创建者所属组织ID
	MYSQL_SYNTHESIZE(long long, orgId, OrgId);

public:
	cardDO() : BaseDO("card")
	{
		MYSQL_ADD_FIELD_PK("id", "l", id);
		MYSQL_ADD_FIELD("course_id", "l", courseId);
		MYSQL_ADD_FIELD("title", "s", title);
		MYSQL_ADD_FIELD("quantity", "i", quantity);
		MYSQL_ADD_FIELD("remaining_quantity", "i", remainingQuantity);
		MYSQL_ADD_FIELD("lesson_count", "i", lessonCount);
		MYSQL_ADD_FIELD("expire_days", "i", expireDays);
		MYSQL_ADD_FIELD("end_date", "s", endDate);
		MYSQL_ADD_FIELD("state", "i", state);
		MYSQL_ADD_FIELD("creator", "l", creator);
		MYSQL_ADD_FIELD("editor", "l", editor);
		MYSQL_ADD_FIELD("add_time", "s", addTime);
		MYSQL_ADD_FIELD("edit_time", "s", editTime);
		MYSQL_ADD_FIELD("deleted", "i", deleted);
		MYSQL_ADD_FIELD("org_id", "l", orgId);
	}
};

// 定义一个试听卡实体的智能指针
typedef std::shared_ptr<cardDO> PtrCardDO;
#endif // !_CARD_DO_H
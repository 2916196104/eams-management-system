#pragma once
#ifndef _GETTRIALCARD_DO_
#define _GETTRIALCARD_DO_
#include "../../DoInclude.h"

class GetTrialcardDO :public BaseDO {
	// ====================== 1. 定义属性 + 自动生成get/set方法 ======================
// 主键ID（bigint unsigned → uint64_t，非空自增）
	MYSQL_SYNTHESIZE(uint64_t, id, Id);
	// 课程ID（bigint unsigned → uint64_t，非空）
	MYSQL_SYNTHESIZE(uint64_t, courseId, CourseId);
	// 名称（varchar(255) → string，非空，utf8mb4）
	MYSQL_SYNTHESIZE(string, title, Title);
	// 发行数量（int → int，非空，默认0）
	MYSQL_SYNTHESIZE(int, quantity, Quantity);
	// 剩余数量（int → int，默认NULL）
	MYSQL_SYNTHESIZE(int, remainingQuantity, RemainingQuantity);
	// 课时数（int unsigned → uint32_t/int，非空，默认0）
	MYSQL_SYNTHESIZE(int, lessonCount, LessonCount);
	// 领取后有效天数（int → int，非空）
	MYSQL_SYNTHESIZE(int, expireDays, ExpireDays);
	// 发行结束日期（date → string，非空）
	MYSQL_SYNTHESIZE(string, endDate, EndDate);
	// 启用状态（tinyint(1) → int，默认1）
	MYSQL_SYNTHESIZE(int, state, State);
	// 创建人（bigint → uint64_t，默认NULL）
	MYSQL_SYNTHESIZE(uint64_t, creator, Creator);
	// 编辑人（bigint → uint64_t，默认NULL）
	MYSQL_SYNTHESIZE(uint64_t, editor, Editor);
	// 添加时间（datetime → string，默认NULL）
	MYSQL_SYNTHESIZE(string, addTime, AddTime);
	// 编辑时间（datetime → string，默认NULL）
	MYSQL_SYNTHESIZE(string, editTime, EditTime);
	// 删除标记（tinyint(1) → int，默认0，0=未删/1=已删）
	MYSQL_SYNTHESIZE(int, deleted, Deleted);
	// 创建者所属组织ID（bigint → uint64_t，默认NULL）
	MYSQL_SYNTHESIZE(uint64_t, orgId, OrgId);
public:
	GetTrialcardDO() :BaseDO("course_trial")
	{
		// 主键字段映射
		MYSQL_ADD_FIELD_PK("id", "i", id);

		// 普通字段映射（严格按表字段顺序）
		MYSQL_ADD_FIELD("course_id", "i", courseId);
		MYSQL_ADD_FIELD("title", "s", title);
		MYSQL_ADD_FIELD("quantity", "i", quantity);
		MYSQL_ADD_FIELD("remaining_quantity", "i", remainingQuantity);
		MYSQL_ADD_FIELD("lesson_count", "i", lessonCount);
		MYSQL_ADD_FIELD("expire_days", "i", expireDays);
		MYSQL_ADD_FIELD("end_date", "s", endDate);
		MYSQL_ADD_FIELD("state", "i", state);
		MYSQL_ADD_FIELD("creator", "i", creator);
		MYSQL_ADD_FIELD("editor", "i", editor);
		MYSQL_ADD_FIELD("add_time", "s", addTime);
		MYSQL_ADD_FIELD("edit_time", "s", editTime);
		MYSQL_ADD_FIELD("deleted", "i", deleted);
		MYSQL_ADD_FIELD("org_id", "i", orgId);
	}
};
typedef std::shared_ptr<GetTrialcardDO> PtrGetTrialcardDO;
#endif // !_GETTRIALCARD_DO_

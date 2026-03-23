#pragma once
#ifndef OPERATION_RECORD_DO_H
#define OPERATION_RECORD_DO_H

#include "../DoInclude.h"

/**
 * operation_record表数据库实体类
 */
class OperationRecordDO : public BaseDO
{
	// 主键ID
	MYSQL_SYNTHESIZE(long long, id, Id);
	// 操作类型
	MYSQL_SYNTHESIZE(int, type, Type);
	// 关联项ID
	MYSQL_SYNTHESIZE(long long, itemId, ItemId);
	// 状态
	MYSQL_SYNTHESIZE(string, state, State);
	// 操作内容
	MYSQL_SYNTHESIZE(string, content, Content);
	// 创建人
	MYSQL_SYNTHESIZE(long long, creator, Creator);
	// 添加时间
	MYSQL_SYNTHESIZE(string, addTime, AddTime);
	// 组织ID
	MYSQL_SYNTHESIZE(long long, orgId, OrgId);

public:
	OperationRecordDO() : BaseDO("operation_record")
	{
		// 主键
		MYSQL_ADD_FIELD_PK("id", "i", id);
		// 操作类型
		MYSQL_ADD_FIELD("type", "i", type);
		// 关联项ID
		MYSQL_ADD_FIELD("item_id", "i", itemId);
		// 状态
		MYSQL_ADD_FIELD("state", "s", state);
		// 操作内容
		MYSQL_ADD_FIELD("content", "s", content);
		// 创建人
		MYSQL_ADD_FIELD("creator", "i", creator);
		// 添加时间
		MYSQL_ADD_FIELD("add_time", "s", addTime);
		// 组织ID
		MYSQL_ADD_FIELD("org_id", "i", orgId);
	}
};

typedef std::shared_ptr<OperationRecordDO> PtrOperationRecordDO;

#endif // OPERATION_RECORD_DO_H
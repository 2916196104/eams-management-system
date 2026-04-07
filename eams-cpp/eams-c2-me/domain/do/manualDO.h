#pragma once
#ifndef _MANUAL_DO_
#define _MANUAL_DO_
#include "domain/do/DoInclude.h"
//DO对象与数据库表结构一一对应，用于DAO层与数据库交互
class ManualDO : public BaseDO {
	// 使用宏定义字段 提供get、set方法
	MYSQL_SYNTHESIZE(uint64_t, _id, Id);
	MYSQL_SYNTHESIZE(std::string, _title, Title);
	MYSQL_SYNTHESIZE(std::string, _content, Content);
	MYSQL_SYNTHESIZE(std::string, _type, Type);
	MYSQL_SYNTHESIZE(int64_t, _creator, Creator);
	MYSQL_SYNTHESIZE(std::string, _addTime, AddTime);
	MYSQL_SYNTHESIZE(bool, _deleted, Deleted);
	MYSQL_SYNTHESIZE(std::string, _editTime, EditTime);
	MYSQL_SYNTHESIZE(int64_t, _editor, Editor);
	MYSQL_SYNTHESIZE(bool, _state, State);
	MYSQL_SYNTHESIZE(int, _sortNum, SortNum);
public:
	// 构造函数中注册字段
	ManualDO() :BaseDO("help") // "help"是表名
	{
		// 注册主键字段
		MYSQL_ADD_FIELD_PK("id", "i", _id);
		// 注册普通字段
		MYSQL_ADD_FIELD("title", "s", _title);
		MYSQL_ADD_FIELD("content", "s", _content);
		MYSQL_ADD_FIELD("type", "s", _type);
		MYSQL_ADD_FIELD("creator", "i", _creator);
		MYSQL_ADD_FIELD("add_time", "dt", _addTime);
		MYSQL_ADD_FIELD("deleted", "b", _deleted);
		MYSQL_ADD_FIELD("edit_time", "dt", _editTime);
		MYSQL_ADD_FIELD("editor", "i", _editor);
		MYSQL_ADD_FIELD("state", "b", _state);
		MYSQL_ADD_FIELD("sort_num", "i", _sortNum);
	}
};
typedef std::shared_ptr<ManualDO> PtrManualDO;
#endif

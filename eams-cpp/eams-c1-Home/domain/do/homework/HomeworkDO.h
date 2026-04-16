#pragma once
#ifndef _HOMEWORK_DO_
#define _HOMEWORK_DO_
#include"../DoInclude.h"
class HomeworkDO :public BaseDO {
	MYSQL_SYNTHESIZE(uint64_t, id, Id);
	MYSQL_SYNTHESIZE(uint64_t, classId, ClassId);
	MYSQL_SYNTHESIZE(string, title, Title);
	MYSQL_SYNTHESIZE(string, content, Content);
	MYSQL_SYNTHESIZE(uint64_t, creator, Creator);
	MYSQL_SYNTHESIZE(uint64_t, editor, Editor);
	MYSQL_SYNTHESIZE(string, addTime, AddTime);
	MYSQL_SYNTHESIZE(string, editTime, EditTime);
	MYSQL_SYNTHESIZE(int, deleted, Deleted);
	MYSQL_SYNTHESIZE(uint64_t, orgId, OrgId);

public:
	HomeworkDO() :BaseDO("homework") {
		MYSQL_ADD_FIELD_PK("id", "ull", id);
		MYSQL_ADD_FIELD("class_id", "ull", classId);
		MYSQL_ADD_FIELD("title", "s", title);
		MYSQL_ADD_FIELD("content", "s", content);
		MYSQL_ADD_FIELD("creator", "ull", creator);
		MYSQL_ADD_FIELD("editor", "ull", editor);
		MYSQL_ADD_FIELD("add_time", "s", addTime);
		MYSQL_ADD_FIELD("edit_time", "s", editTime);
		MYSQL_ADD_FIELD("deleted", "i", deleted);
		MYSQL_ADD_FIELD("org_id", "ull", orgId);
	}



};


typedef std::shared_ptr<HomeworkDO> PtrHomeworkDO;
#endif
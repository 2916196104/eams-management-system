#pragma once
#ifndef _HOMEWORK_DO_
#define _HOMEWORK_DO_
#include"../DoInclude.h"
class HomeworkDO :public BaseDO {
	MYSQL_SYNTHESIZE(string, id, Id);
	MYSQL_SYNTHESIZE(string, title, Title);
	MYSQL_SYNTHESIZE(string, content, Content);
	MYSQL_SYNTHESIZE(string, publisher, Publisher);
	MYSQL_SYNTHESIZE(string, publishTime, PublishTime);

public:
	HomeworkDO() :BaseDO("homework") {
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD_PK("title", "s", title);
		MYSQL_ADD_FIELD("content", "s", content);
		MYSQL_ADD_FIELD("publisher", "s", publisher);
		MYSQL_ADD_FIELD("publish_time", "s", publishTime);
	}



};


typedef std::shared_ptr<HomeworkDO> PtrHomeworkDO;
#endif
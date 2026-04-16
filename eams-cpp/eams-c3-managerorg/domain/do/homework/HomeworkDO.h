#pragma once

#ifndef __HOMEWORK_DO_H__
#define __HOMEWORK_DO_H__
#include "../DoInclude.h"


//作业DO
//兄弟我需要用你的这个DO，必须是HomeworkDO:public BaseDO
class HomeworkDO:public BaseDO
{
	//主键ID（作业记录唯一标识）
	MYSQL_SYNTHESIZE(int, id, Id);
	//班级ID
	MYSQL_SYNTHESIZE(int, classId, ClassId);
	//作业标题
	MYSQL_SYNTHESIZE(string, title, Title);
	//作业内容
	MYSQL_SYNTHESIZE(string, content, Content);
	//创建人
	MYSQL_SYNTHESIZE(int, creator, Creator);
	//编辑人
	MYSQL_SYNTHESIZE(int, editor, Editor);
	//添加时间
	MYSQL_SYNTHESIZE(string, addTime, AddTime); //兄弟，这个时间字段我用string类型了，阿伟的arch-demo中创建时间用的是string
	//编辑时间
	MYSQL_SYNTHESIZE(string, editTime, EditTime);
	//删除标记
	MYSQL_SYNTHESIZE(int,deleted,Deleted);
	//创建者所属组织ID
	MYSQL_SYNTHESIZE(int, orgId, OrgId);
public:
	HomeworkDO() :BaseDO("homework") {
		MYSQL_ADD_FIELD_PK("id", "i", id);
		MYSQL_ADD_FIELD("class_id", "i", classId);
		MYSQL_ADD_FIELD("title", "s", title);
		MYSQL_ADD_FIELD("content", "s", content);
		MYSQL_ADD_FIELD("creator", "i", creator);
		MYSQL_ADD_FIELD("editor", "i", editor);
		MYSQL_ADD_FIELD("add_time", "t", addTime);
		MYSQL_ADD_FIELD("edit_time", "t", editTime);
		MYSQL_ADD_FIELD("deleted", "i", deleted);
		MYSQL_ADD_FIELD("org_id", "i", orgId);
	}
};


//定义智能指针
typedef std::shared_ptr<HomeworkDO> PtrHomeworkDO;




#endif
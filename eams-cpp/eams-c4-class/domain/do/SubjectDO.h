#pragma once
#ifndef SBJECTDO_H_
#define SBJECTDO_H_

#include "../DoInclude.h"

class SubjectDO : public BaseDO
{
	// 科目唯一ID
	MYSQL_SYNTHESIZE(int, id, Id);
	// 科目名称
	MYSQL_SYNTHESIZE(string, name, Name);
	// 科目简介
	MYSQL_SYNTHESIZE(string, info, Info);
	//创建人
	MYSQL_SYNTHESIZE(int, creator, Creator);
	//编辑者
	MYSQL_SYNTHESIZE(int, editor, Editor);
	//新增时间
	MYSQL_SYNTHESIZE(string, createTime, CreateTime);
	//修改时间
	MYSQL_SYNTHESIZE(string, editTime, EditTime);
	//删除标志
	MYSQL_SYNTHESIZE(int, deleted, Deleted);
	//排序值
	MYSQL_SYNTHESIZE(int, sort, Sort);
	创建者所属组织ID
	MYSQL_SYNTHESIZE(int, orgId, OrgId);
public:
	SubjectDO() : BaseDO("subject")
	{
		MYSQL_ADD_FIELD_PK("id","i",id);
		MYSQL_ADD_FIELD_NULLABLE("name", "s", name,false);
		MYSQL_ADD_FIELD_NULLABLE("info", "s", info,true);
		MYSQL_ADD_FIELD_NULLABLE("creator", "i", creator,false);
		MYSQL_ADD_FIELD_NULLABLE("editor", "i", editor,false);
		MYSQL_ADD_FIELD_NULLABLE("create_time", "s", createTime,false);
		MYSQL_ADD_FIELD_NULLABLE("edit_time", "s", editTime,false);
		MYSQL_ADD_FIELD_NULLABLE("deleted", "i", deleteFlag,false);
		MYSQL_ADD_FIELD_NULLABLE("sort", "i", sort,false);
		MYSQL_ADD_FIELD_NULLABLE("org_id", "i", orgId,true);
	}
};
typedef shared_ptr<SubjectDO> SubjectDOPtr;
#endif // !SBJECTDO_H_

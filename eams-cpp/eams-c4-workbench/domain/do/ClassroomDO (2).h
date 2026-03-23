#pragma once
#ifndef CLASSROOM_DO_
#define CLASSROOM_DO_

#include "../DoInclude.h"

class ClassroomDO : public BaseDO
{
	// 教室唯一ID
	MYSQL_SYNTHESIZE(int, id, Id);
	// 教室名称
	MYSQL_SYNTHESIZE(string, name, Name);
	//面积
	MYSQL_SYNTHESIZE(int, area, Area);
	// 备注
	MYSQL_SYNTHESIZE(string, remark,Remark);
	//创建人
	MYSQL_SYNTHESIZE(int, creator, Creator);
	//编辑者
	MYSQL_SYNTHESIZE(int, editor, Editor);
	//创建时间
	MYSQL_SYNTHESIZE(string, addTime, AddTime);
	//修改时间
	MYSQL_SYNTHESIZE(string, editTime, EditTime);
	//删除标志
	MYSQL_SYNTHESIZE(int, deleted, Deleted);
	//创建者所属学校ID
	MYSQL_SYNTHESIZE(int, schoolId, SchoolId);
	//创建者所属组织ID
	MYSQL_SYNTHESIZE(int, orgId, OrgId);
public:
	ClassroomDO() : BaseDO("classroom")
	{
		MYSQL_ADD_FIELD_PK("id", "i", id);
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD("area", "i", area);
		MYSQL_ADD_FIELD("remark", "s", remark);
		MYSQL_ADD_FIELD("creator", "i", creator);
		MYSQL_ADD_FIELD("editor", "i", editor);
		MYSQL_ADD_FIELD("add_time", "s", addTime);
		MYSQL_ADD_FIELD("edit_time", "s", editTime);
		MYSQL_ADD_FIELD("deleted", "i", deleted);
		MYSQL_ADD_FIELD("school_id", "i", schoolId);
		MYSQL_ADD_FIELD("org_id", "i", orgId);
	}
};
typedef shared_ptr<ClassroomDO> ClassroomDOPtr;
#endif // !CLASSROOM_DO_

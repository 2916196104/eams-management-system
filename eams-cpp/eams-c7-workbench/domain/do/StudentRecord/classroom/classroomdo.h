#pragma once
#ifndef _CLASSROOM_DO_
#define _CLASSROOM_DO_
//classroom表格do对象
#include "../DoInclude.h"

/**
 * classroom数据库实体类
 */
class ClassroomDO : public BaseDO
{
	// 教室主键ID
	MYSQL_SYNTHESIZE(int64_t, id, Id);
	// 教室名称
	MYSQL_SYNTHESIZE(string, name, Name);
	// 教室地址
	MYSQL_SYNTHESIZE(string, address, Address);
	// 教室区域/面积
	MYSQL_SYNTHESIZE(int, area, Area);
	// 备注信息
	MYSQL_SYNTHESIZE(string, remark, Remark);
	// 创建人
	MYSQL_SYNTHESIZE(int64_t, creator, Creator);
	// 修改人
	MYSQL_SYNTHESIZE(int64_t, editor, Editor);
	// 数据添加时间
	MYSQL_SYNTHESIZE(string, add_time, AddTime);
	// 数据修改时间
	MYSQL_SYNTHESIZE(string, edit_time, EditTime);
	// 是否删除标识
	MYSQL_SYNTHESIZE(int, deleted, Deleted);
	// 所属学校ID
	MYSQL_SYNTHESIZE(int64_t, school_id, SchoolId);
	// 所属机构ID
	MYSQL_SYNTHESIZE(int64_t, org_id, OrgId);
public:
	ClassroomDO() : BaseDO("classroom")
	{
		MYSQL_ADD_FIELD_PK("id", "l", id);
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD("address", "s", address);
		MYSQL_ADD_FIELD("area", "i", area);
		MYSQL_ADD_FIELD("remark", "s", remark);
		MYSQL_ADD_FIELD("creator", "l", creator);
		MYSQL_ADD_FIELD("editor", "l", editor);
		MYSQL_ADD_FIELD("add_time", "s", add_time);
		MYSQL_ADD_FIELD("edit_time", "s", edit_time);
		MYSQL_ADD_FIELD("deleted", "i", deleted);
		MYSQL_ADD_FIELD("school_id", "l", school_id);
		MYSQL_ADD_FIELD("org_id", "l", org_id);
	}
};

// 给SampleDO智能指针设定一个别名方便使用
typedef std::shared_ptr<ClassroomDO> PtrClassroomDO;




#endif 

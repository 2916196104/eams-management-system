#pragma once
#ifndef STAFFORGINFODO_H
#define STAFFORGINFODO_H

#include "../do/DoInclude.h"

/**
 * staff_orginfo表数据库实体类
 */
class StaffOrginfoDO : public BaseDO
{
	// 主键ID
	MYSQL_SYNTHESIZE(long long, id, Id);
	// 员工ID
	MYSQL_SYNTHESIZE(long long, staffId, StaffId);
	// 所属机构ID
	MYSQL_SYNTHESIZE(long long, orgId, OrgId);
	// 所属集团ID
	MYSQL_SYNTHESIZE(long long, groupId, GroupId);
	// 所属公司ID
	MYSQL_SYNTHESIZE(long long, comId, ComId);
	// 所属部门ID
	MYSQL_SYNTHESIZE(long long, dptId, DptId);
	// 所属职位ID
	MYSQL_SYNTHESIZE(long long, positionId, PositionId);
	// 删除标记
	MYSQL_SYNTHESIZE(int, deleted, Deleted);
	// 创建时间
	MYSQL_SYNTHESIZE(string, addTime, AddTime);
	// 创建人
	MYSQL_SYNTHESIZE(long long, creator, Creator);
	// ID全路径
	MYSQL_SYNTHESIZE(string, idPath, IdPath);

public:
	StaffOrginfoDO() : BaseDO("staff_orginfo")
	{
		// 主键
		MYSQL_ADD_FIELD_PK("id", "i", id);
		// 员工ID
		MYSQL_ADD_FIELD("staff_id", "i", staffId);
		// 所属机构ID
		MYSQL_ADD_FIELD("org_id", "i", orgId);
		// 所属集团ID
		MYSQL_ADD_FIELD("group_id", "i", groupId);
		// 所属公司ID
		MYSQL_ADD_FIELD("com_id", "i", comId);
		// 所属部门ID
		MYSQL_ADD_FIELD("dpt_id", "i", dptId);
		// 所属职位ID
		MYSQL_ADD_FIELD("position_id", "i", positionId);
		// 删除标记
		MYSQL_ADD_FIELD("deleted", "i", deleted);
		// 创建时间
		MYSQL_ADD_FIELD("add_time", "s", addTime);
		// 创建人
		MYSQL_ADD_FIELD("creator", "i", creator);
		// ID全路径
		MYSQL_ADD_FIELD("id_path", "s", idPath);
	}
};

typedef std::shared_ptr<StaffOrginfoDO> PtrStaffOrginfoDO;

#endif // STAFFORGINFODO_H

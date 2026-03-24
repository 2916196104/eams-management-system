#pragma once
#ifndef _ORG_DO_
#define _ORG_DO_
#include "../DoInclude.h"

/**
 * 机构表数据库实体类
 * 对应表: org
 */
class OrgDO : public BaseDO
{
	// 主键 (bigint unsigned - 64位无符号整数)
	MYSQL_SYNTHESIZE(uint64_t, id, Id);
	// 上级公司ID (bigint - 关联org.id，0表示顶级机构)
	MYSQL_SYNTHESIZE(uint64_t, pid, Pid);
	// 公司名称 (varchar(30) - 机构全称)
	MYSQL_SYNTHESIZE(string, name, Name);
	// 是否有效 (tinyint(1) - 1有效 0无效)
	MYSQL_SYNTHESIZE(int, state, State);
	// 公司简称 (varchar(100))
	MYSQL_SYNTHESIZE(string, shortname, Shortname);
	// 类型 (tinyint(4) - 机构类型标识)
	MYSQL_SYNTHESIZE(int, type, Type);
	// 级别 (tinyint(4) - 1集团总部 2分校 3部门)
	MYSQL_SYNTHESIZE(int, level, Level);
	// 路径 (varchar(255) - ID层级路径，如: 1,2,3,)
	MYSQL_SYNTHESIZE(string, idPath, IdPath);
	// 机构名路径 (varchar(255) - 名称层级路径，如: 集团/分校/部门)
	MYSQL_SYNTHESIZE(string, namePath, NamePath);
	// 联系人 (varchar(50))
	MYSQL_SYNTHESIZE(string, contactName, ContactName);
	// 联系电话 (varchar(20))
	MYSQL_SYNTHESIZE(string, phone, Phone);
	// 传真 (varchar(20))
	MYSQL_SYNTHESIZE(string, fax, Fax);
	// Email (varchar(50))
	MYSQL_SYNTHESIZE(string, email, Email);
	// 描述 (varchar(255) - 机构说明信息)
	MYSQL_SYNTHESIZE(string, info, Info);
	// 创建人 (bigint - 关联staff.id，存储用户ID)
	MYSQL_SYNTHESIZE(uint64_t, creator, Creator);
	// 编辑人 (bigint - 关联staff.id，存储用户ID)
	MYSQL_SYNTHESIZE(uint64_t, editor, Editor);
	// 添加时间 (datetime)
	MYSQL_SYNTHESIZE(string, addTime, AddTime);
	// 编辑时间 (datetime)
	MYSQL_SYNTHESIZE(string, editTime, EditTime);
	// 删除标记 (tinyint(1) - 0未删除 1已删除)
	MYSQL_SYNTHESIZE(int, deleted, Deleted);
	// 省 (int(11) - 关联region.id)
	MYSQL_SYNTHESIZE(int, province, Province);
	// 市 (int(11) - 关联region.id)
	MYSQL_SYNTHESIZE(int, city, City);
	// 区 (int(11) - 关联region.id)
	MYSQL_SYNTHESIZE(int, district, District);
	// 地址 (varchar(255) - 详细地址)
	MYSQL_SYNTHESIZE(string, address, Address);
	// 排序 (int(11) - 显示顺序)
	MYSQL_SYNTHESIZE(int, sortNum, SortNum);
	// 营业执照 (varchar(80))
	MYSQL_SYNTHESIZE(string, license, License);
public:
	OrgDO() : BaseDO("org")
	{
		MYSQL_ADD_FIELD_PK("id", "ull", id);
		MYSQL_ADD_FIELD("pid", "ull", pid);
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD("state", "i", state);
		MYSQL_ADD_FIELD("shortname", "s", shortname);
		MYSQL_ADD_FIELD("type", "i", type);
		MYSQL_ADD_FIELD("level", "i", level);
		MYSQL_ADD_FIELD("id_path", "s", idPath);
		MYSQL_ADD_FIELD("name_path", "s", namePath);
		MYSQL_ADD_FIELD("contact_name", "s", contactName);
		MYSQL_ADD_FIELD("phone", "s", phone);
		MYSQL_ADD_FIELD("fax", "s", fax);
		MYSQL_ADD_FIELD("email", "s", email);
		MYSQL_ADD_FIELD("info", "s", info);
		MYSQL_ADD_FIELD("creator", "ull", creator);
		MYSQL_ADD_FIELD("editor", "ull", editor);
		MYSQL_ADD_FIELD("add_time", "s", addTime);
		MYSQL_ADD_FIELD("edit_time", "s", editTime);
		MYSQL_ADD_FIELD("deleted", "i", deleted);
		MYSQL_ADD_FIELD("province", "i", province);
		MYSQL_ADD_FIELD("city", "i", city);
		MYSQL_ADD_FIELD("district", "i", district);
		MYSQL_ADD_FIELD("address", "s", address);
		MYSQL_ADD_FIELD("sort_num", "i", sortNum);
		MYSQL_ADD_FIELD("license", "s", license);
	}
};

// 给OrgDO智能指针设定一个别名方便使用
typedef std::shared_ptr<OrgDO> PtrOrgDO;
#endif // !_ORG_DO_
#pragma once
#include <cstdint>
#include "../DoInclude.h"

/**
 * 数据权限数据模型
 */
class PermissionDO : public BaseDO
{
	// 唯一表示, 64位无符号整形，雪花算法生成
	MYSQL_SYNTHESIZE(uint64_t, id, Id);
	// 职位id
	MYSQL_SYNTHESIZE(int64_t, positionid, PositionId);
	// 数据范围类型
	MYSQL_SYNTHESIZE(int8_t, scopeType, ScopeType);
	// 数据实体表
	MYSQL_SYNTHESIZE(std::string, entityName, EntityName);
	// 描述数据表单条记录所属者的字段
	MYSQL_SYNTHESIZE(std::string, ownerField, OwnerField);
	// 备注信息
	MYSQL_SYNTHESIZE(std::string, info, Info);
	// 描述数据表单条记录所属组织的字段
	MYSQL_SYNTHESIZE(std::string, ownerOrgField, OwnerOrgField);
public:
	PermissionDO()
		: BaseDO("data_permission")
	{
		MYSQL_ADD_FIELD_PK("id", "ull", id);
		MYSQL_ADD_FIELD_NULLABLE("position_id", "ll", positionid, false);
		MYSQL_ADD_FIELD("scope_type", "b", scopeType);
		MYSQL_ADD_FIELD_NULLABLE("entity_name", "s", entityName, false);
		MYSQL_ADD_FIELD_NULLABLE("owner_field", "s", ownerField, false);
		MYSQL_ADD_FIELD("info", "s", info);
		MYSQL_ADD_FIELD("owner_org_field", "s", ownerOrgField);
	}
};

// -01: 所有DO必须要用MYSQL_ADD_FIELD_PK设置主键，否则会在BaseDO的函数调用处报错
// -02:更改代码一处地方就一定要想好这个更改会牵连哪里，上面scopetype是tinyint但是实际在注册却注册成string直接报错

// 定义一个智能指针别名方便使用
typedef std::shared_ptr<PermissionDO> PtrPermissionDO;
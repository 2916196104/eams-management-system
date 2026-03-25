#pragma once

#ifndef _POSITIONDTODATA_H_
#define _POSITIONDTODATA_H_

#include "../../GlobalInclude.h"
#include "PermissionDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
	职位数据权限数据传输对象
 */
class PositionDataDTO : public oatpp::DTO 
{
	//ownerField, ownerOrgField要和数据实体表中字段相对应；orgIds配合scopeType来进行查询条件构建，比如只允许查询部门id为[10, 20, 30]这些的数据
	DTO_INIT(PositionDataDTO, DTO);
	API_DTO_FIELD_REQUIRE(String, entityName, ZH_WORDS_GETTER("datapermission.psdto.ename"), true);
	API_DTO_FIELD_REQUIRE(UInt64, id, ZH_WORDS_GETTER("datapermission.psdto.id"), false); //更新权限记录时需要提供，新增是不需要提供
	API_DTO_FIELD_REQUIRE(String, info, ZH_WORDS_GETTER("datapermission.psdto.info"), false);
	API_DTO_FIELD_REQUIRE(Vector<Int64>, orgIds, ZH_WORDS_GETTER("datapermission.psdto.orgids"), false);
	API_DTO_FIELD_REQUIRE(String, ownerField, ZH_WORDS_GETTER("datapermission.psdto.ownerfield"), false);
	API_DTO_FIELD_REQUIRE(String, ownerOrgField, ZH_WORDS_GETTER("datapermission.psdto.ownerorgfield"), false);
	API_DTO_FIELD_REQUIRE(Int64, position_Id, ZH_WORDS_GETTER("datapermission.psdto.positionid"), true);
	API_DTO_FIELD_REQUIRE(Int8, scopeType, ZH_WORDS_GETTER("datapermission.psdto.scopetype"), false);
	//DTO_FIELD(Int32, id);               // 职位ID
	DTO_FIELD(String, name);             // 职位名称
	DTO_FIELD(Vector<oatpp::Object<PermissionDTO>>, permissions);  // 权限列表
};

#include OATPP_CODEGEN_END(DTO)
#endif // _POSITIONDTODATA_H_
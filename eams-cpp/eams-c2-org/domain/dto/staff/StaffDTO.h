#pragma once

#ifndef _STAFFDTO_H_
#define _STAFFDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
	员工数据传输对象
 */
class StaffDTO : public oatpp::DTO {
  DTO_INIT(StaffDTO, DTO);
};
class   StaffChangePasswordDTO :public oatpp::DTO {
	DTO_INIT(StaffChangePasswordDTO, DTO);
	API_DTO_FIELD_REQUIRE(Int64, id, ZH_WORDS_GETTER("staff.field.id"),true);
	API_DTO_FIELD_REQUIRE(String, password, ZH_WORDS_GETTER("staff.field.new-password"),true);

};

class StaffExportQueryDto :public oatpp::DTO {
	DTO_INIT(StaffExportQueryDto, DTO);
	DTO_FIELD(Boolean, exportFlag, "export");
	DTO_FIELD_INFO(exportFlag) {
		info->required = true;
		info->description = ZH_WORDS_GETTER("staff.export-list.export");
	}
	//API_DTO_FIELD_REQUIRE(Boolean, exportFlag, ZH_WORDS_GETTER("staff.export-list.export"), true);
	API_DTO_FIELD_DEFAULT(String, keyword, ZH_WORDS_GETTER("staff.export-list.keyword"));
	API_DTO_FIELD_DEFAULT(String, state, ZH_WORDS_GETTER("staff.field.state"));
	
};
#include OATPP_CODEGEN_END(DTO)
#endif // _STAFFDTO_H_

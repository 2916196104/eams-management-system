#pragma once
#ifndef ENROLLMENTDTO_H
#define ENROLLMENTDTO_H
#include"../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)
/*
* 报名数据传输对象
*/
 class EnrollmentDTO : public oatpp::DTO {

	 DTO_INIT(EnrollmentDTO, DTO);
	 DTO_FIELD(String, name);
	 DTO_FIELD_INFO(name) {
		 info->description = ZH_WORDS_GETTER("sample.field.id");
	 }
};
 /*
 * 保存报名数据传输对象
 */
 class EnrollmentSaveDTO : public EnrollmentDTO
 {
	 DTO_INIT(EnrollmentSaveDTO, EnrollmentDTO);
 };
#include OATPP_CODEGEN_END(DTO)
#endif // ENROLLMENTDTO_H
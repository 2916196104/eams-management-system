#pragma once
#ifndef _FINISH_STUDENT_VO_H_
#define _FINISH_STUDENT_VO_H_

#include "domain/GlobalInclude.h"
#include "domain/vo/JsonVO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 结业学员导入结果对象
 */
//class FinishStudentImportResultVO : public oatpp::DTO
//{
//	DTO_INIT(FinishStudentImportResultVO, DTO);
//
//	API_DTO_FIELD_DEFAULT(Int32, totalCount, ZH_WORDS_GETTER("finishstudent.field.total-count"));
//	API_DTO_FIELD_DEFAULT(Int32, successCount, ZH_WORDS_GETTER("finishstudent.field.success-count"));
//	API_DTO_FIELD_DEFAULT(Int32, failCount, ZH_WORDS_GETTER("finishstudent.field.failed-count"));
//	/*DTO_FIELD(List<String>, failMessages) = {};
//	DTO_FIELD_INFO(failMessages) {
//		info->description = ZH_WORDS_GETTER("finish_student.import.failMessages");
//	}*/
//};
//
///**
// * 结业学员导入结果响应对象
// */
//class FinishStudentImportResultJsonVO : public JsonVO<FinishStudentImportResultVO::Wrapper>
//{
//	DTO_INIT(FinishStudentImportResultJsonVO, JsonVO<FinishStudentImportResultVO::Wrapper>);
//};
#include OATPP_CODEGEN_END(DTO)

#endif // !_FINISH_STUDENT_VO_H_

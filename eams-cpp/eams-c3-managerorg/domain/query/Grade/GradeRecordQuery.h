#pragma once
#ifndef __GRADE_RECORD_QUERY_H__
#define __GRADE_RECORD_QUERY_H__

#include "domain/GlobalInclude.h"
#include "domain/query/PageQuery.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 成绩记录表查询：筛选 + 分页（筛选字段均为非必传）
 */
class GradeRecordQuery : public PageQuery
{
	DTO_INIT(GradeRecordQuery, PageQuery);

	API_DTO_FIELD_DEFAULT(UInt64, gradeId, ZH_WORDS_GETTER("GradeRecordDTO.gradeId"));
	API_DTO_FIELD_DEFAULT(UInt64, studentId, ZH_WORDS_GETTER("GradeRecordDTO.studentId"));
	API_DTO_FIELD_DEFAULT(Int32, score, ZH_WORDS_GETTER("GradeRecordDTO.score"));
	API_DTO_FIELD_DEFAULT(UInt64, creator, ZH_WORDS_GETTER("GradeRecordDTO.creator"));
	API_DTO_FIELD_DEFAULT(String, startAddTime, ZH_WORDS_GETTER("GradeRecordDTO.startAddTime"));
	API_DTO_FIELD_DEFAULT(String, endAddTime, ZH_WORDS_GETTER("GradeRecordDTO.endAddTime"));
};

#include OATPP_CODEGEN_END(DTO)

#endif

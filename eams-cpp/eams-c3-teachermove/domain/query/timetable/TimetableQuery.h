#ifndef __TIMETABLE_QUERY_H__
#define __TIMETABLE_QUERY_H__

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/* Timetable query parameters */
class TimetableQuery : public oatpp::DTO
{
	DTO_INIT(TimetableQuery, DTO)
};

// --- 1. Query parameters for getting student list ---
// Inherits from base PageQuery, which provides pageIndex and pageSize fields.
class StuListQuery : public PageQuery {
	DTO_INIT(StuListQuery, PageQuery)

		API_DTO_FIELD(String, keyword, ZH_WORDS_GETTER("timetable.query.keyword"), false, "")
};

// --- 2. Query parameters for getting student class list ---
class StuClassQuery : public oatpp::DTO {
	DTO_INIT(StuClassQuery, DTO)

		API_DTO_FIELD(String, id, ZH_WORDS_GETTER("timetable.dto.TimetableStudentDTO.studentID"), true, "10001")
};

#include OATPP_CODEGEN_END(DTO)

#endif
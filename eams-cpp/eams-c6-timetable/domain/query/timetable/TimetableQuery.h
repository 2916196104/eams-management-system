#pragma once
#ifndef TIMETABLE_QUERY_H
#define TIMETABLE_QUERY_H
#include "../../GlobalInclude.h"
#include "../../../../lib-oatpp/include/domain/query/PageQuery.h"
#include OATPP_CODEGEN_BEGIN(DTO)
/**
 * 课表分页查询（按日期）
 */
class TimetableQuery : public PageQuery
{
    // 查询日期（必传）
    API_DTO_FIELD(String, queryDate, ZH_WORDS_GETTER("filed.timetable.querydate"), true, "")
      


};
#include OATPP_CODEGEN_END(DTO)
#endif // TIMETABLE_QUERY_H



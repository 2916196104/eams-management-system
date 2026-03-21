#pragma once
#ifndef TIMETABLE_QUERY_H
#define TIMETABLE_QUERY_H
#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)
/**
 * 进入课表页面时，默认查询当天的课表数据，用户也可以选择其他日期进行查询。
 * 不是分页查询，不继承pageQuery，后续如果需要分页查询，可以再添加分页参数
 */
class TimetableQuery : public oatpp::DTO
{
    DTO_INIT(TimetableQuery, DTO);

    // 查询日期
    API_DTO_FIELD(String, queryDate, ZH_WORDS_GETTER("timetable.field.query.query-date"), true, "");
};

#include OATPP_CODEGEN_END(DTO)
#endif // TIMETABLE_QUERY_H



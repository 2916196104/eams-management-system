#pragma once
#ifndef TIMETABLE_QUERY_H
#define TIMETABLE_QUERY_H

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 课表按天查询对象
 * 用户进入课表页面时，默认查询当天课表
 * 用户点击当前月历中的某一天时，查询该天的课程信息
 * 该查询不是分页查询，因为一天的课表数据量通常较小
 * queryDate 格式建议为yyyy-MM-dd
 */
class TimetableDayQuery : public oatpp::DTO
{
    DTO_INIT(TimetableDayQuery, DTO);

    // 查询日期
    API_DTO_FIELD(String, queryDate, ZH_WORDS_GETTER("timetable.field.query.query-date"), true, "");
};


/**
 * 课表按月查询对象
 * 用户点击“上个月”或“下个月”时，查询指定月份哪些日期有课
 * 用于月历区域的小圆点提示
 * 这查询同样不是分页查询，因为一个月最多涉及31天的数据标记
 * year表示年份，例如2026
 * month表示月份，取值范围是[1,12]
 * 这个查询不返回当天详细课表，而是返回 有课日期列表
 */
class TimetableMonthQuery : public oatpp::DTO
{
    DTO_INIT(TimetableMonthQuery, DTO);

    // 查询年份
    API_DTO_FIELD(Int32, year, ZH_WORDS_GETTER("timetable.field.query.year"), true, 0);
    // 查询月份
    API_DTO_FIELD(Int32, month, ZH_WORDS_GETTER("timetable.field.query.month"), true, 0);
};

#include OATPP_CODEGEN_END(DTO)

#endif // TIMETABLE_QUERY_H

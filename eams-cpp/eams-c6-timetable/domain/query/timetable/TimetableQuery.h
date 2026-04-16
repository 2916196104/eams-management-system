#pragma once
#ifndef TIMETABLE_QUERY_H
#define TIMETABLE_QUERY_H

#include "../../GlobalInclude.h"
#include <regex>

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 课表按天查询对象
 * 用户进入课表页面时，默认查询当天课表
 * 用户点击当前月历中的某一天时，查询该天的课程信息
 * 该查询不是分页查询，因为一天的课表数据量通常较小
 */
class TimetableDayQuery : public oatpp::DTO
{
    DTO_INIT(TimetableDayQuery, DTO);

    API_DTO_FIELD(String, queryDate, ZH_WORDS_GETTER("timetable.field.query.query-date"), true, "");
    API_DTO_FIELD_REQUIRE(String, studentId, ZH_WORDS_GETTER("timetable.field.query.student-id"), true);
    API_DTO_FIELD(Boolean, includeReservable, ZH_WORDS_GETTER("timetable.field.query.include-reservable"), false, true);

public:
    std::string validate()
    {
        if (!queryDate || queryDate->empty())
        {
            return "queryDate cannot be empty.";
        }
        if (!studentId || studentId->empty())
        {
            return "studentId cannot be empty.";
        }

        static const std::regex datePattern("^\\d{4}-\\d{2}-\\d{2}$");
        std::string queryDateStr = queryDate.getValue("");
        if (!std::regex_match(queryDateStr, datePattern))
        {
            return "queryDate format must be yyyy-MM-dd.";
        }

        return "";
    }
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

    API_DTO_FIELD(Int32, year, ZH_WORDS_GETTER("timetable.field.query.year"), true, 0);
    API_DTO_FIELD(Int32, month, ZH_WORDS_GETTER("timetable.field.query.month"), true, 0);
    API_DTO_FIELD_DEFAULT(String, studentId, ZH_WORDS_GETTER("timetable.field.query.student-id"));

public:
    std::string validate()
    {
        if (!year || year <= 0)
        {
            return "year invalidate.";
        }
        if (!month || month < 1 || month > 12)
        {
            return "month invalidate.";
        }
        if (!studentId || studentId->empty())
        {
            return "studentId cannot be empty.";
        }
        return "";
    }
};

#include OATPP_CODEGEN_END(DTO)

#endif // TIMETABLE_QUERY_H

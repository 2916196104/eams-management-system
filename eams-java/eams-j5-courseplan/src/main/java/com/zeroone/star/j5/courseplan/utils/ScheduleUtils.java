package com.zeroone.star.j5.courseplan.utils;

import java.time.LocalDate;
import java.util.HashSet;
import java.util.Set;



/*
 * 工具类：计算天数 (ScheduleUtils.java)
 **/
public class ScheduleUtils {
    /**
     * 计算在指定日期范围内，符合指定星期字符串的天数总和
     * @param startDate 开始日期 (包含)
     * @param endDate 结束日期 (包含)
     * @param weeksStr 星期字符串，格式如 "1", "1,3,5" (1=周一, 7=周日)
     * @return 总天数 (即排课次数)
     */
    /**
     * 计算【单条规则】在指定日期范围内产生的课次
     * 例如：规则是"每周一"，范围是3月1日-3月31日 -> 返回 5
     */
    public static int calculateRuleOccurrences(LocalDate startDate, LocalDate endDate, String weeksStr) {
        if (startDate == null || endDate == null || startDate.isAfter(endDate)) {
            return 0;
        }
        if (weeksStr == null || weeksStr.trim().isEmpty()) {
            return 0;
        }

        Set<Integer> targetWeeks = new HashSet<>();
        for (String s : weeksStr.split(",")) {
            try {
                int w = Integer.parseInt(s.trim());
                if (w >= 1 && w <= 7) targetWeeks.add(w);
            } catch (NumberFormatException ignored) {}
        }

        if (targetWeeks.isEmpty()) return 0;

        int count = 0;
        LocalDate current = startDate;
        while (!current.isAfter(endDate)) {
            if (targetWeeks.contains(current.getDayOfWeek().getValue())) {
                count++;
            }
            current = current.plusDays(1);
        }
        return count;
    }
}

package com.zeroone.star.j5.courseplan.service;

/**
 * 单个排课计划独立事务处理服务接口
 */
public interface ICoursePlanSingleService {
    /**
     * 生成单个排课计划的课表
     * * @param scheduleId 排课计划ID
     * @param excludeHoliday 是否排除节假日
     * @param overwrite 是否覆盖已生成课表
     * @return 成功生成的课次数量
     */
    int generateSingleSchedule(Long scheduleId, Boolean excludeHoliday, Boolean overwrite);
}
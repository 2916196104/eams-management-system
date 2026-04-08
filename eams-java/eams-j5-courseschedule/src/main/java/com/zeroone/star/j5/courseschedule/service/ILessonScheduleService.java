package com.zeroone.star.j5.courseschedule.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.dto.j5.courseschedule.CourseAppointStatusDTO;
import com.zeroone.star.project.dto.j5.courseschedule.CourseScheduleDTO;
import com.zeroone.star.project.vo.JsonVO;

public interface ILessonScheduleService extends IService<CourseScheduleDTO> {
    /**
     * 重排课次
     *
     * @param courseScheduleVO 重排课次参数
     * @return 重排课次结果
     */


    JsonVO<String> reapteSchedule(CourseScheduleDTO courseScheduleVO);

    JsonVO<String> freeSchedule(CourseScheduleDTO courseScheduleVO);

    JsonVO<String> switchSchedule(CourseAppointStatusDTO courseAppointStatusDto);
}

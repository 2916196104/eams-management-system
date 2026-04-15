package com.zeroone.star.j5.courseschedule.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.j5.courseschedule.annotation.AutoFill;
import com.zeroone.star.project.dto.j5.courseschedule.CourseAppointStatusDTO;
import com.zeroone.star.project.dto.j5.courseschedule.CourseScheduleDTO;
import com.zeroone.star.project.enums.OperationType;
import com.zeroone.star.project.vo.j5.courseschedule.CourseScheduleSettingVO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Update;


import java.util.List;

@Mapper
public interface LessonScheduleMapper extends BaseMapper<CourseScheduleDTO> {




    void insertBatch(List<CourseScheduleSettingVO> list);



    @AutoFill(OperationType.INSERT)
    void reapteSchedule(CourseScheduleDTO courseScheduleDto);

    @AutoFill(OperationType.UPDATE)
    @Update("update lesson_schedule set state = #{status} where id = #{id}")
    void switchSchedule(CourseAppointStatusDTO courseAppointStatusDto);
    /**
     * 重排课次
     *
     * @param courseScheduleVO 重排课次参数
     * @return 重排课次结果
     */

}

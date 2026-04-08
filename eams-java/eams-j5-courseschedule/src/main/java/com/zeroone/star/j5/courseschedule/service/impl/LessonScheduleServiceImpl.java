package com.zeroone.star.j5.courseschedule.service.impl;

import cn.hutool.core.bean.BeanUtil;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.j5.courseschedule.mapper.LessonScheduleMapper;

import com.zeroone.star.j5.courseschedule.service.ILessonScheduleService;
import com.zeroone.star.project.dto.j5.courseschedule.CourseAppointStatusDTO;
import com.zeroone.star.project.dto.j5.courseschedule.CourseScheduleDTO;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j5.courseschedule.CourseScheduleSettingVO;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
@RequiredArgsConstructor

public class LessonScheduleServiceImpl extends ServiceImpl<LessonScheduleMapper, CourseScheduleDTO> implements ILessonScheduleService {
    private final LessonScheduleMapper lessonScheduleMapper;

    @Override
    public JsonVO<String> reapteSchedule(CourseScheduleDTO courseScheduleDto) {
        List<CourseScheduleSettingVO> courseScheduleSettingVOList = BeanUtil.copyToList(courseScheduleDto.getLessonScheduleSettingDtos() ,

                CourseScheduleSettingVO.class);

        for (CourseScheduleSettingVO courseScheduleSettingVO : courseScheduleSettingVOList) {
            courseScheduleSettingVO.setScheduleId(courseScheduleDto.getId());
        }
        lessonScheduleMapper.reapteSchedule(courseScheduleDto);
        lessonScheduleMapper.insertBatch(courseScheduleSettingVOList);
        return JsonVO.success("重复课次成功");

    }

    @Override
    public JsonVO<String> freeSchedule(CourseScheduleDTO courseScheduleVO) {
        lessonScheduleMapper.reapteSchedule(courseScheduleVO);
        return JsonVO.success("释放课次成功");
    }

    @Override
    public JsonVO<String> switchSchedule(CourseAppointStatusDTO courseAppointStatusDto) {
        lessonScheduleMapper.switchSchedule(courseAppointStatusDto);
        return JsonVO.success("切换课次成功");
    }
}


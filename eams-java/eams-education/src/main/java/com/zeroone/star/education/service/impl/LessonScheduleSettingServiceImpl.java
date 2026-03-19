package com.zeroone.star.education.service.impl;

import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.education.entity.LessonSchedule;
import com.zeroone.star.education.entity.LessonScheduleSetting;
import com.zeroone.star.education.mapper.LessonScheduleSettingMapper;
import com.zeroone.star.education.service.LessonScheduleSettingService;
import org.springframework.stereotype.Service;

@Service
public class LessonScheduleSettingServiceImpl extends ServiceImpl<LessonScheduleSettingMapper, LessonScheduleSetting> implements LessonScheduleSettingService {
}

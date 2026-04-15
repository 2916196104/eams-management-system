package com.zeroone.star.student.service.impl;

import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.student.entity.CourseDO;
import com.zeroone.star.student.mapper.CourseMapper;
import com.zeroone.star.student.service.ICourseService;
import org.springframework.stereotype.Service;

@Service
public class CourseServiceImpl extends ServiceImpl<CourseMapper, CourseDO> implements  ICourseService{
}

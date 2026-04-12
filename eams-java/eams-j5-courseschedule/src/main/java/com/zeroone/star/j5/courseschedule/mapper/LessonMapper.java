package com.zeroone.star.j5.courseschedule.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.*;
import com.zeroone.star.j5.courseschedule.entity.Lesson;
import com.zeroone.star.project.DO.j5.courseschedule.LessonDo;
import com.zeroone.star.project.dto.j5.courseschedule.LessonParamDTO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;

@Mapper
public interface LessonMapper extends BaseMapper<LessonDo> {

}

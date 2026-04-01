package com.zeroone.star.project.j1.orgmanager.mapper.staff;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.project.DO.Lesson;
import org.apache.ibatis.annotations.Mapper;

/**
* @author linjianyu
* @description 针对表【lesson(课程表)】的数据库操作Mapper
* @createDate 2026-03-25 20:42:03
* @Entity com.zeroone.star.project.DO.Lesson
*/
@Mapper
public interface LessonMapper extends BaseMapper<Lesson> {

    /**
     * 查询授课记录
     */
   // List<LessonRecordDTO> selectLessonRecordList(@Param("teacherId") Long teacherId);
}






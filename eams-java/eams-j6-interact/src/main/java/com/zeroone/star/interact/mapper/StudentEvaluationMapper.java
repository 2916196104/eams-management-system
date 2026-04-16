package com.zeroone.star.interact.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dataobject.j6.interact.LessonStudentDO;
import com.zeroone.star.project.dto.j6.interact.StudentEvaluationDTO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

import java.time.LocalDate;

@Mapper
public interface StudentEvaluationMapper extends BaseMapper<LessonStudentDO> {

    IPage<StudentEvaluationDTO> queryPage(Page<StudentEvaluationDTO> page,
                                          @Param("evaluation") String evaluation,
                                          @Param("lessonId") Long lessonId,
                                          @Param("teacherId") Long teacherId,
                                          @Param("studentId") Long studentId,
                                          @Param("startTime") LocalDate startTime,
                                          @Param("endTime") LocalDate endTime);
}

package com.zeroone.star.student.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.student.entity.ClassStudentDO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;

/**
 * 班级学员关系 Mapper
 */
@Mapper
public interface ClassStudentMapper extends BaseMapper<ClassStudentDO> {

    /**
     * 检查学员是否已在班级中
     */
    @Select("SELECT COUNT(*) FROM class_student WHERE class_id = #{classId} AND student_id = #{studentId} AND deleted = 0")
    int countByClassAndStudent(@Param("classId") Long classId, @Param("studentId") Long studentId);

    /**
     * 统计班级当前学员数
     */
    @Select("SELECT COUNT(*) FROM class_student WHERE class_id = #{classId} AND deleted = 0")
    int countByClassId(@Param("classId") Long classId);
}
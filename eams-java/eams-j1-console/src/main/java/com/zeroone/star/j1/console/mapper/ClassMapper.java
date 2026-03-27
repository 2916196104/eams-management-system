package com.zeroone.star.j1.console.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.j1.console.entity.ClassDO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;

/**
 * <p>
 * 班级表 Mapper 接口
 * </p>
 * @author hxb
 */
@Mapper
public interface ClassMapper extends BaseMapper<ClassDO> {

    /**
     * 统计班级总数
     * @return 班级总数
     */
    @Select("SELECT COUNT(*) FROM class WHERE deleted = 0")
    Integer countTotalClasses();

    /**
     * 根据ID获取班级名称
     * @param id 班级ID
     * @return 班级名称
     */
    @Select("SELECT name FROM class WHERE id = #{id} AND deleted = 0")
    String getNameById(Long id);

    /**
     * 获取班级剩余名额
     * @param classId 班级ID
     * @return 剩余名额
     */
    @Select("SELECT c.planned_student_count - (SELECT COUNT(*) FROM class_student WHERE class_id = #{classId} AND deleted = 0) FROM class c WHERE c.id = #{classId} AND c.deleted = 0")
    Integer getRemainingSeats(@Param("classId") Long classId);
}

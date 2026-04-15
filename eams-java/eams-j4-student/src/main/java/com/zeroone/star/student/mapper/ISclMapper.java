package com.zeroone.star.student.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.student.entity.StudentCreditLog;
import org.apache.ibatis.annotations.*;

import java.util.List;

@Mapper
public interface ISclMapper extends BaseMapper<StudentCreditLog> {
    @Select("select id from student where name = #{stuName}")
    String SelectIdByName(@Param("stuName")String stuName);

    @Select("select credit from student where id = #{id}")
    Integer SelectCreditById(@Param("id") String student_id);

    @Update("UPDATE student SET credit = #{current_credit} WHERE id = #{id}")
    int UpdateCreditById(@Param("current_credit") int current_credit, @Param("id") int id);
}

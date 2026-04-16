package com.zeroone.star.course.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.course.entity.SubjectDO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;

/**
 * 学科 Mapper（只读）
 * @author yangxiao
 */
@Mapper
public interface SubjectMapper extends BaseMapper<SubjectDO> {

    @Select("select name from subject where id = #{subjectId}")
    String selectNameById(Long subjectId);
}

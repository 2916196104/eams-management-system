package com.zeroone.star.j1.console.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.j1.console.entity.LessonDO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;

/**
 * <p>
 * 课次表 Mapper 接口
 * </p>
 * @author hxb
 */
@Mapper
public interface LessonMapper extends BaseMapper<LessonDO> {

    /**
     * 统计总课次
     * @return 总课次数
     */
    @Select("SELECT COUNT(*) FROM lesson WHERE deleted = 0")
    Integer countTotalLessons();
}

package com.zeroone.star.j1.console.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.j1.console.entity.ClassroomDO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;

/**
 * <p>
 * 教室表 Mapper 接口
 * </p>
 * @author hxb
 */
@Mapper
public interface ClassroomMapper extends BaseMapper<ClassroomDO> {

    /**
     * 根据ID获取教室名称
     * @param id 教室ID
     * @return 教室名称
     */
    @Select("SELECT name FROM classroom WHERE id = #{id} AND deleted = 0")
    String getNameById(Long id);
}

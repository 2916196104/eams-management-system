package com.zeroone.star.j1.console.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.j1.console.entity.StaffDO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;

/**
 * <p>
 * 教师员工表 Mapper 接口
 * </p>
 * @author hxb
 */
@Mapper
public interface StaffMapper extends BaseMapper<StaffDO> {

    /**
     * 统计教师总数
     * @return 教师总数
     */
    @Select("SELECT COUNT(*) FROM staff WHERE deleted = 0 AND state = 1")
    Integer countTotalTeachers();

    /**
     * 根据ID获取教师姓名
     * @param id 教师ID
     * @return 教师姓名
     */
    @Select("SELECT name FROM staff WHERE id = #{id} AND deleted = 0")
    String getNameById(Long id);
}

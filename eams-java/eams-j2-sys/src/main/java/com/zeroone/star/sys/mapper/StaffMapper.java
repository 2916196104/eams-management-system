package com.zeroone.star.sys.mapper;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.j2.sys.Optlog.OptlogOperatorDTO;
import com.zeroone.star.sys.entity.Staff;
import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

/**
 * <p>
 * 教师员工表 Mapper 接口
 * </p>
 *
 * @author isme
 * @since 2026-03-22
 */
@Mapper
public interface StaffMapper extends BaseMapper<Staff> {

    Page<OptlogOperatorDTO> selectOptlogOperators(Page<?> page, @Param("name") String name);
}

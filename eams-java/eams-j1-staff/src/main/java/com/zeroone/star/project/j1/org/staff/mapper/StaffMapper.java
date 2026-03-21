package com.zeroone.star.project.j1.org.staff.mapper;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.project.dto.j1.org.StaffDTO;
import com.zeroone.star.project.query.j1.org.StaffQuery;
import org.apache.ibatis.annotations.Mapper;

@Mapper
public interface StaffMapper extends BaseMapper<StaffDTO> {
    // 实现void queryPage(StaffQuery condition)
    // 注意：PageHelper分页是“拦截下一次查询”，所以方法内先启动分页，再执行查询
    default void queryPage(StaffQuery condition) {

        // 2. 构造MP查询条件（Wrapper）
        LambdaQueryWrapper<StaffDTO> queryWrapper = new LambdaQueryWrapper<>();
        // 动态拼接业务条件（非空才拼接）
        if (condition.getName() != null && !condition.getName().isEmpty()) {
            queryWrapper.like(StaffDTO::getName, condition.getName());
        }
        if (condition.getId() != null) {
            queryWrapper.eq(StaffDTO::getId, condition.getId());
        }

        // 3. 执行查询（PageHelper会自动拦截这个查询，实现分页）
        // 因为方法返回值是void，这里直接执行查询即可（如需返回分页结果，可改为返回PageInfo）
        this.selectList(queryWrapper);
    }
}

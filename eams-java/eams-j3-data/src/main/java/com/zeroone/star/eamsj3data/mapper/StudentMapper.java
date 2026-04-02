package com.zeroone.star.eamsj3data.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.github.yulichang.base.MPJBaseMapper;
import com.zeroone.star.eamsj3data.entity.Student;
import org.apache.ibatis.annotations.Mapper;

/**
 * <p>
 * 学员 Mapper 接口
 * </p>
 * @author yeyue
 * @version 1.0.0
 */
@Mapper
public interface StudentMapper extends MPJBaseMapper<Student> {
}

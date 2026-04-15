package com.zeroone.star.student.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.student.entity.Refund;
import org.apache.ibatis.annotations.Mapper;

/**
 * <p>
 * 描述：线下退费单数据访问接口
 * </p>
 */
@Mapper
public interface RefundMapper extends BaseMapper<Refund> {
}

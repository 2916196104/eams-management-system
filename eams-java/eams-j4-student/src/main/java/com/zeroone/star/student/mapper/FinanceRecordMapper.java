package com.zeroone.star.student.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.student.entity.FinanceRecord;
import org.apache.ibatis.annotations.Mapper;

/**
 * <p>
 * 描述：财务流水数据访问接口
 * </p>
 */
@Mapper
public interface FinanceRecordMapper extends BaseMapper<FinanceRecord> {
}

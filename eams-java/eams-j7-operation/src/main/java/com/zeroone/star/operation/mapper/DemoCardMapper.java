package com.zeroone.star.operation.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.operation.entity.CourseTrialRecord;
import com.zeroone.star.project.dto.j7.operation.DemoCardDTO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

/**
 * <p>
 * 试听卡Mapper接口
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-22
 */
@Mapper
public interface DemoCardMapper extends BaseMapper<CourseTrialRecord> {
    
    /**
     * 保存试听卡
     */
    int insertDemoCard(@Param("dto") DemoCardDTO dto);
}

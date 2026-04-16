package com.zeroone.star.operation.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.query.j7.operation.TrialRecordQuery;
import com.zeroone.star.project.vo.j7.operation.TrialRecordVO;
import com.zeroone.star.operation.entity.CourseTrialRecord;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

/**
 * <p>
 * 课程体验卡领取记录 Mapper 接口
 * </p>
 *
 * @author zht
 * @since 2026-03-13
 */
@Mapper
public interface CourseTrialRecordMapper extends BaseMapper<CourseTrialRecord> {
    // 自定义联表分页查询领取记录
    Page<TrialRecordVO> selectRecordPage(@Param("page") Page<TrialRecordVO> page, @Param("query") TrialRecordQuery query);
}

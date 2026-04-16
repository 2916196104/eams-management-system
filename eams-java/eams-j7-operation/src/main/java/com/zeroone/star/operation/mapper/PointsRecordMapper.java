package com.zeroone.star.operation.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.project.dto.j7.operation.PointsRecordUpdateDTO;
import com.zeroone.star.project.entity.StudentCreditLog;
import com.zeroone.star.project.dto.j7.operation.PointsRecordDTO;
import com.zeroone.star.project.query.j7.operation.PointsRecordQuery;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

import java.util.List;

@Mapper
public interface PointsRecordMapper extends BaseMapper<StudentCreditLog> {
    /**
     * 分页查询积分记录
     */
    List<PointsRecordDTO> selectPointsRecordList(@Param("query") PointsRecordQuery query,
                                               @Param("offset") int offset,
                                               @Param("pageSize") int pageSize);

    /**
     * 查询积分记录总数
     */
    int countPointsRecord(@Param("query") PointsRecordQuery query);

    /**
     * 更新积分记录
     */
    int updatePointsRecord(@Param("entity") PointsRecordUpdateDTO entity);


}

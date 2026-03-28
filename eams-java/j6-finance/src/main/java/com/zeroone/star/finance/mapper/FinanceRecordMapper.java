package com.zeroone.star.finance.mapper;


import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.query.j6.finance.FinanceRecordQuery;
import com.zeroone.star.project.vo.j6.finance.FinanceRecordVO;
import feign.Param;
import org.apache.ibatis.annotations.Mapper;

import java.util.List;

@Mapper
public interface FinanceRecordMapper {
    /**
     * 分页查询款项列表 VO
     * @param page 分页对象
     * @param condition 查询条件
     * @return 分页结果
     */
    IPage<FinanceRecordVO> selectPageVO(Page<FinanceRecordVO> page, @Param("condition") FinanceRecordQuery condition);

    /**
    * 批量确认款项
    * @param ids 款项ID列表
    * @return 影响行数
    */
    int batchConfirm(@Param("ids") List<Long> ids);

    /**
     * 批量拒绝款项
     * @param ids 款项ID列表
     * @return 影响行数
     */
    int batchRefuse(@Param("ids") List<Long> ids);
}

package com.zeroone.star.finance.mapper;

import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.j6.finance.FinanceRecordDTO;
import com.zeroone.star.project.query.j6.finance.FinanceRecordQuery;
import com.zeroone.star.project.vo.j6.finance.FinanceRecordVO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

import java.util.List;

/**
 * 款项管理Mapper
 */
@Mapper
public interface FundManageMapper {

    /**
     * 分页查询款项列表
     * @param page 分页对象
     * @param condition 查询条件
     * @return 分页结果
     */
    IPage<FinanceRecordDTO> selectPageDTO(Page<FinanceRecordDTO> page, @Param("condition") FinanceRecordQuery condition);

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

    /**
     * 查询所有款项（用于导出）
     * @return 款项列表
     */
    List<FinanceRecordVO> findAll();
}

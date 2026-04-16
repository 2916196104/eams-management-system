package com.zeroone.star.operation.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.j7.operation.CreditMallDTO;
import com.zeroone.star.project.dto.j7.operation.CreditMallDetailDTO;
import com.zeroone.star.operation.entity.CreditMall;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;

import java.util.List;

/**
 * 积分商城礼品数据访问层
 */
@Mapper
public interface CreditMallMapper extends BaseMapper<CreditMall> {

    // 根据 ID 查询详情（含关联表字段）
    CreditMallDetailDTO selectDetailById(@Param("id") String id);

    //查询列表
    IPage<CreditMallDTO> selectCreditMallDTOPage(Page<CreditMallDTO> page, String name, Integer state);

    @Select("SELECT count(1) FROM material WHERE id = #{materialId}")
    int countMaterialExists(Long materialId);

    @Select("SELECT count(1) FROM material WHERE category_id = #{categoryId}")
    int countCategoryExists(Long categoryId);
    /**
     * 根据ID列表删除礼品（逻辑删除）
     * @param ids 礼品ID列表
     */
    void deleteByIdList(@Param("ids") List<Long> ids);

    /**
     * 根据ID列表更新礼品状态
     * @param ids 礼品ID列表
     * @param status 状态值（1:启用, 0:禁用）
     */
    void updateStatusByIdList(@Param("ids") List<Long> ids, @Param("status") Integer status);
}

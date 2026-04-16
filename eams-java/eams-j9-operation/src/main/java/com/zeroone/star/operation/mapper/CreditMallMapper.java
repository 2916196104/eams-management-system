package com.zeroone.star.operation.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.operation.entity.CreditMallDO;
import com.zeroone.star.project.query.j9.operation.CreditMallPageQuery;
import com.zeroone.star.project.vo.j9.operation.CreditMallPageVO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Update;

/**
 * 积分商城礼品 Mapper 接口
 */
@Mapper
public interface CreditMallMapper extends BaseMapper<CreditMallDO> {

    /**
     * 增加礼品库存
     * @param id 礼品ID
     * @param num 增加数量
     * @return 影响行数
     */
    @Update("UPDATE credit_mall SET stock = stock + #{num} WHERE id = #{id}")
    int incrementStock(@Param("id") Long id, @Param("num") Integer num);

    /**
     * 分页查询礼品列表（关联org表查询学校名称）
     * @param page 分页对象（MyBatisPlus分页）
     * @param query 查询参数
     * @return 分页结果
     */
    IPage<CreditMallPageVO> pageQueryWithSchoolName(Page<CreditMallPageVO> page,
                                                    @Param("query") CreditMallPageQuery query);
}

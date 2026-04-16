package com.zeroone.star.j7.interaction.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.entity.Grade;
import com.zeroone.star.project.query.j7.interaction.GradeQuery;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

@Mapper
public interface GradeMapper extends BaseMapper<Grade> {
    /**
     * 分页查询考核项列表
     * @param page 分页对象
     * @param query 查询条件
     * @return 考核项分页结果
     */
    IPage<Grade> selectGradePage(Page<?> page, @Param("query") GradeQuery query);

    /**
     * 批量逻辑删除（将 deleted 设为 1）
     * @param ids ID 列表
     * @return 删除数量
     */
    int deleteLogicBatchIds(@Param("ids") java.util.List<Long> ids);
}


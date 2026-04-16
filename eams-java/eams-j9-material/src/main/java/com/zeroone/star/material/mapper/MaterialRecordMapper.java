package com.zeroone.star.material.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.material.entity.MaterialRecordDO;
import com.zeroone.star.project.dto.j9.material.MaterialRecordDTO;
import com.zeroone.star.project.query.j9.material.MaterialRecordQuery;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

/**
 * <p>
 * 物料出入库记录 Mapper 接口
 * </p>
 *
 * @author fantast
 * @since 2026-03-16
 */
@Mapper
public interface MaterialRecordMapper extends BaseMapper<MaterialRecordDO> {

    Page<MaterialRecordDTO> selectMaterialRecordList(Page<MaterialRecordDTO> page, @Param("query") MaterialRecordQuery query);

}

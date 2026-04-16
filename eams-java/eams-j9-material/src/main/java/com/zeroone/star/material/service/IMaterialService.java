package com.zeroone.star.material.service;

import com.zeroone.star.material.entity.MaterialDO;
import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j9.material.MaterialDTO;
import com.zeroone.star.project.query.j9.material.MaterialRecordQuery;

import java.util.List;

/**
 * <p>
 * 物料表 服务类
 * </p>
 *
 * @author fantast
 * @since 2026-03-16
 */
public interface IMaterialService extends IService<MaterialDO> {

    int updateMaterialState(List<Long> ids, Integer state);

    PageDTO<MaterialDTO> listAll(MaterialRecordQuery condition);

    MaterialDTO getMaterialById(Long id);

    Long saveMaterial(MaterialDTO dto);

}

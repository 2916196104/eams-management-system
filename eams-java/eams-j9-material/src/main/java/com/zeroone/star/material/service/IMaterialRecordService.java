package com.zeroone.star.material.service;

import com.zeroone.star.material.entity.MaterialRecordDO;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j9.material.MaterialRecordDTO;
import com.zeroone.star.project.query.j9.material.MaterialRecordQuery;
import com.baomidou.mybatisplus.extension.service.IService;

import java.util.List;

/**
 * <p>
 * 物料出入库记录 服务类
 * </p>
 *
 * @author fantast
 * @since 2026-03-16
 */
public interface IMaterialRecordService extends IService<MaterialRecordDO> {

    List<Long> saveInStorage(List<Long> ids, int amount);

    List<Long> saveOutStorage(List<Long> ids, int amount);

    PageDTO<MaterialRecordDTO> listPage(MaterialRecordQuery query);

}

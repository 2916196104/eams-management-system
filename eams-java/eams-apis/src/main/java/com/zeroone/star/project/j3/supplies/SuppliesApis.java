package com.zeroone.star.project.j3.supplies;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j3.supplies.MaterialStockChangeDTO;
import com.zeroone.star.project.query.j3.supplies.MaterialRecordQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j3.supplies.MaterialRecordVO;
import com.zeroone.star.project.vo.j3.supplies.MaterialStockVO;

/**
 * <p>
 * 描述：物料接口
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 阿伟学长
 * @version 1.0.0
 */
public interface SuppliesApis {

    /**
     * 物料出入库
     * @param materialStockChangeDTO 出入库信息
     * @return 修改结果
     */
    JsonVO<MaterialStockVO> changeMaterialAmount(MaterialStockChangeDTO materialStockChangeDTO);

    /**
     * 物料出入库记录分页查询
     * @param query 查询条件
     * @return 出入库记录分页列表
     */
    JsonVO<PageDTO<MaterialRecordVO>> queryMaterialRecordPage(MaterialRecordQuery query);
}


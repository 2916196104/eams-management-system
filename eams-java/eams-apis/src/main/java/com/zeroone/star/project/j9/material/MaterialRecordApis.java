package com.zeroone.star.project.j9.material;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j9.material.MaterialRecordDTO;
import com.zeroone.star.project.query.j9.material.MaterialRecordQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.ApiParam;
import org.springframework.web.bind.annotation.RequestBody;

import javax.validation.Valid;
import javax.validation.constraints.NotEmpty;
import java.util.List;

public interface MaterialRecordApis {
    /**
     * 查询物料记录分页列表
     * @param condition 物料记录查询条件
     * @return 物料记录分页列表
     */
    JsonVO<PageDTO<MaterialRecordDTO>> queryPage(@Valid MaterialRecordQuery condition);

    /**
     * 批量入库
     * @param ids 物料ID列表
     * @param amount 入库数量
     * @return 入库结果
     */
    JsonVO<List<Long>> addInStorage(
            @ApiParam(value = "物料ID列表", required = true)
            @NotEmpty(message = "至少选择一个物料")
            @RequestBody List<Long> ids,
            Integer amount
    );

    /**
     * 批量出库
     * @param ids 物料ID列表
     * @param amount 出库数量
     * @return 出库结果
     */
    JsonVO<List<Long>> addOutStorage(
            @ApiParam(value = "物料ID列表", required = true)
            @NotEmpty(message = "至少选择一个物料")
            @RequestBody List<Long> ids,
            Integer amount
    );
}

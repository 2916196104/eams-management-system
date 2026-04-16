package com.zeroone.star.project.j9.material;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j9.material.MaterialDTO;
import com.zeroone.star.project.query.j9.material.MaterialRecordQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.ApiParam;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestParam;

import javax.validation.constraints.Max;
import javax.validation.constraints.Min;
import javax.validation.constraints.NotEmpty;
import javax.validation.constraints.NotNull;
import java.util.List;

/**
 * 物料管理接口
 */
public interface MaterialApis {

    /**
     * 获取物料列表（条件+分页）
     */
    JsonVO<PageDTO<MaterialDTO>> queryAll(MaterialRecordQuery condition);

    /**
     * 获取物料详情
     */
    JsonVO<MaterialDTO> queryById(
            @ApiParam(value = "物料ID", required = true) @PathVariable Long id);

    /**
     * 保存物料
     */
    JsonVO<Long> addMaterial(@RequestBody MaterialDTO dto);

    /**
     * 删除物料（支持批量删除）
     */
    JsonVO<String> removeMaterials(
            @ApiParam(value = "物料ID列表", required = true) @RequestBody List<Long> ids);

    /**
     * 启/禁用物料（支持批量）
     */
    JsonVO<String> modifyMaterialState(
            @ApiParam(value = "物料ID列表", required = true)
            @NotEmpty(message = "至少选择一个物料")
            @RequestBody List<Long> ids,

            @ApiParam(value = "状态：0禁用 1启用", required = true)
            @NotNull(message = "状态不能为空")
            @Min(value = 0, message = "状态只能是0或1")
            @Max(value = 1, message = "状态只能是0或1")
            @RequestParam Integer state
    );
}

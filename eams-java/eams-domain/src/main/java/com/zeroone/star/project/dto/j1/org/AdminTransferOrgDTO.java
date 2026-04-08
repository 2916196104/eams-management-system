package com.zeroone.star.project.dto.j1.org;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import java.util.List;

/**
 * <p>
 * 描述：管理员批量转出员工机构数据传输对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author chchu
 * @version 1.0.0
 */
@Data
@ApiModel("管理员批量转出员工机构数据传输对象")
public class AdminTransferOrgDTO {
    @ApiModelProperty(value = "员工ID集合", required = true)
    private List<Long> staffIds;

    @ApiModelProperty(value = "目标机构ID", required = true)
    private Long targetOrgId;
}
package com.zeroone.star.project.dto.j1.org;

import lombok.Data;
import javax.validation.constraints.NotEmpty;
import javax.validation.constraints.NotNull;
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
public class AdminTransferOrgDTO {
    @NotEmpty(message = "员工ID列表不能为空")
    private List<Long> staffIds;

    @NotNull(message = "目标机构ID不能为空")
    private Long targetOrgId;
}
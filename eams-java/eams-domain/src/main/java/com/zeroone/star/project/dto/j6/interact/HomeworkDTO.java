package com.zeroone.star.project.dto.j6.interact;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * <p>作业数据传输对象
 * </p>
 *
 * @author yuqiuchiling
 * @since 2026-03-16
 */
@Data
public class HomeworkDTO {
    /**
     * 作业ID,新增不传，查询，修改必须传
     */
    @ApiModelProperty(value = "作业ID,新增不传，查询，修改必须传", example = "1323453463")
    private Long id;

}
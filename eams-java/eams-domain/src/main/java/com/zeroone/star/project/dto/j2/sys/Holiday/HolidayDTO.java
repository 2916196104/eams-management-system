package com.zeroone.star.project.dto.j2.sys.Holiday;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDate;
import java.time.LocalDateTime;

/**
 * <p>
 * 描述：节日数据传输对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author Wind
 * @version 1.0.0
 */
@Data
public class HolidayDTO {
    /**
     * 节日id
     */
    @ApiModelProperty(value = "节日id", example = "15")
    private Long id;

    /**
     * 节日时间
     */
    @ApiModelProperty(value = "节日时间", example = "2027-01-01")
    private LocalDate holidayTime;
}

package com.zeroone.star.project.dto.j3.data;


import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;

@Data
public class ClassHourStatsDTO {
    /**
     * 老师ID
     */
    @ApiModelProperty(value = "老师ID", example = "1")
    private Long teacherId;

    /**
     * 姓名
     */
    @ApiModelProperty(value = "姓名", example = "李老师")
    private String teacherName;

    /**
     * 总课时数
     */
    @ApiModelProperty(value = "总课时数", example = "100")
    private BigDecimal totalHours;
}

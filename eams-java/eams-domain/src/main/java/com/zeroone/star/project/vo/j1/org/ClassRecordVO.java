package com.zeroone.star.project.vo.j1.org;

import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;
import java.time.LocalDate;

/**
 * <p>
 * 描述：员工带班记录展示对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author chichu
 * @version 1.0.0
 */
@Data
@Builder
@NoArgsConstructor
@AllArgsConstructor
public class ClassRecordVO {
    @ApiModelProperty(value = "班级名称", example = "2026春季Java班")
    private String className;

    @ApiModelProperty(value = "课程名称", example = "Java后端开发")
    private String courseName;

    @ApiModelProperty(value = "学生人数", example = "30")
    private Integer studentCount;

    @ApiModelProperty(value = "开班时间", example = "2026-02-15")
    private LocalDate startDate;

    @ApiModelProperty(value = "上课进度", example = "50%")
    private String progress;
}
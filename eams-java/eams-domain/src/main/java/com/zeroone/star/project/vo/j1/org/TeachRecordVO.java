package com.zeroone.star.project.vo.j1.org;

import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;
import java.time.LocalDateTime;

/**
 * <p>
 * 描述：员工授课记录展示对象
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
public class TeachRecordVO {
    @ApiModelProperty(value = "上课时间", example = "2026-03-18 14:00:00")
    private LocalDateTime classTime;

    @ApiModelProperty(value = "所属课程", example = "Java后端开发")
    private String courseName;

    @ApiModelProperty(value = "班级名称", example = "2026春季Java班")
    private String className;

    @ApiModelProperty(value = "教室", example = "A栋302教室")
    private String classroom;

    @ApiModelProperty(value = "状态", example = "已完成")
    private String status;
}
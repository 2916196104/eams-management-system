package com.zeroone.star.project.vo.j9.course;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * 批量删除课程结果 VO
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
@ApiModel(description = "批量删除课程结果")
public class CourseDeleteVO {

    @ApiModelProperty(value = "是否全部删除成功", example = "true")
    private Boolean allSuccess;

    @ApiModelProperty(value = "成功删除的数量", example = "3")
    private Integer successCount;

    @ApiModelProperty(value = "因排课等原因失败的数量", example = "0")
    private Integer failCount;
}
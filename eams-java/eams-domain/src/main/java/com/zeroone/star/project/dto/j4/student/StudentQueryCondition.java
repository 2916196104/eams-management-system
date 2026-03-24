package com.zeroone.star.project.dto.j4.student;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import org.springframework.format.annotation.DateTimeFormat;

import java.util.Date;

/**
 * <p>
 * 结业学员查询条件DTO
 * </p>
 */
@Data
@ApiModel(value = "结业学员查询条件", description = "用于接收结业学员列表的查询参数")
public class StudentQueryCondition {

    @ApiModelProperty(value = "学员姓名（模糊查询）", example = "张小宝")
    private String name;

    @ApiModelProperty(value = "所属分校ID", example = "1001")
    private Long schoolId;

    @ApiModelProperty(value = "结业状态（1-已结业，0-未结业）", example = "1", allowableValues = "0,1")
    private Integer graduationState; // 保留字段，用于前端传参，代码中转换为日期判断

    @ApiModelProperty("结业日期-开始")
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private Date graduationDateStart;

    @ApiModelProperty("结业日期-结束")
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private Date graduationDateEnd;
}
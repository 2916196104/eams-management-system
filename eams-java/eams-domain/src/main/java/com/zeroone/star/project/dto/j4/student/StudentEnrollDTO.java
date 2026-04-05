package com.zeroone.star.project.dto.j4.student;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.Getter;
import lombok.Setter;

import java.math.BigDecimal;
import java.time.LocalDate;

@Data
@Setter
@Getter
@ApiModel("学员报名请求对象")
public class StudentEnrollDTO {

    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    @ApiModelProperty(value = "学员ID", required = true, example = "1")
    private Long studentId;

    @ApiModelProperty(value = "课程ID", required = true, example = "1")
    private Long courseId;

    @ApiModelProperty(value = "科目ID", required = true, example = "8")
    private Long subjectId;

    @ApiModelProperty(value = "总课时数", example = "11")
    private Integer countLessonTotal;

    @ApiModelProperty(value = "应付金额", example = "111111.00")
    private BigDecimal amount;

    @ApiModelProperty(value = "实付金额", example = "111111.00")
    private BigDecimal paidAmount;

    @ApiModelProperty(value = "单价", example = "10101.00")
    private BigDecimal unitPrice;

    @ApiModelProperty(value = "开始日期")
    private LocalDate startDate;

    @ApiModelProperty(value = "过期日期")
    private LocalDate expireDate;

    @ApiModelProperty(value = "操作人ID/老师ID", example = "1")
    private Long staffId;

    @ApiModelProperty(value = "备注")
    private String remark;
}
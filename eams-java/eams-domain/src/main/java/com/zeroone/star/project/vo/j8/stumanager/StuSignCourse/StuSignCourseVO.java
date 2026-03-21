package com.zeroone.star.project.vo.j8.stumanager.StuSignCourse;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDateTime;

@Data
@ApiModel("学员课程报名VO")
public class StuSignCourseVO {
    @ApiModelProperty(value = "报名ID")
    private Long id;

    @ApiModelProperty(value = "学生ID")
    private Long studentId;

    @ApiModelProperty(value = "课程ID")
    private Long courseId;

    @ApiModelProperty(value = "报名类型")
    private String enrollType;

    @ApiModelProperty(value = "开始日期")
    private LocalDateTime beginDate;

    @ApiModelProperty(value = "有效期至")
    private LocalDateTime expiredDate;

    @ApiModelProperty(value = "购买课时数")
    private Integer lessonCount;

    @ApiModelProperty(value = "课程金额")
    private BigDecimal courseAmount;

    @ApiModelProperty(value = "实收金额")
    private BigDecimal realAmount;

    @ApiModelProperty(value = "优惠金额")
    private BigDecimal discountAmount;

    @ApiModelProperty(value = "收款经手人")
    private String counselor;

    @ApiModelProperty(value = "备注")
    private String remark;

    @ApiModelProperty(value = "财务审核课时数")
    private Integer verifiedLessonCount;
}

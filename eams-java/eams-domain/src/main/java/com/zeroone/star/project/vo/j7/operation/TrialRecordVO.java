package com.zeroone.star.project.vo.j7.operation;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDate;
import java.time.LocalDateTime;

@Data
@ApiModel("试听卡领取记录显示对象")
public class TrialRecordVO {
    @ApiModelProperty("记录ID")
    private Long id;

    @ApiModelProperty("试听卡ID")
    private Long trialId;

    @ApiModelProperty("试听卡名称")
    private String trialTitle;

    @ApiModelProperty("学生/领取人ID")
    private Long studentId;

    @ApiModelProperty("领取人姓名")
    private String studentName;

    @ApiModelProperty("电话 (脱敏处理，如180****1233)")
    private String mobile;

    @ApiModelProperty("课程名称")
    private String courseName;

    @ApiModelProperty("包含课时数")
    private Integer lessonCount;

    @ApiModelProperty("领取时间")
    private LocalDateTime addTime;

    @ApiModelProperty("过期时间")
    private LocalDate expiredDate;
}

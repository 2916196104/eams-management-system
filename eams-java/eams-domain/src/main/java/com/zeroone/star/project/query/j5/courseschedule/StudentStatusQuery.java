package com.zeroone.star.project.query.j5.courseschedule;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
public class StudentStatusQuery extends PageQuery {
    @ApiModelProperty(value = "课次ID", example = "1", required = true)
    private Long lessonId;

    @ApiModelProperty(value = "搜索关键字(学员姓名/手机号)", example = "张三")
    private String keyword;

    @ApiModelProperty(value = "签到状态 0-未签到 1-已签到 2-迟到 3-请假 4-旷课", example = "1")
    private String status;

}

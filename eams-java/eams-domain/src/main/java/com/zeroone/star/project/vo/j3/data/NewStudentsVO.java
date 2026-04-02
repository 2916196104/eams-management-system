package com.zeroone.star.project.vo.j3.data;

import com.fasterxml.jackson.annotation.JsonFormat;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDate;

@Data
public class NewStudentsVO {
    @ApiModelProperty(value = "新学员数量",example = "100")
    private Integer count;

    @ApiModelProperty(value = "具体日期",example = "2026-03-16")
    @JsonFormat(pattern = "yyyy-MM-dd",timezone = "GMT+8")
    private LocalDate day;
}

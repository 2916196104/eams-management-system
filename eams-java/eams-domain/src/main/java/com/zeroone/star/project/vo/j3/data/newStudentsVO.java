package com.zeroone.star.project.vo.j3.data;

import com.fasterxml.jackson.annotation.JsonFormat;
import io.swagger.annotations.ApiModelProperty;
import jdk.vm.ci.meta.Local;
import lombok.Data;
import org.springframework.format.annotation.DateTimeFormat;

import java.time.LocalDate;

@Data
public class newStudentsVO {
    @ApiModelProperty(value = "新学员数量",example = "100")
    private Integer count;

    @ApiModelProperty(value = "具体日期",example = "2026-03-16")
    @JsonFormat(pattern = "yyyy-MM-dd",timezone = "GMT+8")
    private LocalDate day;
}

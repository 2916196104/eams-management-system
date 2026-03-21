package com.zeroone.star.project.query.j1.console;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDate;

@Data
@ApiModel(value = "MyRegistrationQuery", description = "Course enrollment query")
public class MyRegistrationQuery extends PageQuery {

    @ApiModelProperty(value = "Student name or phone")
    private String keyword;

    @ApiModelProperty(value = "Start date begin")
    private LocalDate startDateBegin;

    @ApiModelProperty(value = "Start date end")
    private LocalDate startDateEnd;
}

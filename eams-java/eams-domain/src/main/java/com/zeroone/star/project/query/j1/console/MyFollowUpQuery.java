package com.zeroone.star.project.query.j1.console;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDate;

@Data
@ApiModel(value = "MyFollowUpQuery", description = "Customer follow-up query")
public class MyFollowUpQuery extends PageQuery {

    @ApiModelProperty(value = "Student name or phone")
    private String keyword;

    @ApiModelProperty(value = "Stage")
    private Integer stage;

    @ApiModelProperty(value = "Start date begin")
    private LocalDate startDateBegin;

    @ApiModelProperty(value = "Start date end")
    private LocalDate startDateEnd;
}

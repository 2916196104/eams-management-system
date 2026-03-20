package com.zeroone.star.project.query.j1.console;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
@ApiModel(value = "NoticeQuery", description = "Notice query")
public class NoticeQuery extends PageQuery {

    @ApiModelProperty(value = "Title")
    private String title;
}

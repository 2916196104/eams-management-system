package com.zeroone.star.project.query;

import io.swagger.annotations.ApiModelProperty;
import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

import javax.validation.constraints.Min;

@Getter
@Setter
@ToString
public class PageQuery {
    @Min(value = 1, message = "pageNum must be at least 1")
    @ApiModelProperty(value = "Current page", example = "1")
    private Integer pageNum = 1;

    @Min(value = 1, message = "pageSize must be at least 1")
    @ApiModelProperty(value = "Page size", example = "30")
    private Integer pageSize = 30;

    public Integer getPageIndex() {
        return pageNum;
    }

    public void setPageIndex(Integer pageIndex) {
        this.pageNum = pageIndex;
    }
}

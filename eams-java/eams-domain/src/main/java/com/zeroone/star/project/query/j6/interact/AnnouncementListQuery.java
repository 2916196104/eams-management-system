package com.zeroone.star.project.query.j6.interact;


import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
public class AnnouncementListQuery extends PageQuery {
    @ApiModelProperty(value = "公告标题")
    private String title;

    @ApiModelProperty("发布者")
    private String creator;

    @ApiModelProperty("类型")
    private Integer type;
}

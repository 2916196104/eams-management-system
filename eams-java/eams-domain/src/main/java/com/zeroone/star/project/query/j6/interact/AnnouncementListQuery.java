package com.zeroone.star.project.query.j6.interact;


import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.EqualsAndHashCode;

@Data
@EqualsAndHashCode(callSuper = true)
@ApiModel("公告列表查询条件")
public class AnnouncementListQuery extends PageQuery {
    @ApiModelProperty(value = "公告标题(模糊查询)")
    private String title;

    @ApiModelProperty(value = "发布者ID")
    private Long creatorId;

    @ApiModelProperty(value = "类型(1-学生端首页弹出,2-学生端首页公告,3-学生端首页Banner,4-普通公告)")
    private Integer type;
}

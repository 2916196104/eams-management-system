package com.zeroone.star.project.query.j7.interaction;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;


@Data
public class NoticeQuery extends PageQuery {

    @ApiModelProperty(value = "发布人",example = "张三")
    private String creator;

    @ApiModelProperty(value = "公告类型",example = "通知")
    private String type;

    @ApiModelProperty(value = "公告标题",example = "新版上线公告")
    private String title;




}

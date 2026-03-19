package com.zeroone.star.project.vo.j1.console;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;
import java.util.List;

@Data
@ApiModel(value = "NoticeConsoleVO", description = "控制台公告列表视图对象")
public class NoticeConsoleVO {

    @ApiModelProperty(value = "总记录数")
    private Long total;

    @ApiModelProperty(value = "公告列表")
    private List<NoticeItem> list;

    @Data
    @ApiModel(value = "NoticeItem", description = "单条公告记录")
    public static class NoticeItem {

        @ApiModelProperty(value = "公告ID")
        private Long id;

        @ApiModelProperty(value = "公告标题")
        private String title;

        @ApiModelProperty(value = "公告内容")
        private String content;

        @ApiModelProperty(value = "浏览次数")
        private Integer viewNum;

        @ApiModelProperty(value = "创建人")
        private Long creator;

        @ApiModelProperty(value = "编辑人")
        private Long editor;

        @ApiModelProperty(value = "添加时间")
        private LocalDateTime addTime;

        @ApiModelProperty(value = "编辑时间")
        private LocalDateTime editTime;

        @ApiModelProperty(value = "删除标记")
        private Boolean deleted;
    }
}

package com.zeroone.star.project.vo.j1.console;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;
import java.util.List;

@Data
@ApiModel(value = "NoticeConsoleVO", description = "公告列表视图对象")
public class ConsoleNoticeVO {

    @ApiModelProperty(value = "总记录数")
    private Long total;

    @ApiModelProperty(value = "公告列表")
    private List<NoticeItem> list;

    @Data
    @ApiModel(value = "NoticeItem", description = "单条公告记录")
    public static class NoticeItem {

        @ApiModelProperty(value = "公告ID")
        private Long id;

        @ApiModelProperty(value = "标题")
        private String title;

        @ApiModelProperty(value = "添加时间")
        private LocalDateTime addTime;

        @ApiModelProperty(value = "修改时间")
        private LocalDateTime editTime;
    }
}

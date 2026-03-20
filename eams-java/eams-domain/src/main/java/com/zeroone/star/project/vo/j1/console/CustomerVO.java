package com.zeroone.star.project.vo.j1.console;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;
import java.util.List;

@Data
@ApiModel(value = "CustomerVO", description = "我的跟进列表视图对象")
public class CustomerVO {

    @ApiModelProperty(value = "总记录数")
    private Long total;

    @ApiModelProperty(value = "跟进列表")
    private List<CustomerItem> list;

    @Data
    @ApiModel(value = "CustomerItem", description = "单条跟进记录")
    public static class CustomerItem {

        @ApiModelProperty(value = "主键ID")
        private Long id;

        @ApiModelProperty(value = "跟进时间")
        private LocalDateTime contactTime;

        @ApiModelProperty(value = "客户")
        private String studentName;

        @ApiModelProperty(value = "阶段")
        private String stageName;

        @ApiModelProperty(value = "跟进方式")
        private String contactTypeName;

        @ApiModelProperty(value = "下次跟进")
        private LocalDateTime contactNextTime;

        @ApiModelProperty(value = "记录时间")
        private LocalDateTime addTime;

        @ApiModelProperty(value = "跟进内容")
        private String info;
    }
}

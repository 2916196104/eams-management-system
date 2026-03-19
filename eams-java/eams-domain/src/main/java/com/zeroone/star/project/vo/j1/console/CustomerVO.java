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

        @ApiModelProperty(value = "学生id")
        private Long studentId;

        @ApiModelProperty(value = "跟进记录")
        private String info;

        @ApiModelProperty(value = "联系时间")
        private LocalDateTime contactTime;

        @ApiModelProperty(value = "下次联系时间")
        private LocalDateTime contactNextTime;

        @ApiModelProperty(value = "联系方式")
        private Integer contactType;

        @ApiModelProperty(value = "联系电话")
        private String contactPhone;

        @ApiModelProperty(value = "创建者")
        private Long creator;

        @ApiModelProperty(value = "时间")
        private LocalDateTime addTime;

        @ApiModelProperty(value = "进展阶段")
        private Integer stage;

        @ApiModelProperty(value = "删除标记")
        private Boolean deleted;

        @ApiModelProperty(value = "所属组织ID")
        private Long orgId;

        // --- 关联查询字段（非表字段） ---

        @ApiModelProperty(value = "客户名称（关联student表）")
        private String studentName;

        @ApiModelProperty(value = "阶段名称（字典转换）")
        private String stageName;

        @ApiModelProperty(value = "跟进方式名称（字典转换）")
        private String contactTypeName;
    }
}

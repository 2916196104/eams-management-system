package com.zeroone.star.project.vo.j1.console;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;
import java.util.List;

/**
 * <p>
 * 描述：我的客户视图对象
 * </p>
 * @author hxb
 */
@Data
@ApiModel(value = "MyCustomerVO", description = "我的客户视图对象")
public class MyCustomerVO {

    @ApiModelProperty(value = "总记录数")
    private Long total;

    @ApiModelProperty(value = "客户列表")
    private List<CustomerItem> list;

    @Data
    @ApiModel(value = "CustomerItem", description = "单条客户记录")
    public static class CustomerItem {

        @ApiModelProperty(value = "主键ID")
        private Long id;

        @ApiModelProperty(value = "学员姓名")
        private String studentName;

        @ApiModelProperty(value = "家长姓名")
        private String parentName;

        @ApiModelProperty(value = "家庭关系：1-爸爸 2-妈妈 3-爷爷 4-奶奶 5-外公 6-外婆 7-其他")
        private Integer familyRel;

        @ApiModelProperty(value = "家庭关系名称")
        private String familyRelName;

        @ApiModelProperty(value = "联系电话")
        private String contactPhone;

        @ApiModelProperty(value = "学习阶段：0-意向学员 1-在读学员 2-结业学员")
        private Integer stage;

        @ApiModelProperty(value = "学习阶段名称")
        private String stageName;

        @ApiModelProperty(value = "性别：0-未知 1-男 2-女")
        private Integer gender;

        @ApiModelProperty(value = "性别名称")
        private String genderName;

        @ApiModelProperty(value = "年龄")
        private Integer age;

        @ApiModelProperty(value = "来源")
        private String sourceName;

        @ApiModelProperty(value = "剩余课次")
        private Integer remainLessonCount;

        @ApiModelProperty(value = "欠缺状态：0-正常 1-欠缺")
        private Integer deficiencyStatus;

        @ApiModelProperty(value = "添加时间")
        private LocalDateTime addTime;

        @ApiModelProperty(value = "最近跟进时间")
        private LocalDateTime lastFollowTime;

        @ApiModelProperty(value = "最近跟进内容")
        private String lastFollowContent;

        @ApiModelProperty(value = "下次跟进时间")
        private LocalDateTime nextFollowTime;

        @ApiModelProperty(value = "备注")
        private String remark;
    }
}

package com.zeroone.star.project.dto.j2.sys.Template;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.Getter;
import lombok.Setter;

import javax.validation.constraints.Max;
import javax.validation.constraints.Min;
import javax.validation.constraints.Pattern;
import javax.validation.constraints.Size;
import javax.validation.constraints.NotBlank;

@Data
@Getter
@Setter
@ApiModel("示例模版传输对象")
public class TemplateDTO {
    @ApiModelProperty(value = "主键ID（新增时不传，修改时必传）", example = "1")
    private Long id;

    @NotBlank(message = "通知名称不能为空")
    @Size(min = 2, max = 255, message = "通知名称长度必须在2-255之间")
    @ApiModelProperty(value = "通知名称", example = "学员上课提醒", required = true)
    private String name;

    @NotBlank(message = "通知编码不能为空")
    @Pattern(regexp = "^[a-zA-Z][a-zA-Z0-9_]*$", message = "通知编码必须以字母开头，只能包含字母、数字和下划线")
    @ApiModelProperty(value = "通知编码", example = "studentLessonStart", required = true)
    private String code;

    @ApiModelProperty(value = "微信通知开关", example = "1")
    private Integer wxOn;

    @Size(max = 255, message = "微信模板ID长度不能超过255")
    @ApiModelProperty(value = "微信模板ID", example = "VPRMRW8分店2ibUYaOg5vs8Jg8VlLYoEGVMqz4uIYwE_VVg")
    private String wxCode;

    @ApiModelProperty(value = "短信通知开关", example = "1")
    private Integer smsOn;

    @Size(max = 255, message = "短信模板ID长度不能超过255")
    @ApiModelProperty(value = "短信模板ID", example = "SMS_123456789")
    private String smsCode;

    @ApiModelProperty(value = "邮件通知开关", example = "0")
    private Integer emailOn;

    @Size(max = 255, message = "提示说明长度不能超过255")
    @ApiModelProperty(value = "提示说明", example = "上课前一天自动发送上课提醒给学员")
    private String info;

    @Min(value = 0, message = "排序号不能小于0")
    @Max(value = 9999, message = "排序号不能大于9999")
    @ApiModelProperty(value = "排序号", example = "0")
    private Integer sortNum;

    @NotBlank(message = "分组编码不能为空")
    @Pattern(regexp = "^(student|teacher)$", message = "分组编码只能是student或teacher")
    @ApiModelProperty(value = "分组编码", example = "student", allowableValues = "student,teacher", required = true)
    private String groupCode;

    @Size(max = 255, message = "参数说明长度不能超过255")
    @ApiModelProperty(value = "参数说明", example = "公众号消息模板搜标题：上课提醒通知")
    private String params;

    @Size(max = 255, message = "消息备注长度不能超过255")
    @ApiModelProperty(value = "消息备注信息", example = "注意：需要提前一天发送")
    private String noticeRemark;

    @Min(value = 0, message = "状态值只能是0或1")
    @Max(value = 1, message = "状态值只能是0或1")
    @ApiModelProperty(value = "状态", example = "1")
    private Integer state;
}

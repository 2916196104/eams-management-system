package com.zeroone.star.project.dto.j8.SaveStu;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.Size;
import java.time.LocalDate;

@ApiModel("学员信息保存DTO")
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
public class SaveStuDTO {

    @ApiModelProperty(value = "学员ID（修改必传，新增不传）")
    private Long id;

    @NotBlank(message = "手机号不能为空")
    @Size(min = 11, max = 11, message = "手机号必须是11位")
    @ApiModelProperty(value = "家长手机号", required = true)
    private String phone;

    @NotNull(message = "所属校区不能为空")
    @ApiModelProperty(value = "所属校区ID", required = true)
    private Long schoolId;

    @ApiModelProperty(value = "家长姓名")
    private String parentName;

    @ApiModelProperty(value = "亲属关系")
    private Integer familyRel;

    @NotBlank(message = "学员姓名不能为空")
    @ApiModelProperty(value = "学员姓名", required = true)
    private String name;

    @NotNull(message = "学生性别不能为空")
    @ApiModelProperty(value = "学生性别 1-男 2-女", required = true)
    private Integer gender;

    @ApiModelProperty(value = "出生年月")
    private LocalDate birthday;

    @ApiModelProperty(value = "身份证号")
    private String idcard;

    @ApiModelProperty(value = "入学时间")
    private LocalDate joinDate;

    @ApiModelProperty(value = "年级")
    private String grade;

    @ApiModelProperty(value = "来源")
    private Integer joinWay;

    @ApiModelProperty(value = "备注")
    private String remark;
}

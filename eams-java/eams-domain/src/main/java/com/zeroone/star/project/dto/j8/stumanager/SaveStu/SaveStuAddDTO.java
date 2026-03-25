package com.zeroone.star.project.dto.j8.stumanager.SaveStu;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;

import lombok.Getter;
import lombok.Setter;
import lombok.ToString;
import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.Pattern;
import javax.validation.constraints.Size;
import java.time.LocalDate;
import java.time.Year;

/**
 * <p>
 * 描述：学员信息新增DTO
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author tsfmn
 * @version 1.0.0
 */
@Getter
@Setter
@ToString
@ApiModel("学员信息新增DTO")
public class SaveStuAddDTO {


    @NotBlank(message = "手机号不能为空")
    @Pattern(regexp = "^1[3-9]\\d{9}$", message = "手机号格式不正确")
    @ApiModelProperty(value = "手机号", example = "13800001111", required = true)
    private String phone;

    @NotNull(message = "所属校区不能为空")
    @ApiModelProperty(value = "所属校区ID", example = "1", required = true)
    private Long schoolId;

    @NotBlank(message = "学员姓名不能为空")
    @ApiModelProperty(value = "学员姓名", example = "张三", required = true)
    private String name;

    @NotNull(message = "学生性别不能为空")
    @ApiModelProperty(value = "学生性别（1男/2女）", example = "1", required = true)
    private Integer gender;

    @NotBlank(message = "身份证号不能为空")
    @Pattern(regexp = "^[1-9]\\d{5}(18|19|20)\\d{2}(0[1-9]|1[0-2])(0[1-9]|[12]\\d|3[01])\\d{3}[0-9Xx]$", message = "身份证号格式不正确")
    @ApiModelProperty(value = "身份证号", example = "110101199001011234", required = true)
    private String idcard;

    @ApiModelProperty(value = "家长姓名", example = "张父")
    private String parentName;

    @ApiModelProperty(value = "亲属关系（字典值）", example = "1")
    private Integer familyRel;

    @ApiModelProperty(value = "入学时间（入学日期）", example = "2024-09-01")
    private LocalDate joinDate;

    @ApiModelProperty(value = "年级ID（字典值）", example = "3")
    private Integer gradeId;

    @ApiModelProperty(value = "出生年月", example = "2010-05-20")
    private LocalDate birthday;

    @ApiModelProperty(value = "来源ID（字典值）", example = "2")
    private Long joinWay;

    @ApiModelProperty(value = "备注", example = "试听后报名")
    private String remark;

    @ApiModelProperty(value = "阶段状态（0意向学员）", example = "0")
    private Integer stage;


}
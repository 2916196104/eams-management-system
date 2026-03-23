package com.zeroone.star.project.dto.j8.SaveStu;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Getter;
import lombok.Setter;
import lombok.ToString;
import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;
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

    @NotBlank(message = "学员姓名不能为空")
    @ApiModelProperty(value = "学员姓名", required = true, example = "张三")
    private String name;

    @NotNull(message = "学生性别不能为空")
    @ApiModelProperty(value = "学生性别 1-男 2-女", required = true, example = "1")
    private Integer gender;

    @ApiModelProperty(value = "出生年月", example = "2018-01-01")
    private LocalDate birthday;

    @ApiModelProperty(value = "身份证号", example = "110101201801011234")
    private String idcard;

    @ApiModelProperty(value = "入学年级", example = "2024")
    private Year grade;

    @NotBlank(message = "手机号不能为空")
    @Size(min = 11, max = 11, message = "手机号必须是11位")
    @ApiModelProperty(value = "家长手机号", required = true, example = "13800138000")
    private String phone;

    @ApiModelProperty(value = "家长姓名", example = "张父")
    private String parentName;

    @ApiModelProperty(value = "亲属关系 （字典值）", example = "1")
    private Integer familyRel;

    @ApiModelProperty(value = "入学日期", example = "2024-09-01")
    private LocalDate joinDate;

    @ApiModelProperty(value = "来源（加入方式）ID", example = "1")
    private Long joinWay;

    @ApiModelProperty(value = "备注", example = "一年级新生，数学薄弱")
    private String remark;

    @ApiModelProperty(value = "阶段状态 0-意向学员（默认0）", example = "0")
    private Integer stage = 0; // 意向学员为默认值，无需强制校验

    @ApiModelProperty(value = "顾问ID（经手人）", example = "1")
    private Long counselor; // 对应实体顾问字段，前端选择经手人传值

    @ApiModelProperty(value = "年级ID（字典值）", example = "1")
    private Integer gradeId; // 实体新增年级ID，适配前端年级选择

}
package com.zeroone.star.project.dto.j4.student;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;


import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.time.LocalDate;
import java.time.LocalDateTime;

//StudentDTO：包含学员基础信息及扩展属性。
@Data
@ApiModel(description = "学员数据传输对象")
@NoArgsConstructor
@AllArgsConstructor
public class StudentDTO {

    @ApiModelProperty(value = "学员ID", example = "1001", required = true)
    private String studentId;

    @ApiModelProperty(value = "学员姓名", example = "张三")
    private String studentName;

    @ApiModelProperty(value = "学员id", example = "1")
    private Long id;

    @ApiModelProperty(value = "顾问")
    private Long counselor;

    @ApiModelProperty(value = "手机号")
    private String mobile;

    @ApiModelProperty(value = "所属校区")
    private Long schoolId;

    @ApiModelProperty(value = "家长姓名")
    private String userName;

    @ApiModelProperty(value = "亲属关系")
    private Integer familyRel;

    @ApiModelProperty(value = "学员姓名")
    private String name;

    @ApiModelProperty(value = "性别")
    private Integer gender;

    @ApiModelProperty(value = "入学时间")
    private LocalDateTime admissionTime;

    @ApiModelProperty(value = "年级ID")
    private Integer gradeId;

    @ApiModelProperty(value = "出生年月")
    private LocalDate birthday;

    @ApiModelProperty(value = "身份证号")
    private String idCard;

    @ApiModelProperty(value = "备注")
    private String remark;

    @ApiModelProperty(value = "来源")
    private String source;

    @ApiModelProperty(value = "学员阶段状态")
    private Integer stage;


    @ApiModelProperty(value = "头像地址", example = "group1/M00/00/01/a.png")
    private String headImg; // 对应 student.head_img

    @ApiModelProperty(value = "入班日期")
    private LocalDateTime joinDate;

    @ApiModelProperty(value = "微信OpenID关联")
    private String wxAccessId;

    @ApiModelProperty(value = "信誉度/积分", example = "0")
    private Integer credit;

    @ApiModelProperty(value = "机构ID", example = "1")
    private Long orgId;


    // --- 业务扩展属性 ---
    @ApiModelProperty(value = "业务专用：关联课程ID", example = "1")
    private Long courseId;

    @ApiModelProperty(value = "家长ID")
    private Long userId;   // 必须加

}

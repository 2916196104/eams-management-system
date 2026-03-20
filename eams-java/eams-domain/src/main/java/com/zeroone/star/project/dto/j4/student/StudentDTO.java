package com.zeroone.star.project.dto.j4.student;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * 学员基础信息及扩展属性 DTO
 */
@Data
@ApiModel(value = "学员详情传输对象", description = "包含学员表全字段及业务扩展属性")
public class StudentDTO implements Serializable {

    @ApiModelProperty(value = "主键ID", example = "1")
    private Long id;

    @ApiModelProperty(value = "用户ID (关联家长端用户)", example = "1")
    private Long userId;

    @ApiModelProperty(value = "家庭关系 (1:爸爸 2:妈妈等)", example = "1")
    private Integer familyRel;

    @ApiModelProperty(value = "是否设为默认 (0:否 1:是)", example = "1")
    private Integer asDefault;

    @ApiModelProperty(value = "所属学校ID", example = "1")
    private Long schoolId;

    @ApiModelProperty(value = "学员姓名", example = "张三三")
    private String name;

    @ApiModelProperty(value = "逻辑删除 (0:正常 1:已删除)", example = "0")
    private Integer deleted;

    @ApiModelProperty(value = "学员阶段 (1:在学 2:意向 3:结业)", example = "1")
    private Long stage;

    @ApiModelProperty(value = "性别 (0:女 1:男 2:未知)", example = "1")
    private Integer gender;

    @ApiModelProperty(value = "出生日期")
    private LocalDateTime birthday;

    @ApiModelProperty(value = "头像地址")
    private String headImg;

    @ApiModelProperty(value = "入读方式")
    private String joinWay;

    @ApiModelProperty(value = "备注信息")
    private String remark;

    @ApiModelProperty(value = "毕业日期")
    private LocalDateTime graduationDate;

    @ApiModelProperty(value = "毕业原因")
    private String graduationReason;

    @ApiModelProperty(value = "报名时间/添加时间")
    private LocalDateTime addTime;

    @ApiModelProperty(value = "咨询师ID (员工ID)", example = "1")
    private Long counselor;

    @ApiModelProperty(value = "创建者ID", example = "1")
    private Long creator;

    @ApiModelProperty(value = "修改者ID", example = "1")
    private Long editor;

    @ApiModelProperty(value = "最后修改时间")
    private LocalDateTime editTime;

    @ApiModelProperty(value = "身份证号")
    private String idcard;

    @ApiModelProperty(value = "红点等级/积分等级")
    private Integer redpointGrade;

    @ApiModelProperty(value = "红点评价")
    private String redpointEvaluate;

    @ApiModelProperty(value = "年级")
    private String grade;

    @ApiModelProperty(value = "入班日期")
    private LocalDateTime joinDate;

    @ApiModelProperty(value = "微信OpenID关联")
    private String wxAccessId;

    @ApiModelProperty(value = "信誉度/积分", example = "0")
    private Integer credit;

    @ApiModelProperty(value = "机构ID", example = "1")
    private Long orgId;

    @ApiModelProperty(value = "班级ID", example = "1")
    private Long gradeId;

    // --- 业务扩展属性 ---

    @ApiModelProperty(value = "业务专用：学员ID (通常同id)", example = "1")
    private Long studentId;

    @ApiModelProperty(value = "业务专用：关联课程ID", example = "1")
    private Long courseId;
}
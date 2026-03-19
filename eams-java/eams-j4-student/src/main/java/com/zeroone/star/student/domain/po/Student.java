package com.zeroone.star.student.domain.po;

import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableName;
import com.baomidou.mybatisplus.annotation.IdType;
import java.time.Year;
import java.time.LocalDate;
import java.time.LocalDateTime;
import com.baomidou.mybatisplus.annotation.TableId;
import java.io.Serializable;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.EqualsAndHashCode;
import lombok.experimental.Accessors;

/**
 * <p>
 * 学生表
 * </p>
 *
 * @author zrt
 * @since 2026-03-16
 */

@Accessors(chain = true)@Data
@EqualsAndHashCode(callSuper = false)
@TableName("student")
@ApiModel(value="Student对象", description="学生表")
public class Student implements Serializable {

    private static final long serialVersionUID = 1L;

    @ApiModelProperty(value = "主键")
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    @ApiModelProperty(value = "家长id")
    @TableField("user_id")
    private Long userId;

    @ApiModelProperty(value = "家庭关系")
    @TableField("family_rel")
    private Integer familyRel;

    @ApiModelProperty(value = "家长默认查看的学员")
    @TableField("as_default")
    private Boolean asDefault;

    @ApiModelProperty(value = "所属分校")
    @TableField("school_id")
    private Long schoolId;

    @ApiModelProperty(value = "姓名")
    @TableField("name")
    private String name;

    @ApiModelProperty(value = "逻辑删除")
    @TableField("deleted")
    private Integer deleted;

    @ApiModelProperty(value = "阶段状态0意向学员")
    @TableField("stage")
    private Integer stage;

    @ApiModelProperty(value = "性别")
    @TableField("gender")
    private Integer gender;

    @ApiModelProperty(value = "生日")
    @TableField("birthday")
    private LocalDate birthday;

    @ApiModelProperty(value = "头像")
    @TableField("head_img")
    private String headImg;

    @ApiModelProperty(value = "加入方式")
    @TableField("join_way")
    private Long joinWay;

    @ApiModelProperty(value = "备注")
    @TableField("remark")
    private String remark;

    @ApiModelProperty(value = "结业日期")
    @TableField("graduation_date")
    private LocalDate graduationDate;

    @ApiModelProperty(value = "结业原因")
    @TableField("graduation_reason")
    private String graduationReason;

    @ApiModelProperty(value = "加入时间")
    @TableField("add_time")
    private LocalDateTime addTime;

    @ApiModelProperty(value = "顾问")
    @TableField("counselor")
    private Long counselor;

    @ApiModelProperty(value = "创建者")
    @TableField("creator")
    private Long creator;

    @ApiModelProperty(value = "编辑人")
    @TableField("editor")
    private Long editor;

    @ApiModelProperty(value = "编辑时间")
    @TableField("edit_time")
    private LocalDateTime editTime;

    @ApiModelProperty(value = "身份证号")
    @TableField("idcard")
    private String idcard;

    @ApiModelProperty(value = "红点标记成绩最后查看时间")
    @TableField("redpoint_grade")
    private LocalDateTime redpointGrade;

    @ApiModelProperty(value = "红点标记点评最后查看时间")
    @TableField("redpoint_evaluate")
    private LocalDateTime redpointEvaluate;

    @ApiModelProperty(value = "入学年份")
    @TableField("grade")
    private Year grade;

    @ApiModelProperty(value = "入学日期")
    @TableField("join_date")
    private LocalDate joinDate;

    @ApiModelProperty(value = "微信登录记录id")
    @TableField("wx_access_id")
    private Long wxAccessId;

    @ApiModelProperty(value = "学生积分")
    @TableField("credit")
    private Integer credit;

    @ApiModelProperty(value = "创建者所属组织ID")
    @TableField("org_id")
    private Long orgId;

    @ApiModelProperty(value = "年级ID")
    @TableField("grade_id")
    private Integer gradeId;


}

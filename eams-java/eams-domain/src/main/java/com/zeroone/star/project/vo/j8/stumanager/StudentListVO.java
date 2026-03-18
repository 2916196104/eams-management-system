package com.zeroone.star.project.vo.j8.stumanager;

import com.fasterxml.jackson.annotation.JsonFormat;

import com.zeroone.star.project.eums.FamilyRelationshipEnum;
import com.zeroone.star.project.eums.GenderEnum;
import com.zeroone.star.project.eums.StudentStageEnum;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import java.time.LocalDate;
import java.time.LocalDateTime;

@Data
@ApiModel(value = "StudentListVO", description = "学员列表展示对象")
public class StudentListVO {
    @ApiModelProperty(value = "学员id",example = "1")
    private Long id;
    @ApiModelProperty(value = "学员姓名",example = "张三")
    private String name;
    @ApiModelProperty(value = "家长姓名",example = "李四")
    private String parentName;
    @ApiModelProperty(value = "亲属关系",example = "爸爸",
            allowableValues = "无,爸爸,妈妈,爷爷,奶奶,姥爷,姥姥,叔叔,姑姑,其他")
    private FamilyRelationshipEnum familyRel;
    @ApiModelProperty(value = "联系电话", example = "13800138000")
    private String mobile;
    @ApiModelProperty(value = "顾问姓名",example = "管理员")
    private String counselorName;
    @ApiModelProperty(value = "年级",example = "2025级")
    private String gradeName;
    @ApiModelProperty(value = "学校名")
    private String schoolName;
    // 剩余课次 当参数里有班级id的时候有只返回班级关联的课程数 todo
    @ApiModelProperty(value = "剩余课次数")
    private Integer countLessonRemaining;
    @ApiModelProperty(value = "当前积分")
    private Integer credit;
    @ApiModelProperty(value = "性别",example = "男",
            allowableValues = "未知，男，女")
    private GenderEnum gender;
    @ApiModelProperty(value = "年龄")
    private Integer age;
    @ApiModelProperty(value = "备注")
    private String remark;
    @ApiModelProperty(value = "客户来源名称",example = "抖音平台")
    private String joinWayName;
    @ApiModelProperty(value = "最新跟进记录时间",example = "2026-03-18 15:30")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm", timezone = "GMT+8")
    private LocalDateTime contactTime;
    @ApiModelProperty(value = "下次联跟进时间", example = "2026-03-20")
    @JsonFormat(pattern = "yyyy-MM-dd", timezone = "GMT+8")
    private LocalDateTime contactNextTime;
    @ApiModelProperty(value = "阶段",example = "在学学员",
            allowableValues = "在学学员,意向学员,结业学员")
    private StudentStageEnum stage;
    @ApiModelProperty(value = "结业日期", example = "2026-03-20")
    @JsonFormat(pattern = "yyyy-MM-dd", timezone = "GMT+8")
    private LocalDate graduationDate;
}

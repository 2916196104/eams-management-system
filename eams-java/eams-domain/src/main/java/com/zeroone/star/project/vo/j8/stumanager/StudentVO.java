package com.zeroone.star.project.vo.j8.stumanager;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import java.math.BigDecimal;
import java.time.LocalDate;
import java.time.LocalDateTime;

@Data
@ApiModel(value = "StudentVO", description = "学员信息展示对象")
public class StudentVO {

    @ApiModelProperty(value = "学员ID", example = "10001")
    private Long id;

    @ApiModelProperty(value = "关联用户ID", example = "20001")
    private Long userId;

    @ApiModelProperty(value = "家庭关系", example = "父亲")
    private String familyRel;

    @ApiModelProperty(value = "是否默认 0-否 1-是", example = "1")
    private Integer asDefault;

    @ApiModelProperty(value = "学校ID", example = "3001")
    private Long schoolId;

    @ApiModelProperty(value = "学员姓名", example = "张三")
    private String name;

    @ApiModelProperty(value = "阶段/年级", example = "高中三年级")
    private String stage;

    @ApiModelProperty(value = "性别 0-女 1-男", example = "1")
    private Integer gender;

    @ApiModelProperty(value = "出生日期", example = "2005-10-01")
    private LocalDate birthday;

    @ApiModelProperty(value = "头像地址", example = "https://xxx.com/head.jpg")
    private String headImg;

    @ApiModelProperty(value = "入学方式", example = "统招")
    private String joinWay;

    @ApiModelProperty(value = "备注信息", example = "优秀学员")
    private String remark;

    @ApiModelProperty(value = "毕业日期", example = "2025-06-15")
    private LocalDate graduationDate;

    @ApiModelProperty(value = "毕业原因", example = "正常毕业")
    private String graduationReason;

    @ApiModelProperty(value = "创建时间", example = "2025-01-01 12:00:00")
    private LocalDateTime addTime;

    @ApiModelProperty(value = "辅导员", example = "李老师")
    private String counselor;

    @ApiModelProperty(value = "身份证号", example = "430123200510011234")
    private String idcard;

    @ApiModelProperty(value = "红点等级", example = "A级")
    private String redpointGrade;

    @ApiModelProperty(value = "红点评价", example = "表现优异")
    private String redpointEvaluate;

    @ApiModelProperty(value = "班级名称", example = "高三1班")
    private String grade;

    @ApiModelProperty(value = "入学日期", example = "2022-09-01")
    private LocalDate joinDate;

    @ApiModelProperty(value = "微信唯一标识", example = "o6_bmjrPTlm6_2sgVt7hMZOPfL2M")
    private String wxAccessId;

    @ApiModelProperty(value = "学分", example = "95.5")
    private BigDecimal credit;

    @ApiModelProperty(value = "机构ID", example = "5001")
    private Long orgId;

    @ApiModelProperty(value = "班级ID", example = "6001")
    private Long gradeId;
}
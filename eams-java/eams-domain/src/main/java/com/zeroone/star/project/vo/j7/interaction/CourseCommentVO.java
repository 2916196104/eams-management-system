package com.zeroone.star.project.vo.j7.interaction;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

/**
 * 教师评价学生返回VO
 * 贴合数据库字段 + 原型图展示字段（序号/学员/课次标题/点评得分/点评内容/点评老师/点评时间）
 * 数据库映射：score=点评得分 / content=点评内容 / creator=点评老师ID / add_time=点评时间
 */
@ApiModel(value = "CourseCommentVO", description = "教师评价学生-列表返回数据")
@Data
public class CourseCommentVO {
    // 原型图展示：序号
    @ApiModelProperty(value = "序号", example = "1")
    private Integer serialNumber;

    // 原型图展示：学员（关联student_id查询姓名）
    @ApiModelProperty(value = "学员姓名", example = "张三")
    private String studentName;

    // 原型图展示：课次标题（关联course_id查询标题）
    @ApiModelProperty(value = "课次标题", example = "Java基础第10讲")
    private String courseTitle;

    // 数据库字段：score → 原型图展示：点评得分
    @ApiModelProperty(value = "点评得分", example = "95")
    private Integer score;

    // 数据库字段：content → 原型图展示：点评内容
    @ApiModelProperty(value = "点评内容", example = "课堂表现优秀，作业完成及时")
    private String content;

    // 原型图展示：点评老师（关联creator查询姓名）
    @ApiModelProperty(value = "点评老师", example = "李四老师")
    private String creatorName;

    // 数据库字段：add_time → 原型图展示：点评时间
    @ApiModelProperty(value = "点评时间", example = "2026-03-14 10:00:00")
    private LocalDateTime addTime;

    // 数据库保留字段（非展示字段，隐藏）
    @ApiModelProperty(value = "订单ID", hidden = true)
    private Long orderId;
    @ApiModelProperty(value = "评价状态（1=有效，0=无效）", hidden = true)
    private Integer state;
    @ApiModelProperty(value = "编辑人ID", hidden = true)
    private Long editor;
    @ApiModelProperty(value = "编辑时间", hidden = true)
    private LocalDateTime editTime;
    @ApiModelProperty(value = "删除状态（1=已删，0=未删）", hidden = true)
    private Integer deleted;
}
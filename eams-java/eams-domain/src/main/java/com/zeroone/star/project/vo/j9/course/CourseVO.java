package com.zeroone.star.project.vo.j9.course;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.math.BigDecimal;
import java.time.LocalDateTime;

/**
 * 课程列表返回数据 VO
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
@ApiModel(description = "课程列表展示数据")
public class CourseVO {

    @ApiModelProperty(value = "课程ID", example = "1001")
    private Long id;

    @ApiModelProperty(value = "课程名称", example = "零基础钢琴入门")
    private String name;

    @ApiModelProperty(value = "机构名称", example = "第一音乐分校")
    private String orgName;

    @ApiModelProperty(value = "科目名称", example = "钢琴")
    private String subjectName;

    @ApiModelProperty(value = "课程价格", example = "199.00")
    private BigDecimal price;

    @ApiModelProperty(value = "课程状态（0=禁用, 1=启用）", example = "1")
    private Integer state;

    @ApiModelProperty(value = "课程状态描述", example = "已启用")
    private String stateDesc;

    @ApiModelProperty(value = "封面图片URL", example = "http://xxx.com/cover.jpg")
    private String cover;

    @ApiModelProperty(value = "创建时间", example = "2026-03-15 10:30:00")
    private LocalDateTime createTime;
    
    // 根据状态自动设置状态描述
    public void setState(Integer state) {
        this.state = state;
        if (state != null) {
            this.stateDesc = state == 1 ? "已启用" : "已禁用";
        } else {
            this.stateDesc = "未知";
        }
    }
}
package com.zeroone.star.project.query.j4.student;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
@ApiModel(description = "学员查询条件")
public class StudentQuery {

    // ====================== 分页参数（前端要求：pageIndex/pageSize 必传）======================
    @ApiModelProperty(value = "当前页码", required = true, example = "1")
    private Integer pageIndex; // 核心修改：page → pageIndex

    @ApiModelProperty(value = "每页条数", required = true, example = "10")
    private Integer pageSize;

    // ====================== 查询条件（和文档/原型一致）======================
    @ApiModelProperty(value = "学员ID")
    private String studentId;

    @ApiModelProperty(value = "学员姓名")
    private String name;

    @ApiModelProperty(value = "手机号")
    private String phone;

    @ApiModelProperty(value = "状态")
    private String status;

    @ApiModelProperty(value = "顾问ID")
    private String advisorId;
    // 课程ID，用于筛选
    private Long courseId;
}
package com.zeroone.star.project.query.j4.student;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

//StudentQuery: 包含姓名、电话、状态（在线/意向/结业）、顾问ID、分页参数。
@Data
public class StudentQuery extends PageQuery {

    @ApiModelProperty(value = "学员ID", example = "111")
    private Long id;

    @ApiModelProperty(value = "姓名", example = "张三")
    private String name;

    @ApiModelProperty(value = "电话", example = "13800000000")
    private String phone;

    @ApiModelProperty(value = "状态 如意向学员", example = "1")
    private Integer stage;

    @ApiModelProperty(value = "顾问ID", example = "111111")
    private Long adviserId;



}

package com.zeroone.star.project.dto.j4.student;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
@ApiModel("账号查询条件")
public class UserQueryDTO {

    @ApiModelProperty("家长姓名（模糊查询）")
    private String name;

    @ApiModelProperty("手机号（模糊查询）")
    private String mobile;

    @ApiModelProperty("账号状态 0禁用 1正常")
    private Integer state;

    @ApiModelProperty("所属学校ID")
    private Long schoolId;

    @ApiModelProperty("分页页码")
    private Long pageNum = 1L;

    @ApiModelProperty("分页每页条数")
    private Long pageSize = 10L;

}
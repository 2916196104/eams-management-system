package com.zeroone.star.project.vo.j4.student;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

@Data
@ApiModel("账号列表VO")
public class UserVO {

    @ApiModelProperty("账号ID")
    private Long id;

    @ApiModelProperty("家长姓名")
    private String name;

    @ApiModelProperty("手机号")
    private String mobile;

    @ApiModelProperty("邮箱")
    private String email;

    @ApiModelProperty("账号状态 0禁用 1正常")
    private Integer state;

    @ApiModelProperty("所属学校ID")
    private Long schoolId;

    @ApiModelProperty("登录次数")
    private Integer loginTimes;

    @ApiModelProperty("上次登录时间")
    private LocalDateTime latestLoginTime;

    @ApiModelProperty("加入时间")
    private LocalDateTime addTime;

    @ApiModelProperty("备注")
    private String remark;
}
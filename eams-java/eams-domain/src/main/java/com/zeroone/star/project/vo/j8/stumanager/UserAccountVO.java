package com.zeroone.star.project.vo.j8.stumanager;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;
import java.util.List;

/**
 * 学员家长账号视图对象
 *
 * @author j26
 */
@Data
@ApiModel(value = "UserAccountVO", description = "学员家长账号响应数据")
public class UserAccountVO {

    @ApiModelProperty(value = "用户主键", example = "1")
    private Long id;

    @ApiModelProperty(value = "家长姓名", example = "张三")
    private String name;

    @ApiModelProperty(value = "手机号账号", example = "13800138000")
    private String mobile;

    @ApiModelProperty(value = "邮箱", example = "zhangsan@example.com")
    private String email;

    @ApiModelProperty(value = "账号状态：1-启用，0-禁用", example = "1")
    private Integer state;

    @ApiModelProperty(value = "登录次数", example = "10")
    private Integer loginTimes;

    @ApiModelProperty(value = "上次登录时间", example = "2026-03-10 15:30:00")
    private LocalDateTime latestLoginTime;

    @ApiModelProperty(value = "上次登录IP", example = "192.168.1.100")
    private String latestLoginIp;

    @ApiModelProperty(value = "加入时间", example = "2025-01-01 10:00:00")
    private LocalDateTime addTime;

    @ApiModelProperty(value = "备注", example = "VIP用户")
    private String remark;

    @ApiModelProperty(value = "所属学校ID", example = "1")
    private Long schoolId;

    @ApiModelProperty(value = "所属组织ID", example = "1")
    private Long orgId;

    @ApiModelProperty(value = "关联学生列表")
    private List<StudentSimpleVO> students;

    /**
     * 学生简要信息
     */
    @Data
    @ApiModel(value = "StudentSimpleVO", description = "学生简要信息")
    public static class StudentSimpleVO {

        @ApiModelProperty(value = "学生ID", example = "100")
        private Long id;

        @ApiModelProperty(value = "学生姓名", example = "小明")
        private String name;

        @ApiModelProperty(value = "家庭关系：0-父亲，1-母亲，2-其他", example = "0")
        private Integer familyRel;

        @ApiModelProperty(value = "是否默认查看", example = "true")
        private Boolean asDefault;
    }
}

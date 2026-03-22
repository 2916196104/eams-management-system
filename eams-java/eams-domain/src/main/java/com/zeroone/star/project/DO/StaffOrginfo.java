package com.zeroone.star.project.DO;

import javax.validation.constraints.Size;
import javax.validation.constraints.NotNull;

import java.io.Serializable;

import java.util.Date;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import org.hibernate.validator.constraints.Length;

/**
* 员工机构信息表
* @TableName staff_orginfo
*/
@Data
public class StaffOrginfo implements Serializable {

    /**
     * 主键
     */
    @NotNull(message = "[主键]不能为空")
    @ApiModelProperty("主键")
    private Long id;
    /**
     * 员工id
     */
    @ApiModelProperty("员工id")
    private Long staffId;
    /**
     * 所属机构
     */
    @ApiModelProperty("所属机构")
    private Long orgId;
    /**
     * 所属集团
     */
    @ApiModelProperty("所属集团")
    private Long groupId;
    /**
     * 所属公司
     */
    @ApiModelProperty("所属公司")
    private Long comId;
    /**
     * 所属部门
     */
    @ApiModelProperty("所属部门")
    private Long dptId;
    /**
     * 所属职位
     */
    @ApiModelProperty("所属职位")
    private Long positionId;
    /**
     * 删除标记
     */
    @ApiModelProperty("删除标记")
    private Integer deleted;
    /**
     *
     */
    @ApiModelProperty("")
    private Date addTime;
    /**
     *
     */
    @ApiModelProperty("")
    private Long creator;
    /**
     * id全路径
     */
    @Size(max = 255, message = "编码长度不能超过255")
    @ApiModelProperty("id全路径")
    @Length(max = 255, message = "编码长度不能超过255")
    private String idPath;

}

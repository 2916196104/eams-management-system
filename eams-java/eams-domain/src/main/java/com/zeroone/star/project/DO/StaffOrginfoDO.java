package com.zeroone.star.project.DO;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.Size;
import javax.validation.constraints.NotNull;

import java.io.Serializable;

import java.util.Date;
import io.swagger.annotations.ApiModelProperty;
import org.hibernate.validator.constraints.Length;

/**
* 员工机构信息表
* @TableName staff_orginfo
*/
public class StaffOrginfoDO implements Serializable {

    /**
    * 主键
    */
    @NotNull(message="[主键]不能为空")
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
    @Size(max= 255,message="编码长度不能超过255")
    @ApiModelProperty("id全路径")
    @Length(max= 255,message="编码长度不能超过255")
    private String idPath;

    /**
    * 主键
    */
    private void setId(Long id){
    this.id = id;
    }

    /**
    * 员工id
    */
    private void setStaffId(Long staffId){
    this.staffId = staffId;
    }

    /**
    * 所属机构
    */
    private void setOrgId(Long orgId){
    this.orgId = orgId;
    }

    /**
    * 所属集团
    */
    private void setGroupId(Long groupId){
    this.groupId = groupId;
    }

    /**
    * 所属公司
    */
    private void setComId(Long comId){
    this.comId = comId;
    }

    /**
    * 所属部门
    */
    private void setDptId(Long dptId){
    this.dptId = dptId;
    }

    /**
    * 所属职位
    */
    private void setPositionId(Long positionId){
    this.positionId = positionId;
    }

    /**
    * 删除标记
    */
    private void setDeleted(Integer deleted){
    this.deleted = deleted;
    }

    /**
    * 
    */
    private void setAddTime(Date addTime){
    this.addTime = addTime;
    }

    /**
    * 
    */
    private void setCreator(Long creator){
    this.creator = creator;
    }

    /**
    * id全路径
    */
    private void setIdPath(String idPath){
    this.idPath = idPath;
    }


    /**
    * 主键
    */
    private Long getId(){
    return this.id;
    }

    /**
    * 员工id
    */
    private Long getStaffId(){
    return this.staffId;
    }

    /**
    * 所属机构
    */
    private Long getOrgId(){
    return this.orgId;
    }

    /**
    * 所属集团
    */
    private Long getGroupId(){
    return this.groupId;
    }

    /**
    * 所属公司
    */
    private Long getComId(){
    return this.comId;
    }

    /**
    * 所属部门
    */
    private Long getDptId(){
    return this.dptId;
    }

    /**
    * 所属职位
    */
    private Long getPositionId(){
    return this.positionId;
    }

    /**
    * 删除标记
    */
    private Integer getDeleted(){
    return this.deleted;
    }

    /**
    * 
    */
    private Date getAddTime(){
    return this.addTime;
    }

    /**
    * 
    */
    private Long getCreator(){
    return this.creator;
    }

    /**
    * id全路径
    */
    private String getIdPath(){
    return this.idPath;
    }

}

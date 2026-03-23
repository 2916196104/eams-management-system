package com.zeroone.star.project.DO;

import javax.validation.constraints.Size;
import javax.validation.constraints.NotNull;

import java.io.Serializable;

import java.util.Date;
import io.swagger.annotations.ApiModelProperty;
import org.hibernate.validator.constraints.Length;

/**
* 物料出入库记录
* @TableName material_record
*/
public class MaterialRecord implements Serializable {

    /**
    * 主键
    */
    @NotNull(message="[主键]不能为空")
    @ApiModelProperty("主键")
    private Long id;
    /**
    * 物料ID
    */
    @NotNull(message="[物料ID]不能为空")
    @ApiModelProperty("物料ID")
    private Long materialId;
    /**
    * 变动数量
    */
    @ApiModelProperty("变动数量")
    private Integer amount;
    /**
    * 变动原因说明
    */
    @Size(max= 50,message="编码长度不能超过50")
    @ApiModelProperty("变动原因说明")
    @Length(max= 50,message="编码长度不能超过50")
    private String reason;
    /**
    * 变动类型1入库2出库3积分商城出库 
    */
    @ApiModelProperty("变动类型1入库2出库3积分商城出库 ")
    private Integer changeType;
    /**
    * 变动对象id如积分商城里的商品id
    */
    @ApiModelProperty("变动对象id如积分商城里的商品id")
    private Long changeTargetId;
    /**
    * 备注信息
    */
    @Size(max= 100,message="编码长度不能超过100")
    @ApiModelProperty("备注信息")
    @Length(max= 100,message="编码长度不能超过100")
    private String remark;
    /**
    * 创建人
    */
    @ApiModelProperty("创建人")
    private Long creator;
    /**
    * 编辑人
    */
    @ApiModelProperty("编辑人")
    private Long editor;
    /**
    * 变动时间
    */
    @ApiModelProperty("变动时间")
    private Date addTime;
    /**
    * 编辑时间
    */
    @ApiModelProperty("编辑时间")
    private Date editTime;
    /**
    * 删除标记
    */
    @ApiModelProperty("删除标记")
    private Integer deleted;
    /**
    * 涉及学生id
    */
    @ApiModelProperty("涉及学生id")
    private Long studentId;
    /**
    * 涉及员工id
    */
    @ApiModelProperty("涉及员工id")
    private Long staffId;
    /**
    * 所属物料的组织ID
    */
    @ApiModelProperty("所属物料的组织ID")
    private Long orgId;
    /**
    * 学校id
    */
    @ApiModelProperty("学校id")
    private Long schoolId;

    /**
    * 主键
    */
    private void setId(Long id){
    this.id = id;
    }

    /**
    * 物料ID
    */
    private void setMaterialId(Long materialId){
    this.materialId = materialId;
    }

    /**
    * 变动数量
    */
    private void setAmount(Integer amount){
    this.amount = amount;
    }

    /**
    * 变动原因说明
    */
    private void setReason(String reason){
    this.reason = reason;
    }

    /**
    * 变动类型1入库2出库3积分商城出库 
    */
    private void setChangeType(Integer changeType){
    this.changeType = changeType;
    }

    /**
    * 变动对象id如积分商城里的商品id
    */
    private void setChangeTargetId(Long changeTargetId){
    this.changeTargetId = changeTargetId;
    }

    /**
    * 备注信息
    */
    private void setRemark(String remark){
    this.remark = remark;
    }

    /**
    * 创建人
    */
    private void setCreator(Long creator){
    this.creator = creator;
    }

    /**
    * 编辑人
    */
    private void setEditor(Long editor){
    this.editor = editor;
    }

    /**
    * 变动时间
    */
    private void setAddTime(Date addTime){
    this.addTime = addTime;
    }

    /**
    * 编辑时间
    */
    private void setEditTime(Date editTime){
    this.editTime = editTime;
    }

    /**
    * 删除标记
    */
    private void setDeleted(Integer deleted){
    this.deleted = deleted;
    }

    /**
    * 涉及学生id
    */
    private void setStudentId(Long studentId){
    this.studentId = studentId;
    }

    /**
    * 涉及员工id
    */
    private void setStaffId(Long staffId){
    this.staffId = staffId;
    }

    /**
    * 所属物料的组织ID
    */
    private void setOrgId(Long orgId){
    this.orgId = orgId;
    }

    /**
    * 学校id
    */
    private void setSchoolId(Long schoolId){
    this.schoolId = schoolId;
    }


    /**
    * 主键
    */
    private Long getId(){
    return this.id;
    }

    /**
    * 物料ID
    */
    private Long getMaterialId(){
    return this.materialId;
    }

    /**
    * 变动数量
    */
    private Integer getAmount(){
    return this.amount;
    }

    /**
    * 变动原因说明
    */
    private String getReason(){
    return this.reason;
    }

    /**
    * 变动类型1入库2出库3积分商城出库 
    */
    private Integer getChangeType(){
    return this.changeType;
    }

    /**
    * 变动对象id如积分商城里的商品id
    */
    private Long getChangeTargetId(){
    return this.changeTargetId;
    }

    /**
    * 备注信息
    */
    private String getRemark(){
    return this.remark;
    }

    /**
    * 创建人
    */
    private Long getCreator(){
    return this.creator;
    }

    /**
    * 编辑人
    */
    private Long getEditor(){
    return this.editor;
    }

    /**
    * 变动时间
    */
    private Date getAddTime(){
    return this.addTime;
    }

    /**
    * 编辑时间
    */
    private Date getEditTime(){
    return this.editTime;
    }

    /**
    * 删除标记
    */
    private Integer getDeleted(){
    return this.deleted;
    }

    /**
    * 涉及学生id
    */
    private Long getStudentId(){
    return this.studentId;
    }

    /**
    * 涉及员工id
    */
    private Long getStaffId(){
    return this.staffId;
    }

    /**
    * 所属物料的组织ID
    */
    private Long getOrgId(){
    return this.orgId;
    }

    /**
    * 学校id
    */
    private Long getSchoolId(){
    return this.schoolId;
    }

}

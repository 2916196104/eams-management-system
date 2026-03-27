package com.zeroone.star.project.DO;

import com.baomidou.mybatisplus.annotation.TableName;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import org.hibernate.validator.constraints.Length;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.Size;
import java.io.Serializable;
import java.util.Date;

/**
* 物料表
* @TableName material
*/
@Data
public class Material implements Serializable {

    /**
    * 主键
    */
    @NotNull(message="[主键]不能为空")
    @ApiModelProperty("主键")
    private Long id;
    /**
    * 所属学校
    */
    @NotNull(message="[所属学校]不能为空")
    @ApiModelProperty("所属学校")
    private Long schoolId;
    /**
    * 所属分类ID
    */
    @NotNull(message="[所属分类ID]不能为空")
    @ApiModelProperty("所属分类ID")
    private Long categoryId;
    /**
    * 分类名
    */
    @Size(max= 255,message="编码长度不能超过255")
    @ApiModelProperty("分类名")
    @Length(max= 255,message="编码长度不能超过255")
    private String categoryName;
    /**
    * 物料名称
    */
    @NotBlank(message="[物料名称]不能为空")
    @Size(max= 100,message="编码长度不能超过100")
    @ApiModelProperty("物料名称")
    @Length(max= 100,message="编码长度不能超过100")
    private String name;
    /**
    * 库存量
    */
    @ApiModelProperty("库存量")
    private Integer storage;
    /**
    * 物料说明
    */
    @Size(max= 255,message="编码长度不能超过255")
    @ApiModelProperty("物料说明")
    @Length(max= 255,message="编码长度不能超过255")
    private String info;
    /**
    * 封面图
    */
    @Size(max= 200,message="编码长度不能超过200")
    @ApiModelProperty("封面图")
    @Length(max= 200,message="编码长度不能超过200")
    private String cover;
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
    * 添加时间
    */
    @ApiModelProperty("添加时间")
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
    * 启用状态
    */
    @ApiModelProperty("启用状态")
    private Integer state;
    /**
    * 创建者所属组织ID
    */
    @ApiModelProperty("创建者所属组织ID")
    private Long orgId;

    /**
    * 主键
    */
    public void setId(Long id){
    this.id = id;
    }

    /**
    * 所属学校
    */
    public void setSchoolId(Long schoolId){
    this.schoolId = schoolId;
    }

    /**
    * 所属分类ID
    */
    public void setCategoryId(Long categoryId){
    this.categoryId = categoryId;
    }

    /**
    * 分类名
    */
    public void setCategoryName(String categoryName){
    this.categoryName = categoryName;
    }

    /**
    * 物料名称
    */
    public void setName(String name){
    this.name = name;
    }

    /**
    * 库存量
    */
    public void setStorage(Integer storage){
    this.storage = storage;
    }

    /**
    * 物料说明
    */
    public void setInfo(String info){
    this.info = info;
    }

    /**
    * 封面图
    */
    public void setCover(String cover){
    this.cover = cover;
    }

    /**
    * 创建人
    */
    public void setCreator(Long creator){
    this.creator = creator;
    }

    /**
    * 编辑人
    */
    public void setEditor(Long editor){
    this.editor = editor;
    }

    /**
    * 添加时间
    */
    public void setAddTime(Date addTime){
    this.addTime = addTime;
    }

    /**
    * 编辑时间
    */
    public void setEditTime(Date editTime){
    this.editTime = editTime;
    }

    /**
    * 删除标记
    */
    public void setDeleted(Integer deleted){
    this.deleted = deleted;
    }

    /**
    * 启用状态
    */
    public void setState(Integer state){
    this.state = state;
    }

    /**
    * 创建者所属组织ID
    */
    public void setOrgId(Long orgId){
    this.orgId = orgId;
    }


    /**
    * 主键
    */
    public Long getId(){
    return this.id;
    }

    /**
    * 所属学校
    */
    public Long getSchoolId(){
    return this.schoolId;
    }

    /**
    * 所属分类ID
    */
    public Long getCategoryId(){
    return this.categoryId;
    }

    /**
    * 分类名
    */
    public String getCategoryName(){
    return this.categoryName;
    }

    /**
    * 物料名称
    */
    public String getName(){
    return this.name;
    }

    /**
    * 库存量
    */
    public Integer getStorage(){
    return this.storage;
    }

    /**
    * 物料说明
    */
    public String getInfo(){
    return this.info;
    }

    /**
    * 封面图
    */
    public String getCover(){
    return this.cover;
    }

    /**
    * 创建人
    */
    public Long getCreator(){
    return this.creator;
    }

    /**
    * 编辑人
    */
    public Long getEditor(){
    return this.editor;
    }

    /**
    * 添加时间
    */
    public Date getAddTime(){
    return this.addTime;
    }

    /**
    * 编辑时间
    */
    public Date getEditTime(){
    return this.editTime;
    }

    /**
    * 删除标记
    */
    public Integer getDeleted(){
    return this.deleted;
    }

    /**
    * 启用状态
    */
    public Integer getState(){
    return this.state;
    }

    /**
    * 创建者所属组织ID
    */
    public Long getOrgId(){
    return this.orgId;
    }

}

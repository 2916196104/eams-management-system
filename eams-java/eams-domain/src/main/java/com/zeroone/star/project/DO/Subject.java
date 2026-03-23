package generator.domain;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.Size;
import javax.validation.constraints.NotNull;

import java.io.Serializable;

import java.util.Date;
import io.swagger.annotations.ApiModelProperty;
import org.hibernate.validator.constraints.Length;

/**
* 科目
* @TableName subject
*/
public class Subject implements Serializable {

    /**
    * 主键
    */
    @NotNull(message="[主键]不能为空")
    @ApiModelProperty("主键")
    private Long id;
    /**
    * 科目
    */
    @NotBlank(message="[科目]不能为空")
    @Size(max= 255,message="编码长度不能超过255")
    @ApiModelProperty("科目")
    @Length(max= 255,message="编码长度不能超过255")
    private String name;
    /**
    * 简介
    */
    @Size(max= 255,message="编码长度不能超过255")
    @ApiModelProperty("简介")
    @Length(max= 255,message="编码长度不能超过255")
    private String info;
    /**
    * 创建人
    */
    @ApiModelProperty("创建人")
    private Long creator;
    /**
    * 编辑者
    */
    @ApiModelProperty("编辑者")
    private Long editor;
    /**
    * 新增时间
    */
    @ApiModelProperty("新增时间")
    private Date addTime;
    /**
    * 修改时间
    */
    @ApiModelProperty("修改时间")
    private Date editTime;
    /**
    * 删除标记
    */
    @ApiModelProperty("删除标记")
    private Integer deleted;
    /**
    * 排序值
    */
    @ApiModelProperty("排序值")
    private Integer sortNum;
    /**
    * 创建者所属组织ID
    */
    @ApiModelProperty("创建者所属组织ID")
    private Long orgId;

    /**
    * 主键
    */
    private void setId(Long id){
    this.id = id;
    }

    /**
    * 科目
    */
    private void setName(String name){
    this.name = name;
    }

    /**
    * 简介
    */
    private void setInfo(String info){
    this.info = info;
    }

    /**
    * 创建人
    */
    private void setCreator(Long creator){
    this.creator = creator;
    }

    /**
    * 编辑者
    */
    private void setEditor(Long editor){
    this.editor = editor;
    }

    /**
    * 新增时间
    */
    private void setAddTime(Date addTime){
    this.addTime = addTime;
    }

    /**
    * 修改时间
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
    * 排序值
    */
    private void setSortNum(Integer sortNum){
    this.sortNum = sortNum;
    }

    /**
    * 创建者所属组织ID
    */
    private void setOrgId(Long orgId){
    this.orgId = orgId;
    }


    /**
    * 主键
    */
    private Long getId(){
    return this.id;
    }

    /**
    * 科目
    */
    private String getName(){
    return this.name;
    }

    /**
    * 简介
    */
    private String getInfo(){
    return this.info;
    }

    /**
    * 创建人
    */
    private Long getCreator(){
    return this.creator;
    }

    /**
    * 编辑者
    */
    private Long getEditor(){
    return this.editor;
    }

    /**
    * 新增时间
    */
    private Date getAddTime(){
    return this.addTime;
    }

    /**
    * 修改时间
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
    * 排序值
    */
    private Integer getSortNum(){
    return this.sortNum;
    }

    /**
    * 创建者所属组织ID
    */
    private Long getOrgId(){
    return this.orgId;
    }

}

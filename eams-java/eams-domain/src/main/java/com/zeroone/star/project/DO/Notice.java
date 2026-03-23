package com.zeroone.star.project.DO;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.Size;
import javax.validation.constraints.NotNull;

import java.io.Serializable;

import java.util.Date;
import io.swagger.annotations.ApiModelProperty;
import org.hibernate.validator.constraints.Length;

/**
* 公告
* @TableName notice
*/
public class Notice implements Serializable {

    /**
    * id
    */
    @NotNull(message="[id]不能为空")
    @ApiModelProperty("id")
    private Long id;
    /**
    * 公告标题
    */
    @NotBlank(message="[公告标题]不能为空")
    @Size(max= 255,message="编码长度不能超过255")
    @ApiModelProperty("公告标题")
    @Length(max= 255,message="编码长度不能超过255")
    private String title;
    /**
    * 公告内容
    */
    @NotBlank(message="[公告内容]不能为空")
    @Size(max= -1,message="编码长度不能超过-1")
    @ApiModelProperty("公告内容")
    @Length(max= -1,message="编码长度不能超过-1")
    private String content;
    /**
    * 
    */
    @ApiModelProperty("")
    private Integer viewNum;
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
    * id
    */
    private void setId(Long id){
    this.id = id;
    }

    /**
    * 公告标题
    */
    private void setTitle(String title){
    this.title = title;
    }

    /**
    * 公告内容
    */
    private void setContent(String content){
    this.content = content;
    }

    /**
    * 
    */
    private void setViewNum(Integer viewNum){
    this.viewNum = viewNum;
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
    * 添加时间
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
    * id
    */
    private Long getId(){
    return this.id;
    }

    /**
    * 公告标题
    */
    private String getTitle(){
    return this.title;
    }

    /**
    * 公告内容
    */
    private String getContent(){
    return this.content;
    }

    /**
    * 
    */
    private Integer getViewNum(){
    return this.viewNum;
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
    * 添加时间
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

}

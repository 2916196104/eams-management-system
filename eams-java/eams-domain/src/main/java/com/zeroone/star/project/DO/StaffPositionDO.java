package com.zeroone.star.project.DO;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.Size;
import javax.validation.constraints.NotNull;

import java.io.Serializable;

import java.util.Date;
import io.swagger.annotations.ApiModelProperty;
import org.hibernate.validator.constraints.Length;

/**
* 职位表
* @TableName staff_position
*/
public class StaffPositionDO implements Serializable {

    /**
    * 
    */
    @NotNull(message="[]不能为空")
    @ApiModelProperty("")
    private Long id;
    /**
    * 职位名称
    */
    @Size(max= 50,message="编码长度不能超过50")
    @ApiModelProperty("职位名称")
    @Length(max= 50,message="编码长度不能超过50")
    private String name;
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
    * 创建者
    */
    @ApiModelProperty("创建者")
    private Long creator;
    /**
    * 编辑者
    */
    @ApiModelProperty("编辑者")
    private Long editor;

    /**
    * 
    */
    private void setId(Long id){
    this.id = id;
    }

    /**
    * 职位名称
    */
    private void setName(String name){
    this.name = name;
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
    * 创建者
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
    * 
    */
    private Long getId(){
    return this.id;
    }

    /**
    * 职位名称
    */
    private String getName(){
    return this.name;
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
    * 创建者
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

}

package com.zeroone.star.project.DO;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.Size;
import javax.validation.constraints.NotNull;

import java.io.Serializable;

import java.util.Date;
import java.math.BigDecimal;
import io.swagger.annotations.ApiModelProperty;
import org.hibernate.validator.constraints.Length;

/**
* 课程套餐表
* @TableName course
*/
public class Course implements Serializable {

    /**
    * 主键
    */
    @NotNull(message="[主键]不能为空")
    @ApiModelProperty("主键")
    private Long id;
    /**
    * 科目id
    */
    @NotNull(message="[科目id]不能为空")
    @ApiModelProperty("科目id")
    private Long subjectId;
    /**
    * 课程名
    */
    @NotBlank(message="[课程名]不能为空")
    @Size(max= 50,message="编码长度不能超过50")
    @ApiModelProperty("课程名")
    @Length(max= 50,message="编码长度不能超过50")
    private String name;
    /**
    * 启用状态
    */
    @ApiModelProperty("启用状态")
    private Integer state;
    /**
    * 提示信息
    */
    @Size(max= 255,message="编码长度不能超过255")
    @ApiModelProperty("提示信息")
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
    * 添加时间
    */
    @ApiModelProperty("添加时间")
    private Date addTime;
    /**
    * 修改时间
    */
    @ApiModelProperty("修改时间")
    private Date editTime;
    /**
    * 有效期月数
    */
    @ApiModelProperty("有效期月数")
    private Integer expireMonths;
    /**
    * 单价
    */
    @ApiModelProperty("单价")
    private BigDecimal unitPrice;
    /**
    * 总价 销售价
    */
    @ApiModelProperty("总价 销售价")
    private BigDecimal price;
    /**
    * 单位名称
    */
    @Size(max= 20,message="编码长度不能超过20")
    @ApiModelProperty("单位名称")
    @Length(max= 20,message="编码长度不能超过20")
    private String unitName;
    /**
    * 优惠金额 取绝对值
    */
    @ApiModelProperty("优惠金额 取绝对值")
    private BigDecimal discount;
    /**
    * 课次数
    */
    @ApiModelProperty("课次数")
    private Integer lessonCount;
    /**
    * 课堂类型1 大课  2 小班课 3 1v1
    */
    @ApiModelProperty("课堂类型1 大课  2 小班课 3 1v1")
    private Integer lessonType;
    /**
    * 描述
    */
    @Size(max= -1,message="编码长度不能超过-1")
    @ApiModelProperty("描述")
    @Length(max= -1,message="编码长度不能超过-1")
    private String description;
    /**
    * 删除标记
    */
    @ApiModelProperty("删除标记")
    private Integer deleted;
    /**
    * 是否可以预约
    */
    @ApiModelProperty("是否可以预约")
    private Integer bookable;
    /**
    * 是否上架中
    */
    @ApiModelProperty("是否上架中")
    private Integer forSale;
    /**
    * 是否推荐
    */
    @ApiModelProperty("是否推荐")
    private Integer recommend;
    /**
    * 封面
    */
    @Size(max= 255,message="编码长度不能超过255")
    @ApiModelProperty("封面")
    @Length(max= 255,message="编码长度不能超过255")
    private String cover;
    /**
    * 报名截止日期
    */
    @ApiModelProperty("报名截止日期")
    private Date closeDate;
    /**
    * 师资信息
    */
    @Size(max= 255,message="编码长度不能超过255")
    @ApiModelProperty("师资信息")
    @Length(max= 255,message="编码长度不能超过255")
    private String teacherInfo;
    /**
    * 服务说明
    */
    @Size(max= 255,message="编码长度不能超过255")
    @ApiModelProperty("服务说明")
    @Length(max= 255,message="编码长度不能超过255")
    private String serviceInfo;
    /**
    * 库存名额
    */
    @ApiModelProperty("库存名额")
    private Integer storage;
    /**
    * 创建者所属组织ID
    */
    @ApiModelProperty("创建者所属组织ID")
    private Long orgId;
    /**
    * 消课课酬(元/课)
    */
    @ApiModelProperty("消课课酬(元/课)")
    private BigDecimal salary;
    /**
    * 适用年级
    */
    @Size(max= 500,message="编码长度不能超过500")
    @ApiModelProperty("适用年级")
    @Length(max= 500,message="编码长度不能超过500")
    private String gradeIds;
    /**
    * 适用年级名
    */
    @Size(max= 500,message="编码长度不能超过500")
    @ApiModelProperty("适用年级名")
    @Length(max= 500,message="编码长度不能超过500")
    private String gradeNames;

    /**
    * 主键
    */
    private void setId(Long id){
    this.id = id;
    }

    /**
    * 科目id
    */
    private void setSubjectId(Long subjectId){
    this.subjectId = subjectId;
    }

    /**
    * 课程名
    */
    private void setName(String name){
    this.name = name;
    }

    /**
    * 启用状态
    */
    private void setState(Integer state){
    this.state = state;
    }

    /**
    * 提示信息
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
    * 添加时间
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
    * 有效期月数
    */
    private void setExpireMonths(Integer expireMonths){
    this.expireMonths = expireMonths;
    }

    /**
    * 单价
    */
    private void setUnitPrice(BigDecimal unitPrice){
    this.unitPrice = unitPrice;
    }

    /**
    * 总价 销售价
    */
    private void setPrice(BigDecimal price){
    this.price = price;
    }

    /**
    * 单位名称
    */
    private void setUnitName(String unitName){
    this.unitName = unitName;
    }

    /**
    * 优惠金额 取绝对值
    */
    private void setDiscount(BigDecimal discount){
    this.discount = discount;
    }

    /**
    * 课次数
    */
    private void setLessonCount(Integer lessonCount){
    this.lessonCount = lessonCount;
    }

    /**
    * 课堂类型1 大课  2 小班课 3 1v1
    */
    private void setLessonType(Integer lessonType){
    this.lessonType = lessonType;
    }

    /**
    * 描述
    */
    private void setDescription(String description){
    this.description = description;
    }

    /**
    * 删除标记
    */
    private void setDeleted(Integer deleted){
    this.deleted = deleted;
    }

    /**
    * 是否可以预约
    */
    private void setBookable(Integer bookable){
    this.bookable = bookable;
    }

    /**
    * 是否上架中
    */
    private void setForSale(Integer forSale){
    this.forSale = forSale;
    }

    /**
    * 是否推荐
    */
    private void setRecommend(Integer recommend){
    this.recommend = recommend;
    }

    /**
    * 封面
    */
    private void setCover(String cover){
    this.cover = cover;
    }

    /**
    * 报名截止日期
    */
    private void setCloseDate(Date closeDate){
    this.closeDate = closeDate;
    }

    /**
    * 师资信息
    */
    private void setTeacherInfo(String teacherInfo){
    this.teacherInfo = teacherInfo;
    }

    /**
    * 服务说明
    */
    private void setServiceInfo(String serviceInfo){
    this.serviceInfo = serviceInfo;
    }

    /**
    * 库存名额
    */
    private void setStorage(Integer storage){
    this.storage = storage;
    }

    /**
    * 创建者所属组织ID
    */
    private void setOrgId(Long orgId){
    this.orgId = orgId;
    }

    /**
    * 消课课酬(元/课)
    */
    private void setSalary(BigDecimal salary){
    this.salary = salary;
    }

    /**
    * 适用年级
    */
    private void setGradeIds(String gradeIds){
    this.gradeIds = gradeIds;
    }

    /**
    * 适用年级名
    */
    private void setGradeNames(String gradeNames){
    this.gradeNames = gradeNames;
    }


    /**
    * 主键
    */
    private Long getId(){
    return this.id;
    }

    /**
    * 科目id
    */
    private Long getSubjectId(){
    return this.subjectId;
    }

    /**
    * 课程名
    */
    private String getName(){
    return this.name;
    }

    /**
    * 启用状态
    */
    private Integer getState(){
    return this.state;
    }

    /**
    * 提示信息
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
    * 添加时间
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
    * 有效期月数
    */
    private Integer getExpireMonths(){
    return this.expireMonths;
    }

    /**
    * 单价
    */
    private BigDecimal getUnitPrice(){
    return this.unitPrice;
    }

    /**
    * 总价 销售价
    */
    private BigDecimal getPrice(){
    return this.price;
    }

    /**
    * 单位名称
    */
    private String getUnitName(){
    return this.unitName;
    }

    /**
    * 优惠金额 取绝对值
    */
    private BigDecimal getDiscount(){
    return this.discount;
    }

    /**
    * 课次数
    */
    private Integer getLessonCount(){
    return this.lessonCount;
    }

    /**
    * 课堂类型1 大课  2 小班课 3 1v1
    */
    private Integer getLessonType(){
    return this.lessonType;
    }

    /**
    * 描述
    */
    private String getDescription(){
    return this.description;
    }

    /**
    * 删除标记
    */
    private Integer getDeleted(){
    return this.deleted;
    }

    /**
    * 是否可以预约
    */
    private Integer getBookable(){
    return this.bookable;
    }

    /**
    * 是否上架中
    */
    private Integer getForSale(){
    return this.forSale;
    }

    /**
    * 是否推荐
    */
    private Integer getRecommend(){
    return this.recommend;
    }

    /**
    * 封面
    */
    private String getCover(){
    return this.cover;
    }

    /**
    * 报名截止日期
    */
    private Date getCloseDate(){
    return this.closeDate;
    }

    /**
    * 师资信息
    */
    private String getTeacherInfo(){
    return this.teacherInfo;
    }

    /**
    * 服务说明
    */
    private String getServiceInfo(){
    return this.serviceInfo;
    }

    /**
    * 库存名额
    */
    private Integer getStorage(){
    return this.storage;
    }

    /**
    * 创建者所属组织ID
    */
    private Long getOrgId(){
    return this.orgId;
    }

    /**
    * 消课课酬(元/课)
    */
    private BigDecimal getSalary(){
    return this.salary;
    }

    /**
    * 适用年级
    */
    private String getGradeIds(){
    return this.gradeIds;
    }

    /**
    * 适用年级名
    */
    private String getGradeNames(){
    return this.gradeNames;
    }

}

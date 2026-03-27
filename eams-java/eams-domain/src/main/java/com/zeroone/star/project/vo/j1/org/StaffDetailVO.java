//package com.zeroone.star.project.vo.j1.org;
//
//import io.swagger.annotations.ApiModel;
//import io.swagger.annotations.ApiModelProperty;
//import lombok.Data;
//import java.time.LocalDate;
//import java.util.List;
//
//@Data
//@ApiModel(value = "StaffDetailVO", description = "员工详情页面VO")
//public class StaffDetailVO {
//
////    @ApiModelProperty(value = "员工ID", example = "1001")
////    private Long id;
//
//    @ApiModelProperty(value = "姓名", example = "翠花", required = true)
//    private String name;
//
//    @ApiModelProperty(value = "手机号", example = "16222522322")
//    private String mobile;
//
//    @ApiModelProperty(value = "头像", example = "https://xxx.com/avatar.png")
//    private String headImg;
//
//    @ApiModelProperty(value = "性别 0-未知 1-男 2-女", example = "1")
//    private Integer gender;
//
//    @ApiModelProperty(value = "年龄", example = "0")
//    private Integer age;
//
//    @ApiModelProperty(value = "生日", example = "2026-03-10")
//    private LocalDate birthday;
//
//    @ApiModelProperty(value = "身份证号", example = "")
//    private String idCard;
//
//    @ApiModelProperty(value = "入职日期", example = "2026-03-31")
//    private LocalDate hireDate;
//
//    @ApiModelProperty(value = "学历", example = "高中")
//    private String degree;
//
//    @ApiModelProperty(value = "毕业学校", example = "")
//    private String school;
//
//    @ApiModelProperty(value = "在职状态 1-在职 2-离职", example = "1")
//    private Integer state;
//
////    @ApiModelProperty(value = "状态名称", example = "在职")
////    private String stateName;
//
//    @ApiModelProperty(value = "个人简介", example = "暂无")
//    private String intro;
//
//    // ===================== 评价得分（雷达图：练习 → 综合） =====================
//    @ApiModelProperty(value = "评价得分-综合", example = "80")
//    private Integer scoreComprehensive;
//
//    @ApiModelProperty(value = "评价得分-效果", example = "85")
//    private Integer scoreEffect;
//
//    @ApiModelProperty(value = "评价得分-态度", example = "82")
//    private Integer scoreAttitude;
//
//    @ApiModelProperty(value = "评价得分-气氛", example = "88")
//    private Integer scoreAtmosphere;
//
//    // ===================== 所带班级列表 =====================
//    @ApiModelProperty(value = "所带班级列表")
//    private List<LessonRecordVO> teachRecordList;
//
//    // ===================== 授课记录列表 =====================
//    @ApiModelProperty(value = "授课记录列表")
//    private List<LessonRecordVO> lessonRecordList;
//}
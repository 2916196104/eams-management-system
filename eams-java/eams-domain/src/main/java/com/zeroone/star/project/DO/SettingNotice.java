package generator.domain;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.Size;
import javax.validation.constraints.NotNull;

import java.io.Serializable;

import io.swagger.annotations.ApiModelProperty;
import org.hibernate.validator.constraints.Length;

/**
* 系统设置表
* @TableName setting_notice
*/
public class SettingNotice implements Serializable {

    /**
    * 主键
    */
    @NotNull(message="[主键]不能为空")
    @ApiModelProperty("主键")
    private Long id;
    /**
    * 名称
    */
    @NotBlank(message="[名称]不能为空")
    @Size(max= 255,message="编码长度不能超过255")
    @ApiModelProperty("名称")
    @Length(max= 255,message="编码长度不能超过255")
    private String name;
    /**
    * 码
    */
    @NotBlank(message="[码]不能为空")
    @Size(max= 50,message="编码长度不能超过50")
    @ApiModelProperty("码")
    @Length(max= 50,message="编码长度不能超过50")
    private String code;
    /**
    * 微信是否开启
    */
    @ApiModelProperty("微信是否开启")
    private Integer wxOn;
    /**
    * 微信模板
    */
    @Size(max= 255,message="编码长度不能超过255")
    @ApiModelProperty("微信模板")
    @Length(max= 255,message="编码长度不能超过255")
    private String wxCode;
    /**
    * 短信是否开启
    */
    @ApiModelProperty("短信是否开启")
    private Integer smsOn;
    /**
    * 短信模板
    */
    @Size(max= 255,message="编码长度不能超过255")
    @ApiModelProperty("短信模板")
    @Length(max= 255,message="编码长度不能超过255")
    private String smsCode;
    /**
    * Email是否开启
    */
    @ApiModelProperty("Email是否开启")
    private Integer emailOn;
    /**
    * 说明
    */
    @Size(max= 255,message="编码长度不能超过255")
    @ApiModelProperty("说明")
    @Length(max= 255,message="编码长度不能超过255")
    private String info;
    /**
    * 排序
    */
    @ApiModelProperty("排序")
    private Integer sortNum;
    /**
    * 分组
    */
    @Size(max= 50,message="编码长度不能超过50")
    @ApiModelProperty("分组")
    @Length(max= 50,message="编码长度不能超过50")
    private String groupCode;
    /**
    * 参数说明
    */
    @Size(max= 255,message="编码长度不能超过255")
    @ApiModelProperty("参数说明")
    @Length(max= 255,message="编码长度不能超过255")
    private String params;
    /**
    * 消息备注信息
    */
    @Size(max= 255,message="编码长度不能超过255")
    @ApiModelProperty("消息备注信息")
    @Length(max= 255,message="编码长度不能超过255")
    private String noticeRemark;

    /**
    * 主键
    */
    private void setId(Long id){
    this.id = id;
    }

    /**
    * 名称
    */
    private void setName(String name){
    this.name = name;
    }

    /**
    * 码
    */
    private void setCode(String code){
    this.code = code;
    }

    /**
    * 微信是否开启
    */
    private void setWxOn(Integer wxOn){
    this.wxOn = wxOn;
    }

    /**
    * 微信模板
    */
    private void setWxCode(String wxCode){
    this.wxCode = wxCode;
    }

    /**
    * 短信是否开启
    */
    private void setSmsOn(Integer smsOn){
    this.smsOn = smsOn;
    }

    /**
    * 短信模板
    */
    private void setSmsCode(String smsCode){
    this.smsCode = smsCode;
    }

    /**
    * Email是否开启
    */
    private void setEmailOn(Integer emailOn){
    this.emailOn = emailOn;
    }

    /**
    * 说明
    */
    private void setInfo(String info){
    this.info = info;
    }

    /**
    * 排序
    */
    private void setSortNum(Integer sortNum){
    this.sortNum = sortNum;
    }

    /**
    * 分组
    */
    private void setGroupCode(String groupCode){
    this.groupCode = groupCode;
    }

    /**
    * 参数说明
    */
    private void setParams(String params){
    this.params = params;
    }

    /**
    * 消息备注信息
    */
    private void setNoticeRemark(String noticeRemark){
    this.noticeRemark = noticeRemark;
    }


    /**
    * 主键
    */
    private Long getId(){
    return this.id;
    }

    /**
    * 名称
    */
    private String getName(){
    return this.name;
    }

    /**
    * 码
    */
    private String getCode(){
    return this.code;
    }

    /**
    * 微信是否开启
    */
    private Integer getWxOn(){
    return this.wxOn;
    }

    /**
    * 微信模板
    */
    private String getWxCode(){
    return this.wxCode;
    }

    /**
    * 短信是否开启
    */
    private Integer getSmsOn(){
    return this.smsOn;
    }

    /**
    * 短信模板
    */
    private String getSmsCode(){
    return this.smsCode;
    }

    /**
    * Email是否开启
    */
    private Integer getEmailOn(){
    return this.emailOn;
    }

    /**
    * 说明
    */
    private String getInfo(){
    return this.info;
    }

    /**
    * 排序
    */
    private Integer getSortNum(){
    return this.sortNum;
    }

    /**
    * 分组
    */
    private String getGroupCode(){
    return this.groupCode;
    }

    /**
    * 参数说明
    */
    private String getParams(){
    return this.params;
    }

    /**
    * 消息备注信息
    */
    private String getNoticeRemark(){
    return this.noticeRemark;
    }

}

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
}

package com.zeroone.star.project.DO;

import com.baomidou.mybatisplus.annotation.TableName;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.io.Serializable;
import java.util.Date;

@Data
@TableName("material")
public class Material implements Serializable {
    @ApiModelProperty("主键")
    private Long id;
    @ApiModelProperty("所属学校")
    private Long schoolId;
    @ApiModelProperty("所属分类ID")
    private Long categoryId;
    @ApiModelProperty("分类名")
    private String categoryName;
    @ApiModelProperty("物料名称")
    private String name;
    @ApiModelProperty("库存量")
    private Integer storage;
    @ApiModelProperty("物料说明")
    private String info;
    @ApiModelProperty("封面图")
    private String cover;
    @ApiModelProperty("创建人")
    private Long creator;
    @ApiModelProperty("编辑人")
    private Long editor;
    @ApiModelProperty("添加时间")
    private Date addTime;
    @ApiModelProperty("编辑时间")
    private Date editTime;
    @ApiModelProperty("删除标记")
    private Integer deleted;
    @ApiModelProperty("启用状态")
    private Integer state;
    @ApiModelProperty("创建者所属组织ID")
    private Long orgId;
}

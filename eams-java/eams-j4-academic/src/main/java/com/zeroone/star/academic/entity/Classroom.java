package com.zeroone.star.academic.entity;

import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableLogic;
import com.baomidou.mybatisplus.annotation.TableName;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;


/**
 * <p>
 * 教室实体类
 * </p>
 * @author ab
 */
@Data
@ApiModel(value = "Classroom", description = "教室实体类")
@TableName("classroom")
public class Classroom {
    /**
     * 教室ID
     */
    @TableId(value = "id")
    @ApiModelProperty(value = "教室ID",example = "1")
    private Long id;
    /**
     * 教室名
     */
    @ApiModelProperty(value = "教室名",example = "教室101")
    private String name;
    /**
     * 教室地址
     */
    @ApiModelProperty(value = "位置",example = "宏德楼")
    private String address;
    /**
     * 教室面积
     */
    @ApiModelProperty(value = "面积（平方米）",example = "50")
    private Integer area;
    /**
     * 备注说明
     */
    @ApiModelProperty(value = "备注",example = "本部校区")
    private String remark;
    /**
     * 创建者 ID
     */
    @ApiModelProperty(value = "创建者 ID")
    private Long creator;
    /**
     * 编辑者 ID
     */
    @ApiModelProperty(value = "编辑者 ID")
    private Long editor;
    /**
     * 创建时间
     */
    @TableField("add_time")
    @ApiModelProperty(value = "创建时间")
    private LocalDateTime addTime;
    /**
     * 修改时间
     */
    @TableField("edit_time")
    @ApiModelProperty(value = "修改时间")
    private LocalDateTime editTime;
    /**
     * 逻辑删除
     */
    @TableLogic
    @TableField("deleted")
    @ApiModelProperty(value = "逻辑删除")
    private Integer deleted;
    /**
     * 学校ID
     */
    @TableField("school_id")
    @ApiModelProperty(value = "学校ID",example = "1")
    private Long schoolId;
    /**
     * 组织ID
     */
    @TableField("org_id")
    @ApiModelProperty(value = "组织ID",example = "1")
    private Long orgId;

}
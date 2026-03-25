package com.zeroone.star.project.DO.j5.courseschedule;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

@Data
@ApiModel(description = "教室DO")
public class ClassroomDO {
    @ApiModelProperty(value = "ID")
    private Long id;
    @ApiModelProperty(value = "教室名称")
    private String name;
    @ApiModelProperty(value = "地址")
    private String address;
    @ApiModelProperty(value = "面积")
    private Integer area;
    @ApiModelProperty(value = "备注")
    private String remark;
    @ApiModelProperty(value = "创建人")
    private Long creator;
    @ApiModelProperty(value = "编辑人")
    private Long editor;
    @ApiModelProperty(value = "创建时间")
    private LocalDateTime addTime;
    @ApiModelProperty(value = "编辑时间")
    private LocalDateTime editTime;
    @ApiModelProperty(value = "删除标记")
    private Integer deleted;
    @ApiModelProperty(value = "学校ID")
    private Long schoolId;
    @ApiModelProperty(value = "机构ID")
    private Long orgId;
}

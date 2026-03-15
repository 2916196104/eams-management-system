package com.zeroone.star.project.vo.j4.academic;

import com.fasterxml.jackson.annotation.JsonFormat;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

/**
 * <p>
 * 教室视图对象
 * </p>
 * @author ab
 */
@Data
@ApiModel(value = "ClassroomVO", description = "教室视图对象")
public class ClassroomVO {
    @ApiModelProperty(value = "教室ID")
    private Long id;

    @ApiModelProperty(value = "教室名")
    private String name;

    @ApiModelProperty(value = "位置")
    private String address;

    @ApiModelProperty(value = "面积（平方米）")
    private Integer area;

    @ApiModelProperty(value = "备注")
    private String remark;

    @ApiModelProperty(value = "创建者 ID")
    private Long creator;

    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    @ApiModelProperty(value = "创建时间")
    private LocalDateTime addTime;

    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    @ApiModelProperty(value = "更新时间")
    private LocalDateTime editTime;

}
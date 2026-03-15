package com.zeroone.star.project.dto.j4.academic;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotBlank;
/**
 * <p>
 * 教室数据传输对象
 * </p>
 *
 * @author ab
 */
@Data
@ApiModel(value = "ClassroomDTO", description = "教室数据传输对象")
public class ClassroomDTO {
    /**
     * 教室ID
     */
    @ApiModelProperty(value = "教室ID")
    private Long id;
    /**
     * 教室名称
     */
    @NotBlank(message = "教室名称不能为空")
    @ApiModelProperty(value = "教室名称")
    private String name;
    /**
     * 教室地址
     */
    @NotBlank(message = "教室地址不能为空")
    @ApiModelProperty(value = "教室地址")
    private String address;
    /**
     * 教室面积
     */
    @ApiModelProperty(value = "教室面积")
    private Integer area;
    /**
     * 教室描述
     */
    @ApiModelProperty(value = "教室描述")
    private String remark;
    /**
     * 学校ID
     */
    @ApiModelProperty(value = "学校ID")
    private Long schoolId;

}

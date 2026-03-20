package com.zeroone.star.project.dto.j4.academic;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.Min;
import javax.validation.constraints.NotBlank;
import java.time.LocalDateTime;

/**
 * <p>
 * 教室数据传输对象
 * </p>
 * @author ab
 */
@Data
@ApiModel(value = "ClassroomDTO", description = "教室数据传输对象")
public class ClassroomDTO {
    /**
     * 教室ID
     */
    @ApiModelProperty(value = "教室ID",example = "1")
    private Long id;
    /**
     * 教室名称
     */
    @NotBlank(message = "教室名称不能为空")
    @ApiModelProperty(value = "教室名称",required = true,example = "教学楼")
    private String name;
    /**
     * 教室地址
     */
    @NotBlank(message = "教室地址不能为空")
    @ApiModelProperty(value = "教室地址",required = true,example = "崇文楼")
    private String address;
    /**
     * 教室面积
     */
    @Min(value = 0, message = "面积不能为负数")
    @ApiModelProperty(value = "教室面积",example = "100")
    private Integer area;
    /**
     * 备注说明
     */
    @ApiModelProperty(value = "备注说明",example = "测试测试")
    private String remark;
    /**
     * 创建者 ID
     */
    @ApiModelProperty(value = "创建者 ID")
    private Long creator;
    /**
     * 创建时间
     */
    @ApiModelProperty(value = "创建时间")
    private LocalDateTime addTime;
    /**
     * 学校ID
     */
    @ApiModelProperty(value = "学校ID",example = "1")
    private Long schoolId;

}

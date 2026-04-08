package com.zeroone.star.project.dto.j5.courseschedule;

import com.fasterxml.jackson.annotation.JsonFormat;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

/**
 * <p>
 * 描述：课程状态传输对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 無名
 * @version 1.0.0
 */

@Data
public class CourseAppointStatusDTO {
    @ApiModelProperty( value = "课程编号", example = "1")
    private String id;
    @ApiModelProperty( value = "课程预约开关", example = "1")
    private String status;
    
    // 审计字段（UPDATE 操作需要）
    @ApiModelProperty(value = "更新人ID")
    private Long editor;
    
    @ApiModelProperty(value = "更新时间")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    private LocalDateTime editTime;
}
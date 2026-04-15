package com.zeroone.star.project.query.j1.console;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.EqualsAndHashCode;

/**
 * <p>
 * 描述：课表日历查询对象
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author 康康舞曲
 * @version 1.0.0
 */
@ApiModel("课表日历查询对象")
@Data
@EqualsAndHashCode(callSuper = true)
public class ScheduleCalendarQuery extends PageQuery {

    @ApiModelProperty(value = "周期-开始日期", example = "2025-03-01")
    private String dateBegin;

    @ApiModelProperty(value = "周期-结束日期", example = "2025-03-12")
    private String dateEnd;

    @ApiModelProperty(value = "班级ID", example = "5001")
    private Long classId;

    @ApiModelProperty(value = "课程ID", example = "4001")
    private Long courseId;

    @ApiModelProperty(value = "老师ID", example = "2001")
    private Long teacherId;

    @ApiModelProperty(value = "学生ID", example = "1001")
    private Long studentId;
}

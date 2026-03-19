package com.zeroone.star.project.dto.j5.courseschedule;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.EqualsAndHashCode;

import java.time.LocalDate;
import java.util.List;

/**
 * <p>
 * 描述：课次列表查询参数
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 冷月葬花魂
 * @version 1.0.0
 */
@Data
@EqualsAndHashCode(callSuper = true)
@ApiModel(value = "课次列表查询参数", description = "课次列表查询参数")
public class LessonParamDTO extends PageQuery {

    @ApiModelProperty(value = "是否试听")
    private Boolean onTrial;

    @ApiModelProperty(value = "课程ID列表")
    private List<Long> courseIds;

    @ApiModelProperty(value = "班级ID列表")
    private List<Long> classIds;

    @ApiModelProperty(value = "教师ID列表")
    private List<Long> teacherIds;

    @ApiModelProperty(value = "学员ID列表")
    private List<Long> studentIds;

    @ApiModelProperty(value = "科目ID")
    private Long subjectId;

    @ApiModelProperty(value = "教室ID")
    private Long roomId;

    @ApiModelProperty(value = "日期范围类型")
    private String dateRange;

    @ApiModelProperty(value = "开始日期")
    private LocalDate startDate;

    @ApiModelProperty(value = "结束日期")
    private LocalDate endDate;
}

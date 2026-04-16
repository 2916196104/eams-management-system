package com.zeroone.star.project.query.j7.interaction;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.EqualsAndHashCode;

import javax.validation.constraints.NotNull;

/**
 * <p>
 * 描述：作业提交记录查询对象
 * </p>
 * @author lvincent
 * @since 2026-03-15
 */
@EqualsAndHashCode(callSuper = true)
@Data
@ApiModel("作业提交记录查询对象")
public class HomeworkRecordQuery extends PageQuery {

    @ApiModelProperty(value = "作业ID（必填）", example = "1", required = true)
    @NotNull(message = "作业ID不能为空")
    private Long homeworkId;
}

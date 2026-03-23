package com.zeroone.star.project.query.j6.interact;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * 获取作业提交列表参数
 */
@Data
public class HomeworkRecordQuery extends PageQuery {
    @ApiModelProperty(value = "学生ID")
    private String student_id;
}
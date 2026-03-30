package com.zeroone.star.project.query.j6.interact;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * <p>
 * 描述：成绩列表查询对象
 * </p>
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
public class GradeRecordQuery extends PageQuery {
    @ApiModelProperty(value = "成绩单id", example = "1", required = true)
    private Long gradeId;

}

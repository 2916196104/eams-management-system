package com.zeroone.star.project.query.j4.academic;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * <p>
 * 描述：教室查询对象
 * </p>
 * @author ab
 */
@Data
public class ClassroomQuery extends PageQuery {
    /**
     * 教室名称
     */
    @ApiModelProperty(value = "教室名", example = "教学楼")
    private String name;
}

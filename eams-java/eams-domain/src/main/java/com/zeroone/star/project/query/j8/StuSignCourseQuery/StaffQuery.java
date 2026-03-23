package com.zeroone.star.project.query.j8.StuSignCourseQuery;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
@ApiModel("经手人查询条件")
public class StaffQuery extends PageQuery {

    @ApiModelProperty(value = "员工姓名", example = "张三")
    private String name;
}

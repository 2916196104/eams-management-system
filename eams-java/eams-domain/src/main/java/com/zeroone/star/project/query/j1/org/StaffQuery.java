package com.zeroone.star.project.query.j1.org;
import com.zeroone.star.project.query.PageQuery;
import com.zeroone.star.project.vo.j1.org.StaffVO;
import io.swagger.annotations.ApiModelProperty;
import io.swagger.models.auth.In;
import lombok.Data;

/**
 * <p>
 * 描述：员工查询操作
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author type-c
 * @version 1.0.0
 */
@Data
public class StaffQuery extends PageQuery {
    @ApiModelProperty(value="员工姓名",example = "管理员")
    private String name;
    @ApiModelProperty(value="员工账号",example="admin")
    private String account;
    @ApiModelProperty(value = "在职状态",example ="1" )
    private Integer statue;

}
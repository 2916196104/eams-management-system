package com.zeroone.star.project.vo.login;

import com.zeroone.star.project.utils.tree.TreeNode;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.EqualsAndHashCode;

import java.util.List;

/**
 * <p>
 * 描述：菜单树展示对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 *
 * @author 阿伟学长
 * @version 1.0.0
 */
@ApiModel("菜单树展示对象")
@EqualsAndHashCode(callSuper = true)
@Data
public class MenuTreeVO extends TreeNode {
    @ApiModelProperty(value = "菜单编号", example = "1")
    private Integer id;

    @ApiModelProperty(value = "菜单名称", example = "首页")
    private String text;

    @ApiModelProperty(value = "菜单图标", example = "dashboard")
    private String icon;

    @ApiModelProperty(value = "路由地址", example = "/dashboard")
    private String href;

    @ApiModelProperty(value = "父级菜单编号", example = "0")
    private Integer pid;

    @ApiModelProperty(value = "子菜单列表")
    public List<MenuTreeVO> getChildren() {
        return childrenElementTrans();
    }
}

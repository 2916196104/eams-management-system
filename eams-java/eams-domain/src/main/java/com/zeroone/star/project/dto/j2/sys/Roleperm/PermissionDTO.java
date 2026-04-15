package com.zeroone.star.project.dto.j2.sys.Roleperm;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.List;

/**
 * <p>
 * 权限描述对象
 * </p>
 *
 * @author Yaco
 * @since 2026-03-17
 */
@Data
@ApiModel("权限描述对象")
@AllArgsConstructor
@NoArgsConstructor
public class PermissionDTO {

    @TableId(type = IdType.AUTO)
    @ApiModelProperty(value = "权限ID（自增主键），修改操作时必须传", example = "1")
    private Long id;

    /**
     * 菜单名称
     */
    @ApiModelProperty(value = "菜单名称", example = "教室管理")
    private String name;

    /**
     * 父类id
     * 注意：数据库中是 varchar，建议用 String 接收，避免父ID为非数字或超长ID时溢出
     */
    @TableField("parent_id")
    @ApiModelProperty(value = "父类ID（顶级菜单填null或空字符串）", example = "10")
    private String parentId;

    /**
     * 链接
     */
    @ApiModelProperty(value = "接口请求URL", example = "/common/classroom/save")
    private String url;

    /**
     * 权限编码
     */
    @ApiModelProperty(value = "权限唯一标识编码", example = "classroommanage")
    private String code;

    /**
     * 接口路径
     */
    @ApiModelProperty(value = "前端路由路径", example = "/edu/classroom")
    private String path;

    /**
     * 是否启用
     */
    @ApiModelProperty(value = "是否启用 1表示启用 0表示禁用", example = "1", allowableValues = "0,1")
    private Short enabled;

    /**
     * 分组名称
     */
    @TableField("group_name")
    @ApiModelProperty(value = "分组名", example = "教务管理")
    private String groupName;


}

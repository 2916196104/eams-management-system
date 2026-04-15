package com.zeroone.star.project.query.j1.console;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.EqualsAndHashCode;

/**
 * <p>
 * 描述：控制台公告查询对象
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author 康康舞曲
 * @version 1.0.0
 */
@ApiModel("控制台公告查询对象")
@Data
@EqualsAndHashCode(callSuper = true)
public class AnnouncementQuery extends PageQuery {

    @ApiModelProperty(value = "标题（模糊查询）", example = "清明节")
    private String title;
}

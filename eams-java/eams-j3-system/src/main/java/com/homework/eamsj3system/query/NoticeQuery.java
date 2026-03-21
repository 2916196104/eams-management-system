package com.homework.eamsj3system.query;

import io.swagger.v3.oas.annotations.media.Schema;
import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

/**
 * <p>
 * 内部公告查询对象
 * </p>
 * @author 阿伟
 */
@Getter
@Setter
@ToString
public class NoticeQuery {

    @Schema(description = "页码")
    private Integer pageNum = 1;

    @Schema(description = "每页显示条数")
    private Integer pageSize = 10;

    @Schema(description = "公告标题（模糊查询）")
    private String title;

    @Schema(description = "公告类型（1-通知 2-公告 3-通告）")
    private Integer type;

    @Schema(description = "发布人")
    private String publisher;

    @Schema(description = "是否置顶（0-否 1-是）")
    private Integer isTop;

    @Schema(description = "是否启用（0-禁用 1-启用）")
    private Integer isEnable;
}

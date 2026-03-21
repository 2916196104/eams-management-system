package com.homework.eamsj3system.vo;

import io.swagger.v3.oas.annotations.media.Schema;
import lombok.Data;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * <p>
 * 内部公告视图对象
 * </p>
 * @author 阿伟
 */
@Data
public class NoticeVO implements Serializable {

    private static final long serialVersionUID = 1L;

    @Schema(description = "公告 ID")
    private Long id;

    @Schema(description = "公告标题")
    private String title;

    @Schema(description = "公告内容")
    private String content;

    @Schema(description = "公告类型（1-通知 2-公告 3-通告）")
    private Integer type;

    @Schema(description = "发布人")
    private String publisher;

    @Schema(description = "发布时间")
    private LocalDateTime publishTime;

    @Schema(description = "是否置顶（0-否 1-是）")
    private Integer isTop;

    @Schema(description = "是否启用（0-禁用 1-启用）")
    private Integer isEnable;

    @Schema(description = "创建时间")
    private LocalDateTime createTime;

    @Schema(description = "更新时间")
    private LocalDateTime updateTime;
}

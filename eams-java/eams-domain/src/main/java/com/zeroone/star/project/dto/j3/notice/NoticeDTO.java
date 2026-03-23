package com.zeroone.star.project.dto.j3.notice;

import lombok.Data;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * <p>
 * 内部公告数据传输对象
 * </p>
 * @author 阿伟
 */
@Data
public class NoticeDTO implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 公告 ID
     */
    private Long id;

    /**
     * 公告标题
     */
    private String title;

    /**
     * 公告内容
     */
    private String content;

    /**
     * 公告类型（1-通知 2-公告 3-通告）
     */
    private Integer type;

    /**
     * 发布人
     */
    private String publisher;

    /**
     * 发布时间
     */
    private LocalDateTime publishTime;

    /**
     * 是否置顶（0-否 1-是）
     */
    private Integer isTop;

    /**
     * 是否启用（0-禁用 1-启用）
     */
    private Integer isEnable;

    /**
     * 创建时间
     */
    private LocalDateTime createTime;

    /**
     * 更新时间
     */
    private LocalDateTime updateTime;
}

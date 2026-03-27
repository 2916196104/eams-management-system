package com.zeroone.star.project.dto.j3.notice;

import lombok.Data;

import java.io.Serializable;

/**
 * <p>
 * 内部公告保存对象
 * </p>
 * @author 阿伟
 */
@Data
public class NoticeDTO implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 公告 ID，新增时为空，修改时必填
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
     * 编辑人
     */
    private Long editor;
}

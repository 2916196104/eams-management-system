package com.zeroone.star.project.vo.j3.notice;

import lombok.Data;

import java.io.Serializable;
import java.util.Date;

/**
 * <p>
 * 内部公告展示对象
 * </p>
 * @author 阿伟
 */
@Data
public class NoticeVO implements Serializable {

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
     * 浏览次数
     */
    private Integer viewNum;

    /**
     * 创建人
     */
    private Long creator;

    /**
     * 编辑人
     */
    private Long editor;

    /**
     * 添加时间
     */
    private Date addTime;

    /**
     * 编辑时间
     */
    private Date editTime;
}

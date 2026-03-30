package com.zeroone.star.sysmanager.service;


import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.dto.j8.sysmanager.NoticeDTO;
import com.zeroone.star.project.query.j8.sysmanager.NoticeQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j8.sysmanager.NoticeVO;
import cn.hutool.db.PageResult;
import com.zeroone.star.sysmanager.entity.Notice;

import java.util.List;

/**
 * 内部公告 Service 接口
 */
public interface InternalNoticeService extends IService<Notice> {

    /**
     * 获取公告列表（条件 + 分页）
     * @param query 查询条件
     * @return 分页结果
     */
    PageResult<NoticeVO> getNoticeList(NoticeQuery query);

    /**
     * 获取公告详情
     * @param id 公告 ID
     * @return 公告详情
     */
    NoticeVO getNoticeDetail(Long id);

    /**
     * 保存公告（新增/修改）
     * @param dto 公告数据
     * @return 是否成功
     */
    Boolean saveNotice(NoticeDTO dto);
}
package com.zeroone.star.sysmanager.service.impl;

import cn.hutool.db.PageResult;
import com.zeroone.star.project.dto.j8.sysmanager.NoticeDTO;
import com.zeroone.star.project.query.j8.sysmanager.NoticeQuery;
import com.zeroone.star.project.vo.j8.sysmanager.NoticeVO;
import com.zeroone.star.sysmanager.entity.Notice;
import com.zeroone.star.sysmanager.mapper.NoticeMapper;

import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.sysmanager.service.InternalNoticeService;
import org.springframework.stereotype.Service;

/**
 * <p>
 * 公告 服务实现类
 * </p>
 *
 * @author dabidai
 * @since 2026-03-14
 */
@Service
public class NoticeServiceImpl implements InternalNoticeService {

    @Override
    public PageResult<NoticeVO> getNoticeList(NoticeQuery query) {
        return null;
    }

    @Override
    public NoticeVO getNoticeDetail(Long id) {
        return null;
    }

    @Override
    public Boolean saveNotice(NoticeDTO dto) {
        return null;
    }
}

package com.zeroone.star.sysmanager.service.impl;

import com.zeroone.star.sysmanager.entity.Notice;
import com.zeroone.star.sysmanager.mapper.NoticeMapper;
import com.zeroone.star.sysmanager.service.INoticeService;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
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
public class NoticeServiceImpl extends ServiceImpl<NoticeMapper, Notice> implements INoticeService {
}

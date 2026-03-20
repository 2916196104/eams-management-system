package com.zeroone.star.sysmanager.service;

import com.zeroone.star.sysmanager.entity.Notice;
import com.baomidou.mybatisplus.extension.service.IService;
import org.springframework.stereotype.Service;

/**
 * <p>
 * 公告 服务类
 * </p>
 *
 * @author dabidai
 * @since 2026-03-14
 */

public interface INoticeService extends IService<Notice> {
    // 这里可以定义你自己特有的复杂功能，比如我们之前定义的：
    // void deleteMyNotice(List<Long> ids);
    // 但因为我们要做的仅仅是根据ID删除，IService自带了这个功能，所以这里甚至可以留空！
}

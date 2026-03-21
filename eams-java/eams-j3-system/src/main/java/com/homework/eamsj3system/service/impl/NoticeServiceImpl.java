package com.homework.eamsj3system.service.impl;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.homework.eamsj3system.dto.NoticeDTO;
import com.homework.eamsj3system.entity.Notice;
import com.homework.eamsj3system.mapper.NoticeMapper;
import com.homework.eamsj3system.query.NoticeQuery;
import com.homework.eamsj3system.service.INoticeService;
import com.homework.eamsj3system.vo.NoticeVO;
import org.springframework.stereotype.Service;

import java.util.List;

/**
 * <p>
 * 内部公告 服务实现类（框架）
 * </p>
 * @author 阿伟
 */
@Service
public class NoticeServiceImpl extends ServiceImpl<NoticeMapper, Notice> implements INoticeService {

    @Override
    public Page<NoticeVO> pageList(NoticeQuery query) {
        // TODO: 待实现分页查询逻辑
        return null;
    }

    @Override
    public NoticeVO getById(Long id) {
        // TODO: 待实现获取详情逻辑
        return null;
    }

    @Override
    public boolean saveNotice(NoticeDTO noticeDTO) {
        // TODO: 待实现保存逻辑
        return false;
    }

    @Override
    public boolean deleteByIds(List<Long> ids) {
        // TODO: 待实现删除逻辑
        return false;
    }
}

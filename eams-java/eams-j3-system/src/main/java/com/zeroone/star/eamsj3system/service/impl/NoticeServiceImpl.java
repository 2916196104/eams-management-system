package com.zeroone.star.eamsj3system.service.impl;

import cn.hutool.core.bean.BeanUtil;
import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.core.conditions.update.LambdaUpdateWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.eamsj3system.mapper.NoticeMapper;
import com.zeroone.star.eamsj3system.service.INoticeService;
import com.zeroone.star.project.DO.Notice;
import com.zeroone.star.project.dto.j3.notice.NoticeDTO;
import com.zeroone.star.project.query.j3.notice.NoticeQuery;
import com.zeroone.star.project.vo.j3.notice.NoticeVO;
import org.springframework.stereotype.Service;
import org.springframework.util.StringUtils;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

/**
 * <p>
 * 内部公告 服务实现类
 * </p>
 * @author 阿伟
 */
@Service
public class NoticeServiceImpl extends ServiceImpl<NoticeMapper, Notice> implements INoticeService {

    @Override
    public Page<NoticeVO> pageList(NoticeQuery query) {
        Page<Notice> page = new Page<>(query.getPageNum(), query.getPageSize());
        LambdaQueryWrapper<Notice> wrapper = new LambdaQueryWrapper<Notice>()
                .eq(Notice::getDeleted, 0)
                .like(StringUtils.hasText(query.getTitle()), Notice::getTitle, query.getTitle())
                .eq(query.getCreator() != null, Notice::getCreator, query.getCreator())
                .orderByDesc(Notice::getAddTime)
                .orderByDesc(Notice::getId);
        Page<Notice> noticePage = page(page, wrapper);
        Page<NoticeVO> result = new Page<>(noticePage.getCurrent(), noticePage.getSize(), noticePage.getTotal());
        result.setPages(noticePage.getPages());

        List<NoticeVO> records = BeanUtil.copyToList(noticePage.getRecords(), NoticeVO.class);
        result.setRecords(records);
        return result;
    }

    @Override
    public NoticeVO getById(Long id) {
        Notice notice = getOne(new LambdaQueryWrapper<Notice>()
                .eq(Notice::getId, id)
                .eq(Notice::getDeleted, 0));
        if (notice == null) {
            throw new IllegalArgumentException("公告不存在");
        }
        return BeanUtil.copyProperties(notice, NoticeVO.class);
    }

    @Override
    public String saveNotice(NoticeDTO noticeDTO) {
        Date now = new Date();

        if (noticeDTO.getId() == null) {
            return createNotice(noticeDTO, now);
        }

        return updateNotice(noticeDTO, now);
    }

    @Override
    public String deleteByIds(List<Long> ids) {
        if (ids == null || ids.isEmpty()) {
            throw new IllegalArgumentException("请选择要删除的公告");
        }

        Notice notice = new Notice();
        notice.setDeleted(1);
        notice.setEditTime(new Date());
        boolean updated = update(notice, new LambdaUpdateWrapper<Notice>()
                .in(Notice::getId, ids)
                .eq(Notice::getDeleted, 0));
        if (!updated) {
            throw new IllegalStateException("删除公告失败");
        }
        return "删除公告成功";
    }

    private String createNotice(NoticeDTO noticeDTO, Date now) {
        Notice notice = BeanUtil.copyProperties(noticeDTO, Notice.class);
        notice.setViewNum(0);
        notice.setDeleted(0);
        notice.setCreator(noticeDTO.getEditor());
        notice.setAddTime(now);
        notice.setEditTime(now);
        boolean saved = save(notice);
        if (!saved) {
            throw new IllegalStateException("保存公告失败");
        }
        return "保存公告成功";
    }

    private String updateNotice(NoticeDTO noticeDTO, Date now) {
        Notice exist = lambdaQuery()
                .eq(Notice::getId, noticeDTO.getId())
                .eq(Notice::getDeleted, 0)
                .one();
        if (exist == null) {
            throw new IllegalArgumentException("公告不存在");
        }

        if (noticeDTO.getTitle() != null) {
            exist.setTitle(noticeDTO.getTitle());
        }
        if (noticeDTO.getContent() != null) {
            exist.setContent(noticeDTO.getContent());
        }
        if (noticeDTO.getEditor() != null) {
            exist.setEditor(noticeDTO.getEditor());
        }
        exist.setEditTime(now);

        boolean updated = updateById(exist);
        if (!updated) {
            throw new IllegalStateException("保存公告失败");
        }
        return "保存公告成功";
    }
}

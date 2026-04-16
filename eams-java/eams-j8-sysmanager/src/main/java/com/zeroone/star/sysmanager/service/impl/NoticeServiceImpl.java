package com.zeroone.star.sysmanager.service.impl;

import cn.hutool.core.bean.BeanUtil;

import cn.hutool.db.PageResult;
import com.alibaba.cloud.commons.lang.StringUtils;
import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.j8.sysmanager.NoticeDTO;
import com.zeroone.star.project.query.j8.sysmanager.NoticeQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j8.sysmanager.NoticeVO;
import com.zeroone.star.sysmanager.entity.Notice;
import com.zeroone.star.sysmanager.exception.BusinessException;
import com.zeroone.star.sysmanager.mapper.NoticeMapper;
import com.zeroone.star.sysmanager.service.INoticeService;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.sysmanager.service.InternalNoticeService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;
import java.time.LocalDateTime;
import java.util.List;
import java.util.stream.Collectors;

@Service
public class NoticeServiceImpl extends ServiceImpl<NoticeMapper, Notice> implements InternalNoticeService {

    @Override
    public PageResult<NoticeVO> getNoticeList(NoticeQuery query) {
        // 1. 分页查询
        Page<Notice> page = new Page<>(
                query.getPageNum() != null ? query.getPageNum() : 1,
                query.getPageSize() != null ? query.getPageSize() : 10
        );

        LambdaQueryWrapper<Notice> wrapper = new LambdaQueryWrapper<>();
        wrapper.like(StringUtils.isNotBlank(query.getTitle()), Notice::getTitle, query.getTitle());
        wrapper.eq(Notice::getDeleted, false);
        wrapper.orderByDesc(Notice::getAddTime);

        IPage<Notice> resultPage = this.page(page, wrapper);

        // 2. 实体转 VO
        List<NoticeVO> voList = resultPage.getRecords()
                .stream()
                .map(n -> BeanUtil.toBean(n, NoticeVO.class))
                .collect(Collectors.toList());

        // 3. 创建 PageResult（传分页参数）
        PageResult<NoticeVO> pageResult = new PageResult<>(
                (int) resultPage.getCurrent(),           // 当前页
                (int) resultPage.getSize(),              // 每页大小
                (int) resultPage.getTotal()              // 总条数
        );

        // 4. 把数据加进去
        pageResult.addAll(voList);

        return pageResult;
    }

    @Override
    public NoticeVO getNoticeDetail(Long id) {
        Notice notice = this.getById(id);
        if (notice == null) {
            throw new BusinessException("公告不存在，ID:" + id);
        }
        // Notice → NoticeVO
        return BeanUtil.toBean(notice, NoticeVO.class);
    }

    @Autowired
    private HttpServletRequest request;

    @Override
    public Boolean saveNotice(NoticeDTO dto) {
        Notice notice = BeanUtil.toBean(dto, Notice.class);

        // 从 Session 获取当前用户 ID
        HttpSession session = request.getSession();
        Long userId = (Long) session.getAttribute("userId");

        if (notice.getId() == null) {
            notice.setAddTime(LocalDateTime.now());
            notice.setCreator(userId != null ? userId : 1L);  // 没登录就默认 1
            notice.setDeleted(false);
            return this.save(notice);
        } else {
            notice.setEditTime(LocalDateTime.now());
            notice.setEditor(userId != null ? userId : 1L);
            return this.updateById(notice);
        }
    }
}
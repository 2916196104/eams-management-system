package com.zeroone.star.eamsj3system.service;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.dto.j3.notice.NoticeDTO;
import com.zeroone.star.project.DO.Notice;
import com.zeroone.star.project.query.j3.notice.NoticeQuery;
import com.zeroone.star.project.vo.j3.notice.NoticeVO;

import java.util.List;

/**
 * <p>
 * 内部公告 服务接口
 * </p>
 * @author 阿伟
 */
public interface INoticeService extends IService<Notice> {

    /**
     * 分页查询公告列表
     * @param query 查询条件
     * @return 返回分页数据
     */
    Page<NoticeVO> pageList(NoticeQuery query);

    /**
     * 根据 ID 获取公告详情
     * @param id 公告 ID
     * @return 返回公告详情
     */
    NoticeVO getById(Long id);

    /**
     * 保存公告
     * @param noticeDTO 公告数据传输对象
     * @return 保存结果
     */
    String saveNotice(NoticeDTO noticeDTO);

    /**
     * 删除公告（支持批量删除）
     * @param ids 公告 ID 列表
     * @return 删除结果
     */
    String deleteByIds(List<Long> ids);
}

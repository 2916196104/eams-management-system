package com.zeroone.star.eamsj3system.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.DO.SettingNotice;
import com.zeroone.star.project.dto.j3.notice.NoticeSettingDTO;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j3.notice.NoticeSettingListVO;

import java.util.List;

/**
 * 通知设置服务
 */
public interface ISettingNoticeService extends IService<SettingNotice> {
    /**
     * 获取通知设置
     * @return 通知设置
     */
    JsonVO<NoticeSettingDTO> getNoticeSettingList();

    /**
     * 保存通知设置
     * @param dto 通知设置DTO
     * @return 保存结果
     */
    JsonVO<NoticeSettingDTO> saveNoticeSetting(NoticeSettingDTO dto);
}
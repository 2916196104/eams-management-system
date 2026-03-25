package com.zeroone.star.project.j3.notice;

import com.zeroone.star.project.dto.j3.notice.NoticeSettingDTO;
import com.zeroone.star.project.vo.JsonVO;

/**
 * <p>
 * 描述：通知设置模块模块Api
 * </p>
 *
 * @author chenyixing
 * @version 1.0.0
 */
public interface NoticeApis {
    //  获取通知设置
    JsonVO<NoticeSettingDTO> queryNoticeSettingList();



    //  保存通知设置
    JsonVO<NoticeSettingDTO> saveNoticeSetting(NoticeSettingDTO noticeSettingDTO);




}

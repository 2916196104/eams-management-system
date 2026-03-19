package com.zeroone.star.project.j3.notice;

import com.zeroone.star.project.dto.j3.noticsetting.NoticeSettingDTO;
import com.zeroone.star.project.dto.j3.noticsetting.PageDTO;
import com.zeroone.star.project.query.j3.noticesetting.NoticeSettingQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j3.system.NoticeSettingDetailVO;
import com.zeroone.star.project.vo.j3.system.NoticeSettingListVO;

import java.util.List;

/**
 * <p>
 * 描述：通知设置模块模块Api
 * </p>
 *
 * @author chenyixing
 * @version 1.0.0
 */
public interface NoticeApis {
    //  获取通知设置列表（条件 + 分页）
    JsonVO<NoticeSettingDTO> queryNoticeSettingList(NoticeSettingQuery noticeSettingQuery);



    //  保存通知设置
    JsonVO<String> saveNoticeSetting(NoticeSettingDTO noticeSettingDTO);





}

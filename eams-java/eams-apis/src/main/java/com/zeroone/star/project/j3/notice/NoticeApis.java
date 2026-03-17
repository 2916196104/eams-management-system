package com.zeroone.star.project.j3.notice;

import com.zeroone.star.project.dto.j3.noticsetting.NoticeSettingDTO;
import com.zeroone.star.project.dto.j3.noticsetting.PageDTO;
import com.zeroone.star.project.query.j3.noticesetting.NoticeSettingQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j3.system.NoticeSettingDetailVO;
import com.zeroone.star.project.vo.j3.system.NoticeSettingListVO;

import java.util.List;

public interface NoticeApis {
    //  获取通知设置列表（条件 + 分页）
    JsonVO<PageDTO<NoticeSettingDTO>> queryNoticeSettingList(NoticeSettingQuery noticeSettingQuery);



    //  保存通知设置
    JsonVO<String> saveNoticeSetting(NoticeSettingDTO noticeSettingDTO);





}

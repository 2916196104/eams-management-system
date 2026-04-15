package com.zeroone.star.eamsj3system.service.impl;

import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.eamsj3system.mapper.SettingNoticeMapper;
import com.zeroone.star.eamsj3system.service.ISettingNoticeService;
import com.zeroone.star.project.DO.SettingNotice;
import com.zeroone.star.project.dto.j3.notice.NoticeSettingDTO;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j3.notice.NoticeSettingListVO;
import org.springframework.beans.BeanUtils;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.stream.Collectors;

/**
 * 通知设置服务实现
 */
@Service
public class SettingNoticeServiceImpl extends ServiceImpl<SettingNoticeMapper, SettingNotice> implements ISettingNoticeService {

    @Override
    public JsonVO<NoticeSettingDTO> getNoticeSettingList() {
        // 查询所有数据
        List<SettingNotice> list = list();
        
        // 创建DTO对象
        NoticeSettingDTO dto = new NoticeSettingDTO();
        
        // 无论是否有数据，都设置所有必需的属性
        if (!list.isEmpty()) {
            SettingNotice item = list.get(0);
            dto.setId(item.getId());
            dto.setEmailon(item.getEmailOn() != null && item.getEmailOn() == 1);
            dto.setWechaton(item.getWxOn() != null && item.getWxOn() == 1);
            dto.setMessageon(item.getSmsOn() != null && item.getSmsOn() == 1);
            dto.setNoticewechatId(item.getWxCode());
            dto.setMessageId_eg(item.getSmsCode());
            dto.setTips(item.getInfo());
        } else {
            // 即使没有数据，也设置所有必需的属性为默认值
            dto.setId(0L);
            dto.setEmailon(false);
            dto.setWechaton(false);
            dto.setMessageon(false);
            dto.setNoticewechatId("");
            dto.setMessageId_eg("");
            dto.setTips("");
        }

        // 构建返回结果
        JsonVO<NoticeSettingDTO> result = new JsonVO<>();
        result.setData(dto);
        result.setMessage("获取通知设置成功");
        result.setCode(200);
        return result;
    }

    @Override
    public JsonVO<NoticeSettingDTO> saveNoticeSetting(NoticeSettingDTO dto) {
        // 转换DTO为实体
        SettingNotice settingNotice = new SettingNotice();
        settingNotice.setId(dto.getId());
        // 设置必填字段的默认值
        settingNotice.setName("通知设置");
        settingNotice.setCode("notice_setting");
        // 设置其他字段
        settingNotice.setEmailOn(dto.isEmailon() ? 1 : 0);
        settingNotice.setWxOn(dto.isWechaton() ? 1 : 0);
        settingNotice.setSmsOn(dto.isMessageon() ? 1 : 0);
        settingNotice.setWxCode(dto.getNoticewechatId());
        settingNotice.setSmsCode(dto.getMessageId_eg());
        settingNotice.setInfo(dto.getTips());

        // 保存或更新数据
        boolean success = saveOrUpdate(settingNotice);

        // 构建返回结果
        JsonVO<NoticeSettingDTO> result = new JsonVO<>();
        if (success) {
            result.setData(dto);
            result.setMessage("保存通知设置成功");
            result.setCode(200);
        } else {
            result.setData(dto);
            result.setMessage("保存通知设置失败");
            result.setCode(500);
        }
        return result;
    }
}
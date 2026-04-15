package com.zeroone.star.project.vo.j3.notice;

import com.zeroone.star.project.dto.j3.notice.NoticeSettingDTO;
import lombok.Data;

import java.util.List;

@Data
public class NoticeSettingListVO {
    private Long id;
    private String name;
    private String code;
    private Boolean wxOn;
    private Boolean smsOn;
    private Boolean emailOn;
    private String info;
    private Integer sortNum;
    private String groupCode;
    private List<NoticeSettingDTO> list;

    // getter和setter
    public List<NoticeSettingDTO> getList() {
        return list;
    }

    public void setList(List<NoticeSettingDTO> list) {
        this.list = list;
    }
}

package com.zeroone.star.project.vo.j3.notice;

import lombok.Data;

@Data
public class NoticeSettingDetailVO {
    private Long id;
    private String name;
    private String code;
    private Boolean wxOn;
    private Boolean smsOn;
    private Boolean emailOn;
    private String info;
    private Integer sortNum;
    private String groupCode;
    private String smsCode;
    private String wxCode;
    private String params;

}

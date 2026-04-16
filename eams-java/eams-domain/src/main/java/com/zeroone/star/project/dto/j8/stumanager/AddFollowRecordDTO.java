package com.zeroone.star.project.dto.j8.stumanager;

import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.time.LocalDateTime;


public class AddFollowRecordDTO {
    @ApiModelProperty(value = "学员ID", example = "1", required = true)
    private Long studentId;

    @ApiModelProperty(value = "跟进内容", example = "学员对课程感兴趣，希望了解更多详情")
    private String info;

    @ApiModelProperty(value = "联系时间", example = "2024-01-15T10:30:00")
    private LocalDateTime contactTime;

    @ApiModelProperty(value = "下次联系时间", example = "2024-01-20T14:00:00")
    private LocalDateTime contactNextTime;

    @ApiModelProperty(value = "联系方式类型(1:电话 2:微信 3:面谈 4:其他)", example = "1")
    private Integer contactType;

    @ApiModelProperty(value = "联系电话", example = "13800138000")
    private String contactPhone;

    @ApiModelProperty(value = "跟进阶段(1:初次接触 2:意向确认 3:试听安排 4:报名跟进 5:其他)", example = "1")
    private Integer stage;

    public Long getStudentId() {
        return studentId;
    }

    public void setStudentId(Long studentId) {
        this.studentId = studentId;
    }

    public String getInfo() {
        return info;
    }

    public void setInfo(String info) {
        this.info = info;
    }

    public LocalDateTime getContactTime() {
        return contactTime;
    }

    public void setContactTime(LocalDateTime contactTime) {
        this.contactTime = contactTime;
    }

    public LocalDateTime getContactNextTime() {
        return contactNextTime;
    }

    public void setContactNextTime(LocalDateTime contactNextTime) {
        this.contactNextTime = contactNextTime;
    }

    public Integer getContactType() {
        return contactType;
    }

    public void setContactType(Integer contactType) {
        this.contactType = contactType;
    }

    public String getContactPhone() {
        return contactPhone;
    }

    public void setContactPhone(String contactPhone) {
        this.contactPhone = contactPhone;
    }

    public Integer getStage() {
        return stage;
    }

    public void setStage(Integer stage) {
        this.stage = stage;
    }
}
package com.zeroone.star.project.vo.j8.stumanager;

import java.time.LocalDateTime;

public class ContactRecordVO {
    private Long id;
    private Long studentId;
    private String info;
    private LocalDateTime contactTime;
    private LocalDateTime contactNextTime;
    private Integer contactType;
    private String contactPhone;
    private Long creator;
    private LocalDateTime addTime;
    private Integer stage;
    
    public Long getId() {
        return id;
    }
    
    public void setId(Long id) {
        this.id = id;
    }
    
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
    
    public Long getCreator() {
        return creator;
    }
    
    public void setCreator(Long creator) {
        this.creator = creator;
    }
    
    public LocalDateTime getAddTime() {
        return addTime;
    }
    
    public void setAddTime(LocalDateTime addTime) {
        this.addTime = addTime;
    }
    
    public Integer getStage() {
        return stage;
    }
    
    public void setStage(Integer stage) {
        this.stage = stage;
    }
}
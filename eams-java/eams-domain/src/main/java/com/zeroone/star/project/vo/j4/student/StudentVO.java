package com.zeroone.star.project.vo.j4.student;
//StudentVO：用于列表显示，包含头像、剩余课时、当前教程名。

public class StudentVO {
    /**
     * 头像
     */
    private String avatar;

    /**
     * 剩余课时
     */
    private Integer remainingHours;

    /**
     * 当前教程名
     */
    private String currentTutorialName;

    public String getAvatar() {
        return avatar;
    }

    public void setAvatar(String avatar) {
        this.avatar = avatar;
    }

    public Integer getRemainingHours() {
        return remainingHours;
    }

    public void setRemainingHours(Integer remainingHours) {
        this.remainingHours = remainingHours;
    }

    public String getCurrentTutorialName() {
        return currentTutorialName;
    }

    public void setCurrentTutorialName(String currentTutorialName) {
        this.currentTutorialName = currentTutorialName;
    }
}

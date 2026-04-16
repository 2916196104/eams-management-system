package com.zeroone.star.project.vo.j9.operation;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.time.LocalDateTime;

/**
 * 积分记录列表返回 VO
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
@ApiModel(description = "积分记录列表返回数据")
public class StudentCreditLogVO {

    //@ApiModelProperty(value = "序号", example = "1")
    //private Long id; // 前端用此ID做序号自增，无需单独返回序号

    @ApiModelProperty(value = "学生姓名", example = "张三")
    private String studentName;

    @ApiModelProperty(value = "变动原因", example = "课程打卡")
    private String changeReason;

    @ApiModelProperty(value = "变动积分", example = "+500")
    private String changeCredit; // 带符号展示（+增加/-减少）

    @ApiModelProperty(value = "剩余积分", example = "1200")
    private Integer currentCredit;

    @ApiModelProperty(value = "说明", example = "日常课程打卡奖励")
    private String remark;

    @ApiModelProperty(value = "变动时间", example = "2026-03-15 10:30:00")
    private LocalDateTime changeTime;

    // 辅助方法：自动给变动积分加正负号（无需前端处理）
    public void setChangeCredit(Integer credit) {
        if (credit == null) {
            this.changeCredit = "";
            return;
        }
        this.changeCredit = credit > 0 ? "+" + credit : credit.toString();
    }
}
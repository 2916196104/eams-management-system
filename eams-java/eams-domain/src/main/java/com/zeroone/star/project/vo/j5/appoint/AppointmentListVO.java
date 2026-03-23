package com.zeroone.star.project.vo.j5.appoint;
import com.fasterxml.jackson.annotation.JsonFormat;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * <p>
 * 预约列表分页展示对象
 * </p>
 *
 * @author makise
 * @since 2026/3/23
 */

@Data
@ApiModel(value = "AppointmentListVO", description = "预约列表分页展示视图对象")
public class AppointmentListVO implements Serializable {

    private static final long serialVersionUID = 1L;

    // ================= 隐形控制字段 =================

    @ApiModelProperty(value = "主键ID(勾选复选框、确认/取消预约时必须传给后台)", example = "101")
    private Long id;

    @ApiModelProperty(value = "状态枚举值(用于前端判断按钮显隐，如1-待审, 2-通过, 3-驳回)", example = "2")
    private Integer verifyState;

    @ApiModelProperty(value = "课程ID(用于点击蓝色的课程名称跳转到课程详情页)", example = "888")
    private Long courseId;

    // ================= 页面展示字段  =================

    @ApiModelProperty(value = "学生姓名", example = "张小明")
    private String studentName;

    @ApiModelProperty(value = "手机号", example = "13800000001")
    private String mobile;

    @ApiModelProperty(value = "课程名称", example = "钢琴入门课")
    private String courseName;

    @ApiModelProperty(value = "上课时间", example = "2026-01-19 11:00:00")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    private LocalDateTime lessonTime;

    @ApiModelProperty(value = "预约时间", example = "2026-01-17 14:41:00")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    private LocalDateTime addTime;

    @ApiModelProperty(value = "状态文本", example = "审核通过")
    private String verifyStateText;

    @ApiModelProperty(value = "审核人姓名", example = "张三")
    private String verifyStaffName;
}
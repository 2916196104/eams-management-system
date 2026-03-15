package com.zeroone.star.project.dto.j4.student;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import java.time.LocalDateTime;

/**
 * <p>
 * 描述：跟进记录传输对象
 */
@Data
public class FollowUpDTO {

    @ApiModelProperty(value = "跟进记录ID，修改时必传，新增不传", example = "2008418408985583618")
    private Long id;

    @ApiModelProperty(value = "学员ID", required = true, example = "2008418408985583617")
    private Long studentId;

    @ApiModelProperty(value = "学员姓名 (只读/展示用)", example = "张三")
    private String studentName;

    @ApiModelProperty(value = "跟进内容", required = true, example = "与客户沟通了课程细节，客户意向强烈")
    private String content;

    @ApiModelProperty(value = "跟进方式 (1:电话 2:微信 3:面谈 4:其他)", required = true, example = "1")
    private Integer followType;

    @ApiModelProperty(value = "跟进结果 (1:有效 2:无效 3:待跟进)", example = "1")
    private Integer resultType;

    @ApiModelProperty(value = "下次跟进时间", example = "2026-03-20 10:00:00")
    private LocalDateTime nextFollowTime;

    @ApiModelProperty(value = "跟进人ID", example = "1001")
    private Long followUserId;

    @ApiModelProperty(value = "跟进人姓名", example = "李老师")
    private String followUserName;

    @ApiModelProperty(value = "创建时间", example = "2026-03-15 16:20:00")
    private LocalDateTime createTime;
}
package com.zeroone.star.project.dataobject.j6.interact;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * <p>
 * 描述:  成绩对象，用于互动模块-成绩单功能
 * </p>
 *
 * @author upup
 * @version 1.0.0
 * @since 2026-03-21
 */

@Data
@TableName("grade_record")
public class GradeRecordDO implements Serializable {
    /**
     * 主键ID
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;
    /**
     * 考核项id
     */

    private Long gradeId;
    /**
     * 学生id
     */
    private Long studentId;
    /**
     *  分数
     * */
    private Integer score;
    /**
     * 添加时间
     */
    private LocalDateTime addTime;

    /**
     * 添加人
     */
    private Long creator;
}

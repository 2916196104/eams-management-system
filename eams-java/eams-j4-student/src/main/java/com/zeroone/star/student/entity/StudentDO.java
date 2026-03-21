package com.zeroone.star.student.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;
import java.time.LocalDate;
import java.time.LocalDateTime;

@Data
@TableName("student")
public class StudentDO {
    @TableId(type = IdType.AUTO)
    private Long id;
    private Long userId;
    private Integer familyRel;
    private Integer asDefault;
    private Long schoolId;
    private String name;
    private Integer deleted;
    private Integer stage;
    private Integer gender;
    private LocalDate birthday;
    private String headImg;
    private Long joinWay;
    private String remark;
    private LocalDate graduationDate;
    private String graduationReason;
    private LocalDateTime addTime;
    private Long counselor;
    private Long creator;
    private Long editor;
    private LocalDateTime editTime;
    private String idcard;
    private LocalDateTime redpointGrade;
    private LocalDateTime redpointEvaluate;
    private Integer grade;
    private LocalDate joinDate;
    private Long wxAccessId;
    private Integer credit;
    private Long orgId;
    private Integer gradeId;
}
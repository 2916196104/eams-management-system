package com.zeroone.star.project.vo.j4.student;

import lombok.Data;


/**
 * 结业学员导出VO
 *
 *
 */
@Data
public class StudentExportVO {
    private String name;
    private Integer gender;
    private String idcard;
    private String graduationDate;
    private String graduationReason;
    private String parentName;
    private String parentMobile;
}
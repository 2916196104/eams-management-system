package com.zeroone.star.project.dto.j8.stumanger;



import com.zeroone.star.project.eums.FamilyRelationshipEnum;
import com.zeroone.star.project.eums.GenderEnum;
import com.zeroone.star.project.eums.StudentStageEnum;
import lombok.Data;
import org.springframework.format.annotation.DateTimeFormat;

import javax.validation.constraints.NotBlank;
import java.time.LocalDate;

/**
 * @author Ryan 541720500@qq.com
 * description
 */
@Data
public class StudentBaseInfoDTO {
    private Long id;
    private String name;
    @NotBlank(message = "缺少手机号")
    private String mobile;
    private String idcard;
    private String parentName;
    private FamilyRelationshipEnum familyRel;
    private StudentStageEnum stage;
    private Long joinWay;
    private GenderEnum gender;
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private LocalDate birthday;
    private String remark;
    // 顾问
    private Long counselor;
    private Long schoolId;
    private String passwordEncode;
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private LocalDate joinDate;
    private Long gradeId;
}

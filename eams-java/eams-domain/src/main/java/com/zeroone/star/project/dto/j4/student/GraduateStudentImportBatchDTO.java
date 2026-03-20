package com.zeroone.star.project.dto.j4.student;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.Valid;
import javax.validation.constraints.NotEmpty;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * 结业学员批量导入DTO
 *
 *
 */
@Data
@ApiModel(description = "结业学员批量导入DTO")
public class GraduateStudentImportBatchDTO {

    @ApiModelProperty(
            value = "结业学员列表（必填，默认包含1条示例数据）",
            required = true,
            example = "[{\"studentId\":\"2024001\",\"studentName\":\"张三\",\"gender\":1,\"idCard\":\"110101199001011234\",\"className\":\"高三1班\",\"graduateTime\":\"2024-06-30\",\"graduateStatus\":1,\"phone\":\"13800138000\",\"remark\":\"无\"}]"
    )
    @Valid
    @NotEmpty(message = "导入学员列表不能为空")
    private List<GraduateStudentImportDTO> studentList = new ArrayList<>(Arrays.asList(
            new GraduateStudentImportDTO() {{
                setStudentId("2024001");
                setStudentName("张三");
                setGender(1);
                setIdCard("110101199001011234");
                setClassName("高三1班");
                setGraduateTime(LocalDate.of(2024, 6, 30));
                setGraduateStatus(1);
                setPhone("13800138000");
                setRemark("无");
            }}
    ));
}
package com.zeroone.star.project.dto.j8.stumanager.SaveStu;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;

/**
 * @description：学员状态修改DTO（只传stage和学生ID）
 * @author：
 */
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
@ApiModel(value = "学员状态修改DTO")
public class SaveStuAddDTO {

    @NotNull(message = "学生ID不能为空")
    @ApiModelProperty(value = "学生ID", required = true)
    private Long studentId;

    @NotNull(message = "必须选择学员状态")
    @ApiModelProperty(value = "学员状态 0=意向 1=在学 2=结业 3=休学 4=退学", required = true)
    private Integer stage;
}

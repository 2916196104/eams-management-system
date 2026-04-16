package com.zeroone.star.project.dto.j8.stumanager.SaveStu;
import com.zeroone.star.project.dto.j8.stumanager.SaveStu.SaveStuAddDTO;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.Pattern;
import java.time.LocalDate;
import java.time.LocalDateTime;

/**
 * <p>
 * 描述：学员信息DTO
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author tsfmn
 * @version 1.0.0
 */
@Data
@ApiModel("学员信息DTO")
public class SaveStuDTO extends SaveStuAddDTO {

    @NotNull(message = "学员ID不能为空")
    @ApiModelProperty(value = "学员主键ID", example = "16", required = true)
    private Long id;

}
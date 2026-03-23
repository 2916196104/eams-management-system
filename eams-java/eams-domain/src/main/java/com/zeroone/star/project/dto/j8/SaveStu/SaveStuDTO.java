package com.zeroone.star.project.dto.j8.SaveStu;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import javax.validation.constraints.NotNull;
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
    @NotNull(message = "学员ID不能为空") // 修正：ID是Long类型，不能用@NotBlank（仅适用于字符串）
    @ApiModelProperty(value = "学员主键ID", required = true, example = "1")
    private Long id;

    // ========== 新增：实体中查询展示用的核心字段（前端详情页必显） ==========
    @ApiModelProperty(value = "加入时间（创建时间）", example = "2024-09-01 10:00:00")
    private LocalDateTime addTime;

    @ApiModelProperty(value = "编辑时间", example = "2024-09-02 14:00:00")
    private LocalDateTime editTime;

    @ApiModelProperty(value = "结业日期", example = "2027-06-30")
    private LocalDateTime graduationDate;

    @ApiModelProperty(value = "结业原因", example = "正常毕业")
    private String graduationReason;

    @ApiModelProperty(value = "逻辑删除 0-未删除 1-已删除", example = "0")
    private Integer deleted;

    @ApiModelProperty(value = "创建者所属组织ID", example = "1")
    private Long orgId;
}
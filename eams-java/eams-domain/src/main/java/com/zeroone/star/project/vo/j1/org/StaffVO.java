package com.zeroone.star.project.vo.j1.org;

import com.fasterxml.jackson.annotation.JsonFormat;
import io.swagger.annotations.ApiModelProperty;
import io.swagger.models.auth.In;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDate;

/**
 * <p>
 * 描述：员工查询操作
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author type-c
 * @version 1.0.0
 */
@Data
public class StaffVO {
   @ApiModelProperty(value="员工姓名",example = "管理员")
   private String name;
   @ApiModelProperty(value="员工账号",example="admin")
   private String account;
   @ApiModelProperty(value = "在职状态",example ="1" )
   private Integer statue;
   @ApiModelProperty
   private Integer gender;
   @ApiModelProperty
   private long orgId;
@ApiModelProperty
   private Integer isManger;
 @ApiModelProperty
private Integer isInner;
   @JsonFormat(pattern = "yyyy-MM-dd")
   private LocalDate hireDate;
   @ApiModelProperty
   private String positionName;
}

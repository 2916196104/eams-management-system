package com.zeroone.star.project.DO;

import com.baomidou.mybatisplus.annotation.TableName;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import org.hibernate.validator.constraints.Length;

import javax.validation.constraints.NotNull;
import javax.validation.constraints.Size;
import java.io.Serializable;
import java.util.Date;

/**
* 物料出入库记录
* @TableName material_record
*/
@Data
public class MaterialRecord implements Serializable {

    /**
    * 主键
    */
    @NotNull(message="[主键]不能为空")
    @ApiModelProperty("主键")
    private Long id;
    /**
    * 物料ID
    */
    @NotNull(message="[物料ID]不能为空")
    @ApiModelProperty("物料ID")
    private Long materialId;
    /**
    * 变动数量
    */
    @ApiModelProperty("变动数量")
    private Integer amount;
    /**
    * 变动原因说明
    */
    @Size(max= 50,message="编码长度不能超过50")
    @ApiModelProperty("变动原因说明")
    @Length(max= 50,message="编码长度不能超过50")
    private String reason;
    /**
    * 变动类型1入库2出库3积分商城出库
    */
    @ApiModelProperty("变动类型1入库2出库3积分商城出库 ")
    private Integer changeType;
    /**
    * 变动对象id如积分商城里的商品id
    */
    @ApiModelProperty("变动对象id如积分商城里的商品id")
    private Long changeTargetId;

    @Size(max= 100,message="编码长度不能超过100")
    @ApiModelProperty("备注信息")
    @Length(max= 100,message="编码长度不能超过100")
    private String remark;
    /**
    * 创建人
    */
    @ApiModelProperty("创建人")
    private Long creator;
    /**
    * 编辑人
    */
    @ApiModelProperty("编辑人")
    private Long editor;
    /**
    * 变动时间
    */
    @ApiModelProperty("变动时间")
    private Date addTime;
    /**
    * 编辑时间
    */
    @ApiModelProperty("编辑时间")
    private Date editTime;
    /**
    * 删除标记
    */
    @ApiModelProperty("删除标记")
    private Integer deleted;
    /**
    * 涉及学生id
    */
    @ApiModelProperty("涉及学生id")
    private Long studentId;
    /**
    * 涉及员工id
    */
    @ApiModelProperty("涉及员工id")
    private Long staffId;
    /**
    * 所属物料的组织ID
    */
    @ApiModelProperty("所属物料的组织ID")
    private Long orgId;
    /**
    * 学校id
    */
    @ApiModelProperty("学校id")
    private Long schoolId;
}

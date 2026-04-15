package com.zeroone.star.project.vo.j4.academic;

import com.baomidou.mybatisplus.annotation.TableName;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

/**
 * <p>
 * 教室视图对象
 * </p>
 * @author ab
 */
@Data
@ApiModel(value = "ClassroomVO", description = "教室视图对象")
public class ClassroomVO {
    /**
     * 教室ID
     */
    @ApiModelProperty(value = "教室ID",example = "1")
    private Long id;
    /**
     * 教室名
     */
    @ApiModelProperty(value = "教室名",example = "教室101")
    private String name;
    /**
     * 教室地址
     */
    @ApiModelProperty(value = "位置",example = "宏德楼")
    private String address;
    /**
     * 教室面积
     */
    @ApiModelProperty(value = "面积（平方米）",example = "50")
    private Integer area;
    /**
     * 备注说明
     */
    @ApiModelProperty(value = "备注",example = "本部校区")
    private String remark;
    /**
     * 创建者 ID
     */
    @ApiModelProperty(value = "创建者 ID")
    private Long creator;
    /**
     * 创建时间
     */
    @ApiModelProperty(value = "创建时间")
    private LocalDateTime addTime;

    /**
     * 修改者 ID
     */
    @ApiModelProperty(value = "修改者 ID")
    private Long editor;
    /**
     * 修改时间
     */
    @ApiModelProperty(value = "修改时间")
    private LocalDateTime editTime;
    /**
     * 学校ID
     */
    @ApiModelProperty(value = "学校ID",example = "1")
    private Long schoolId;
}
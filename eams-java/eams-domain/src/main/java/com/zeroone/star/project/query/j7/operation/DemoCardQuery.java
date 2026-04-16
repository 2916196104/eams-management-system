package com.zeroone.star.project.query.j7.operation;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
public class DemoCardQuery extends PageQuery {
    /**
     * 主键 ID
     * 场景：用于“获取指定行详细数据”时传入，此时 pageNum/pageSize 可忽略
     */
    @ApiModelProperty(value = "试听卡ID（用于获取详情）", example = "10086")
    private Long id;

    /**
     * 试听卡名称
     * 场景：列表模糊搜索，如“跆拳道”
     */
    @ApiModelProperty(value = "试听卡名称（模糊搜索）", example = "跆拳道")
    private String name;

    /**
     * 所属课程 ID
     * 场景：列表精确筛选，选择特定课程下的试听卡
     */
    @ApiModelProperty(value = "所属课程 ID", example = "3001")
    private Long courseId;

    /**
     * 课程名称（辅助查询，若数据库有冗余或需关联查询）
     */
    @ApiModelProperty(value = "课程名称（模糊搜索）", example = "体验课")
    private String courseName;

    /**
     * 是否启用
     * 场景：筛选“已启用”或“已禁用”的卡片
     * 字典：1-启用，0-禁用
     */
    @ApiModelProperty(value = "是否启用：1-启用，0-禁用", example = "1")
    private Integer isActive;

    /**
     * 发行结束日期 - 开始范围
     * 场景：查询某个时间段内过期的卡片
     */
    @ApiModelProperty(value = "发行结束日期起（yyyy-MM-dd）", example = "2026-01-01")
    private String startDate;

    /**
     * 发行结束日期 - 结束范围
     */
    @ApiModelProperty(value = "发行结束日期止（yyyy-MM-dd）", example = "2026-12-31")
    private String endDate;

    /**
     * 排序字段
     * 默认按创建时间倒序
     */
    @ApiModelProperty(value = "排序字段", hidden = true)
    private String orderBy = "created_at";

    /**
     * 排序方式
     */
    @ApiModelProperty(value = "排序方式：asc/desc", hidden = true)
    private String orderDirection = "desc";
}

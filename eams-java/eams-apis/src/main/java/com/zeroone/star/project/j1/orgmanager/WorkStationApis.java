package com.zeroone.star.project.j1.orgmanager;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j1.orgmanager.WorkStationDTO;
import com.zeroone.star.project.query.j1.orgmanager.WorkStationQueryCondition;
import com.zeroone.star.project.vo.JsonVO;

import java.util.List;

/**
 * <p>
 * 描述：职位管理接口
 * </p>
 *
 * @author gzx
 * @version 1.0.0
 */
public interface WorkStationApis {
    /**
     * 分页查询职位
     *
     * @param condition 分页查询条件
     * @return 职位分页列表
     */
    JsonVO<PageDTO<WorkStationDTO>> queryWorkStationPage(WorkStationQueryCondition condition);

    /**
     * 保存职位
     *
     * @param workStationDTO 职位数据对象
     * @return 保存结果
     */
    JsonVO<String> saveWorkStation(WorkStationDTO workStationDTO);

    /**
     * 删除职位
     *
     * @param ids 职位ID列表
     * @return 删除结果
     */
    JsonVO<String> removeWorkStations(List<Long> ids);

    /**
     * 获取职位名称列表
     *
     * @param name 职位名称，可选
     *
     * @return 职位名称列表
     */
    JsonVO<List<WorkStationDTO>> queryWorkStationNameList(String name);
}

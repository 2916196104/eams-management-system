package com.zeroone.star.project.j2.sys;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.sys.HolidayDTO;
import com.zeroone.star.project.query.j2.sys.HolidayQuery;
import com.zeroone.star.project.vo.JsonVO;


/**
 * <p>
 * 描述：节日API接口定义
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author Wind
 * @version 1.0.0
 */
public interface HolidayApis {

    /**
     * 节日条件、分页查询
     * @param query 查询条件
     * @return 查询结果
     */
    JsonVO<PageDTO<HolidayDTO>> pageQueryHoliday(HolidayQuery query);

    /**
     * 节日新增
     * @param holidayDto 新增数据
     * @return 新增结果
     */
    JsonVO<String> addHoliday(HolidayDTO holidayDto);

    /**
     * 节日删除
     * @param id 要删除数据的编号
     * @return 删除结果
     */
    JsonVO<String> removeHoliday(String id);
}

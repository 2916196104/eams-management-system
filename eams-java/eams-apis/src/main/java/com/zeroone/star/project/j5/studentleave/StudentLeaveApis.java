package com.zeroone.star.project.j5.studentleave;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j5.studentleave.StudentLeaveListDTO;
import com.zeroone.star.project.query.j5.studentleave.StudentLeaveQuery;
import com.zeroone.star.project.vo.JsonVO;

import java.util.List;

/**
 * <p>
 * 描述：学员请假相关接口定义
 * </p>
 *
 * @author : 小可
 * @date : 2026/3/15 15:30
 */
public interface StudentLeaveApis {

    /**
     * 撤销请假
     * @param ids 请假表id
     * @return    撤销结果
     */
    JsonVO<Integer> cancelLeaveRequest(List<Long> ids);

    /**
     * 获取请假列表 （条件+分页）
     * @param studentLeaveQuery     查询参数
     * @return                      查询结果
     */
    JsonVO<PageDTO<StudentLeaveListDTO>> queryStudentLeaveList(StudentLeaveQuery studentLeaveQuery);


}

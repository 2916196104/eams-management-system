package com.zeroone.star.operation.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.operation.entity.StudentCreditLogDO;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j9.operation.StudentCreditAdjustDTO;
import com.zeroone.star.project.query.j9.operation.StudentCreditLogQuery;
import com.zeroone.star.project.vo.j9.operation.StudentCreditAdjustVO;
import com.zeroone.star.project.vo.j9.operation.StudentCreditLogVO;

/**
 * 学生积分变动记录 服务接口
 */
public interface IStudentCreditLogService extends IService<StudentCreditLogDO> {

    /**
     * 查询学生积分记录列表（条件+分页）
     * @param condition 查询条件
     * @return 分页数据
     */
    PageDTO<StudentCreditLogVO> listCreditLogs(StudentCreditLogQuery condition);

    /**
     * 调整学生积分
     * @param adjustDTO 调整参数
     * @return 调整结果
     */
    StudentCreditAdjustVO updateStudentCredit(StudentCreditAdjustDTO adjustDTO);
}

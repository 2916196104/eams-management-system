package com.zeroone.star.stumanager.service.impl;

import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j8.stumanager.PayOverdueDTO;
import com.zeroone.star.project.dto.j8.stumanager.RefundDTO;
import com.zeroone.star.project.dto.j8.stumanager.RegistryRecordsDTO;
import com.zeroone.star.project.query.j8.stumanager.RegistryRecordsQuery;
import com.zeroone.star.stumanager.entity.Refund;
import com.zeroone.star.stumanager.entity.StudentCourse;
import com.zeroone.star.stumanager.mapper.RefundMapper;
import com.zeroone.star.stumanager.mapper.StudentCourseMapper;
import com.zeroone.star.stumanager.service.IRegistryRecordsService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;


import java.math.BigDecimal;
import java.time.LocalDateTime;

@Service
public class RegistryRecordsServiceImpl implements IRegistryRecordsService {

    @Autowired
    private StudentCourseMapper studentCourseMapper;

    @Autowired
    private RefundMapper refundMapper;

    /**
     * 分页查询报名记录
     * @param condition 查询条件
     * @return
     */
    @Override
    public PageDTO<RegistryRecordsDTO> queryRegistryRecords(RegistryRecordsQuery condition) {
        Page<RegistryRecordsDTO> page = new Page<>(condition.getPageIndex(), condition.getPageSize());

        IPage<RegistryRecordsDTO> resultPage = studentCourseMapper.selectRegistryRecords(page, condition);

        PageDTO<RegistryRecordsDTO> pageDTO = new PageDTO<>();
        pageDTO.setTotal(resultPage.getTotal());
        pageDTO.setPageIndex(resultPage.getCurrent());
        pageDTO.setPageSize(resultPage.getSize());
        return pageDTO;
    }

    /**
     * 缴纳欠费
     * @param dto 欠费信息
     * @param id 学生课程表 id
     * @return
     */

    @Override
    public String modifyPayOverdue(PayOverdueDTO dto, Long id) {
        StudentCourse studentCourse = studentCourseMapper.selectById(id);

        BigDecimal newAmount = studentCourse.getAmount().subtract(dto.getPayAmount());

        studentCourse.setPaidAmount(studentCourse.getPaidAmount().add(dto.getPayAmount()));

        if (newAmount.compareTo(BigDecimal.ZERO) <= 0) {
            studentCourse.setPayOff(true);
        }

        studentCourseMapper.updateById(studentCourse);

        return "缴纳欠费成功";
    }

    /**
     * 退费
     * @param dto 退费信息
     * @param id 学生课程表 id
     * @return
     */
    @Override
    public String modifyRefund(RefundDTO dto, Long id) {
        StudentCourse studentCourse = studentCourseMapper.selectById(id);

        Refund refund = new Refund();
        refund.setStudentCourseId(id);
        refund.setStudentId(studentCourse.getStudentId());
        refund.setOperator(studentCourse.getOperator());
        refund.setRefundAmount(dto.getActualRefundAmount().negate());
        refund.setRefundLessonCount(dto.getRefundLessonCount());
        refund.setRemark(dto.getRemark());
        refund.setApplyTime(LocalDateTime.now());
        refund.setVerifyState(1);
        refund.setTypeNum(1);

        refundMapper.insert(refund);

        studentCourse.setVerifyState(1);
        studentCourse.setCountLessonRefund(
                (studentCourse.getCountLessonRefund() == null ? 0 : studentCourse.getCountLessonRefund())
                        + dto.getRefundLessonCount()
        );

        studentCourseMapper.updateById(studentCourse);

        return "已成功发起申请";
    }
}

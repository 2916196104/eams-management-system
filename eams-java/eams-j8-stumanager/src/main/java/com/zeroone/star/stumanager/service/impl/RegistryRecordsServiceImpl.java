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
import java.util.List;
import java.util.stream.Collectors;

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
        // 如果 pageSize 为 0，设置为一个很大的值，返回所有记录
        if (condition.getPageSize() == 0) {
            condition.setPageIndex(1);
            condition.setPageSize(Integer.MAX_VALUE);
        }

        Page<RegistryRecordsDTO> page = new Page<>(condition.getPageIndex(), condition.getPageSize());

        IPage<RegistryRecordsDTO> resultPage = studentCourseMapper.selectRegistryRecords(page, condition);

        PageDTO<RegistryRecordsDTO> pageDTO = new PageDTO<>();
        pageDTO.setPageIndex(resultPage.getCurrent());
        pageDTO.setPageSize(resultPage.getSize());
        pageDTO.setTotal(resultPage.getTotal());
        pageDTO.setPages(resultPage.getPages());

        List<RegistryRecordsDTO> records = resultPage.getRecords();

        // 打印日志，查看是否查询到数据
        System.out.println("查询到的记录数：" + records.size());

        // 如果指定了自定义列，只返回这些列的数据
        if (condition.getDisplayColumns() != null && !condition.getDisplayColumns().isEmpty()) {
            records = filterColumns(records, condition.getDisplayColumns());
        }

        pageDTO.setRows(records);

        return pageDTO;
    }

    /**
     * 过滤只显示指定的列
     */
    private List<RegistryRecordsDTO> filterColumns(List<RegistryRecordsDTO> records, List<String> columns) {
        return records.stream()
                .map(dto -> {
                    RegistryRecordsDTO filteredDto = new RegistryRecordsDTO();

                    // 只复制指定字段的值
                    if (columns.contains("addTime")) {
                        filteredDto.setAddTime(dto.getAddTime());
                    }
                    if (columns.contains("name")) {
                        filteredDto.setName(dto.getName());
                    }
                    if (columns.contains("subjectName")) {
                        filteredDto.setSubjectName(dto.getSubjectName());
                    }
                    if (columns.contains("type")) {
                        filteredDto.setType(dto.getType());
                    }
                    if (columns.contains("countLessonTotal")) {
                        filteredDto.setCountLessonTotal(dto.getCountLessonTotal());
                    }
                    if (columns.contains("unitPrice")) {
                        filteredDto.setUnitPrice(dto.getUnitPrice());
                    }
                    if (columns.contains("amount")) {
                        filteredDto.setAmount(dto.getAmount());
                    }
                    if (columns.contains("discountAmount")) {
                        filteredDto.setDiscountAmount(dto.getDiscountAmount());
                    }
                    if (columns.contains("paidAmount")) {
                        filteredDto.setPaidAmount(dto.getPaidAmount());
                    }
                    if (columns.contains("payOverdue")) {
                        filteredDto.setPayOverdue(dto.getPayOverdue());
                    }
                    if (columns.contains("startDate")) {
                        filteredDto.setStartDate(dto.getStartDate());
                    }
                    if (columns.contains("expireDate")) {
                        filteredDto.setExpireDate(dto.getExpireDate());
                    }
                    if (columns.contains("verifyState")) {
                        filteredDto.setVerifyState(dto.getVerifyState());
                    }
                    if (columns.contains("dueAmount")) {
                        filteredDto.setDueAmount(dto.getDueAmount());
                    }
                    if (columns.contains("actualAmount")) {
                        filteredDto.setActualAmount(dto.getActualAmount());
                    }
                    if (columns.contains("refundLessonCount")) {
                        filteredDto.setRefundLessonCount(dto.getRefundLessonCount());
                    }
                    if (columns.contains("remark")) {
                        filteredDto.setRemark(dto.getRemark());
                    }
                    if (columns.contains("refundRerifyState")) {
                        filteredDto.setRefundRerifyState(dto.getRefundRerifyState());
                    }

                    return filteredDto;
                })
                .collect(Collectors.toList());
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

        if(studentCourse == null){
            return "该学生对应欠费不存在";
        }

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

        if(studentCourse == null){
            return "该学生对应退费信息不存在";
        }

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

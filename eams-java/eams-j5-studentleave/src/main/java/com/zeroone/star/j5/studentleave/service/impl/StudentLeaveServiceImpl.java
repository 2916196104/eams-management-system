package com.zeroone.star.j5.studentleave.service.impl;

import cn.hutool.core.bean.BeanUtil;
import com.baomidou.mybatisplus.core.conditions.update.LambdaUpdateWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.project.DO.j5.studentleave.StudentLeaveDO;
import com.zeroone.star.project.vo.j5.studentleave.StudentLeaveListVO;
import com.zeroone.star.j5.studentleave.mapper.StudentLeaveMapper;
import com.zeroone.star.j5.studentleave.service.IStudentLeaveService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j5.studentleave.StudentLeaveListDTO;
import com.zeroone.star.project.query.j5.studentleave.StudentLeaveQuery;
import com.zeroone.star.project.vo.JsonVO;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

/**
 * <p>
 * 学员请假 服务实现类
 * </p>
 *
 * @author xiaoke
 * @since 2026-03-22
 */
@Service
public class StudentLeaveServiceImpl extends ServiceImpl<StudentLeaveMapper, StudentLeaveDO> implements IStudentLeaveService {

    @Autowired
    private StudentLeaveMapper studentLeaveMapper;

    /**
     * 获取请假列表 （条件+分页）
     * @param query
     * @return
     */
    @Override
    public PageDTO<StudentLeaveListDTO> listStudentLeave(StudentLeaveQuery query) {

        // 创建分页对象
        Page<StudentLeaveListVO> page = new Page<>(query.getPageIndex(), query.getPageSize());

        // 查询
        Page<StudentLeaveListVO> resultPage = studentLeaveMapper.selectPageStudentLeave(page, query);

        return PageDTO.create(resultPage, vo -> {
            // 定义转换规则将 VO 转换为 DTO
            StudentLeaveListDTO dto = BeanUtil.copyProperties(vo, StudentLeaveListDTO.class);
            // 拼接课程信息字段
            dto.setCourseInfo(vo.getCourseInfo());
            return dto;
        });
    }

    @Override
    public JsonVO<Integer> cancelLeaveRequest(List<Long> ids) {

        // 1. 参数校验
        if (ids == null || ids.isEmpty()) {
            return JsonVO.fail("请假ID列表不能为空");
        }

        LambdaUpdateWrapper<StudentLeaveDO> wrapper = new LambdaUpdateWrapper<>();
        wrapper.set(StudentLeaveDO::getState, 2)
                .in(StudentLeaveDO::getId, ids);

        int updateCount = studentLeaveMapper.update(null, wrapper);

        return JsonVO.success(updateCount);
    }


}

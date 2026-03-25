package com.zeroone.star.stumanager.service;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j8.stumanager.common.StuClassQuery;
import com.zeroone.star.project.vo.j8.stumanager.ClassScheduleVO;
import com.zeroone.star.project.vo.j8.stumanager.StuClassVO;
import com.zeroone.star.stumanager.entity.Class;
import com.baomidou.mybatisplus.extension.service.IService;
import org.springframework.web.bind.annotation.RequestParam;

import javax.validation.constraints.NotNull;
import java.time.LocalDate;

/**
 * <p>
 * 班级 服务类
 * </p>
 *
 * @author dabidai
 * @since 2026-03-14
 */
public interface IClassService extends IService<Class> {
    PageDTO<StuClassVO> listStuClass(Integer page, Integer pageSize, Long studentId);

    PageDTO<ClassScheduleVO> listClassSchedule(Integer pageNo, Integer pageSize, StuClassQuery stuClassQuery);
}

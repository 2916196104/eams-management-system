package com.zeroone.star.operation.service.impl;

import cn.hutool.core.bean.BeanUtil;
import cn.hutool.core.convert.Convert;
import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.operation.entity.CourseTrialDO;
import com.zeroone.star.operation.mapper.CourseTrialMapper;
import com.zeroone.star.operation.service.ICourseTrialService;
import com.zeroone.star.project.components.user.UserHolder;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j9.operation.CourseTrialDTO;
import com.zeroone.star.project.query.j9.operation.CourseTrialQuery;
import com.zeroone.star.project.vo.j9.operation.CourseTrialVO;
import org.springframework.stereotype.Service;
import org.springframework.util.StringUtils;

import javax.annotation.Resource;
import java.time.LocalDateTime;
import java.time.ZoneId;
import java.util.ArrayList;
import java.util.List;

/**
 * 课程体验卡 服务实现类
 */
@Service
public class CourseTrialServiceImpl extends ServiceImpl<CourseTrialMapper, CourseTrialDO> implements ICourseTrialService {

    @Resource
    private UserHolder userHolder;

    @Override
    public PageDTO<CourseTrialVO> listCourseTrial(CourseTrialQuery condition) {
        LambdaQueryWrapper<CourseTrialDO> wrapper = new LambdaQueryWrapper<>();
        wrapper.eq(condition.getCourseId() != null, CourseTrialDO::getCourseId, condition.getCourseId())
               .like(StringUtils.hasText(condition.getTitle()), CourseTrialDO::getTitle, condition.getTitle())
               .eq(condition.getState() != null, CourseTrialDO::getState, condition.getState())
               .orderByDesc(CourseTrialDO::getAddTime);
        Page<CourseTrialDO> page = new Page<>(condition.getPageIndex(), condition.getPageSize());
        page(page, wrapper);
        return PageDTO.create(page, src -> {
            CourseTrialVO vo = new CourseTrialVO();
            BeanUtil.copyProperties(src, vo);
            if (src.getEndDate() != null) {
                vo.setEndDate(java.util.Date.from(src.getEndDate().atStartOfDay(ZoneId.systemDefault()).toInstant()));
            }
            if (src.getAddTime() != null) {
                vo.setAddTime(java.util.Date.from(src.getAddTime().atZone(ZoneId.systemDefault()).toInstant()));
            }
            return vo;
        });
    }

    @Override
    public CourseTrialVO getCourseTrial(Long id) {
        CourseTrialDO entity = getById(id);
        if (entity == null) {
            return null;
        }
        CourseTrialVO vo = new CourseTrialVO();
        BeanUtil.copyProperties(entity, vo);
        if (entity.getEndDate() != null) {
            vo.setEndDate(java.util.Date.from(entity.getEndDate().atStartOfDay(ZoneId.systemDefault()).toInstant()));
        }
        if (entity.getAddTime() != null) {
            vo.setAddTime(java.util.Date.from(entity.getAddTime().atZone(ZoneId.systemDefault()).toInstant()));
        }
        return vo;
    }

    @Override
    public boolean saveCourseTrial(CourseTrialDTO dto) {
        CourseTrialDO entity = new CourseTrialDO();
        BeanUtil.copyProperties(dto, entity);
        // Date -> LocalDate 转换
        if (dto.getEndDate() != null) {
            entity.setEndDate(dto.getEndDate().toInstant().atZone(ZoneId.systemDefault()).toLocalDate());
        }
        // 获取当前用户ID
        Long currentUserId = getCurrentUserId();
        if (dto.getId() == null) {
            // 新增：初始化剩余数量、创建时间、创建人
            entity.setRemainingQuantity(dto.getQuantity());
            entity.setAddTime(LocalDateTime.now());
            entity.setCreator(currentUserId);
        } else {
            // 修改：更新编辑时间、编辑人
            entity.setEditTime(LocalDateTime.now());
            entity.setEditor(currentUserId);
        }
        return saveOrUpdate(entity);
    }

    @Override
    public List<Long> removeCourseTrial(List<Long> ids) {
        List<Long> failIds = new ArrayList<>();
        for (Long id : ids) {
            if (!removeById(id)) {
                failIds.add(id);
            }
        }
        return failIds;
    }

    /**
     * 获取当前登录用户ID，获取失败返回null
     */
    private Long getCurrentUserId() {
        try {
            return Convert.toLong(userHolder.getCurrentUser().getId());
        } catch (Exception e) {
            return null;
        }
    }
}

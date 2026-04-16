package com.zeroone.star.operation.service.impl;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.operation.entity.CourseTrial;
import com.zeroone.star.operation.mapper.CourseTrialMapper;
import com.zeroone.star.operation.mapper.CourseTrialRecordMapper;
import com.zeroone.star.operation.service.ITrialCardService;
import com.zeroone.star.project.dto.j7.operation.TrialPageDTO;
import com.zeroone.star.project.query.j7.operation.TrialCardQuery;
import com.zeroone.star.project.query.j7.operation.TrialRecordQuery;
import com.zeroone.star.project.vo.j7.operation.TrialCardDetailVO;
import com.zeroone.star.project.vo.j7.operation.TrialCardVO;
import com.zeroone.star.project.vo.j7.operation.TrialRecordVO;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.util.List;

@Service
public class TrialCardServiceImpl extends ServiceImpl<CourseTrialMapper, CourseTrial> implements ITrialCardService {

    @Resource
    private CourseTrialMapper courseTrialMapper;
    @Resource
    private CourseTrialRecordMapper courseTrialRecordMapper;
    @Resource
    private MsTrialCardMapper msTrialCardMapper;
    @Override
    public TrialPageDTO<TrialCardVO> queryTrialCardList(TrialCardQuery query) {
        // 1. 初始化 MyBatis-Plus 的分页对象 (注意泛型直接用 VO)
        Page<TrialCardVO> page = new Page<>(query.getPageIndex(), query.getPageSize());

        // 2. 直接调用 Mapper 的自定义 XML 方法，条件组装都在 XML 里完成了
        Page<TrialCardVO> resultPage = courseTrialMapper.selectTrialPage(page, query);

        // 3. 封装返回给前端 (不需要 MapperStruct 了)
        return TrialPageDTO.create(resultPage);
    }

    @Override
    public TrialCardDetailVO queryTrialCardDetail(Long id) {
        // 直接调 XML 查询
        return courseTrialMapper.selectTrialDetail(id);
    }

    @Override
    public TrialPageDTO<TrialRecordVO> queryTrialCardRecords(TrialRecordQuery query) {

        Page<TrialRecordVO> page = new Page<>(query.getPageIndex(), query.getPageSize());
        Page<TrialRecordVO> resultPage = courseTrialRecordMapper.selectRecordPage(page, query);
        return TrialPageDTO.create(resultPage);
    }

    // 删除试听卡
    @Override
    public Boolean removeTrialCard(List<Long> ids) {
        if(ids == null || ids.isEmpty())
        {    return false;
        }
        //逻辑删除
        return this.lambdaUpdate().in(CourseTrial::getId,ids)
                .set(CourseTrial::getDeleted,1)
                .update();
    }
}

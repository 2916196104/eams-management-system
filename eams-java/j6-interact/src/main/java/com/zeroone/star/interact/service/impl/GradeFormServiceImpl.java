package com.zeroone.star.interact.service.impl;

import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.interact.mapper.GradeFormMapper;
import com.zeroone.star.interact.service.GradeFormService;
import com.zeroone.star.project.dataobject.j6.interact.GradeFormDO;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.interact.GradeFormDTO;
import com.zeroone.star.project.dto.j6.interact.GradeListDTO;
import com.zeroone.star.project.query.j6.interact.GradeFormQuery;
import com.zeroone.star.project.query.j6.interact.GradeRecordQuery;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.BeanUtils;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import javax.annotation.Resource;
import java.util.List;

/**
 * 成绩单业务实现类
 */
@Slf4j
@Service
public class GradeFormServiceImpl extends ServiceImpl<GradeFormMapper, GradeFormDO> implements GradeFormService {


    @Resource
    private GradeFormMapper gradeFormMapper;
    /**
     * 获取成绩单列表（条件+分页）
     * @param condition 查询条件
     * @return
     */
    @Override
    public PageDTO<GradeFormDTO> queryForm(GradeFormQuery condition) {
        //1.构建分页对象
        Page<GradeFormDTO> page=new Page<>(condition.getPageIndex(),condition.getPageSize());
        //2.自定义SQL查询
        IPage<GradeFormDTO> result=gradeFormMapper.queryForm(page,condition.getTitle(),condition.getCreator());
        //3.转换为PageDTO
        return PageDTO.create((Page<GradeFormDTO>) result);
    }

    /**
     * 保存成绩单
     *
     * @param gradeFormDTO 成绩单传递对象
     * @return 返回结果
     */
    @Override
    public Long saveGrade(GradeFormDTO gradeFormDTO) {
        //创建成绩单DO
        GradeFormDO gradeFormDO = new GradeFormDO();
        //属性注入
        BeanUtils.copyProperties(gradeFormDTO, gradeFormDO);
        boolean result = false;
        //判断是新增还是修改
        if (gradeFormDTO.getId() != null) {
            //修改
            //todo 填充修改人、修改时间
            //gradeFormDO.setEditor();
            //gradeFormDO.setEditTime(LocalDateTime.now());
            result  = this.updateById(gradeFormDO);
        }else {
            //新增
            //todo 填充创建者、创建时间、创建者组织、
            //gradeFormDO.setCreator();
            //gradeFormDO.setAddTime(LocalDateTime.now());
            result =  this.save(gradeFormDO);
        }
        //保存数据库
        if (!result) {
            throw new RuntimeException("保存成绩单操作失败");
        }
        //返回结果
        return gradeFormDO.getId();
    }

    /**
     * 删除成绩单
     *
     * @param ids 成绩单ID列表
     * @return 返回结果
     */
    @Override
    @Transactional(rollbackFor = Exception.class)
    public List<Long> deleteGrade(List<Long> ids) {

        boolean result = false;
        try {
            result = this.removeByIds(ids);
        } catch (Exception e) {
            log.error("成绩单删除操作失败");
            //todo 应该换成全局异常处理器
            throw new RuntimeException(e);
        }
        if (!result) {
            log.error("成绩单删除操作失败");
            //todo 应该换成全局异常处理器
            throw new RuntimeException("删除成绩单操作失败");
        }
        return ids;
    }

    /**
     * 获取成绩列表
     *
     * @param gradeRecordQuery 查询条件
     * @return 返回分页结果
     */
    @Override
    public PageDTO<GradeListDTO> getGradeRecordList(GradeRecordQuery gradeRecordQuery) {
        Long gradeId = gradeRecordQuery.getGradeId();
        long pageIndex = gradeRecordQuery.getPageIndex();
        long pageSize = gradeRecordQuery.getPageSize();

        //参数校验
        if(gradeId == null || gradeId <= 0){
            throw new RuntimeException("成绩单ID为空或者成绩单id不合法");
        }
        //构造分页条件
        IPage<GradeListDTO> page = new Page<>(pageIndex,pageSize);
        //查询数据库,获取分页结果
        IPage<GradeListDTO> gradeRecordListPage = this.baseMapper.getGradeRecordList(page, gradeId);

        //创建分页DTO
        PageDTO<GradeListDTO> gradeListDTOPageDTO = new PageDTO<>();
        gradeListDTOPageDTO.setPageIndex(gradeRecordListPage.getCurrent());
        gradeListDTOPageDTO.setPageSize(gradeRecordListPage.getSize());
        gradeListDTOPageDTO.setTotal(gradeRecordListPage.getTotal());
        gradeListDTOPageDTO.setPages(gradeRecordListPage.getPages());
        gradeListDTOPageDTO.setRows(gradeRecordListPage.getRecords());
       //返回结果
        return gradeListDTOPageDTO;
    }
}

package com.zeroone.star.eamsj3class.service.impl;

import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.eamsj3class.entity.Subject;
import com.zeroone.star.eamsj3class.mapper.SubjectMapper;
import com.zeroone.star.eamsj3class.service.ISubjectService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j3.course.SubjectDTO;
import com.zeroone.star.project.query.j3.course.SubjectQuery;
import org.springframework.stereotype.Service;
import org.springframework.util.StringUtils;

import javax.annotation.Resource;
import java.util.List;
import java.util.stream.Collectors;

/**
 * <p>
 * 科目 服务实现类
 * </p>
 *
 * @author heavydrink
 * @since 2026-03-23
 */
@Service
public class SubjectServiceImpl extends ServiceImpl<SubjectMapper, Subject> implements ISubjectService {

    @Resource
    private MsSampleMapper ms;

    @Override
    public PageDTO<SubjectDTO> querySubjectList(SubjectQuery query) {
        if (query == null) {
            query = new SubjectQuery();
        }
        List<SubjectDTO> rows = lambdaQuery()
                .like(StringUtils.hasText(query.getName()), Subject::getName, query.getName())
                .like(StringUtils.hasText(query.getInfo()), Subject::getInfo, query.getInfo())
                .eq(query.getSortNum() != null, Subject::getSortNum, query.getSortNum())
                .ne(Subject::getDeleted, 1)
                .orderByAsc(Subject::getSortNum)
                .list()
                .stream()
                .map(ms::subjectToDto)
                .collect(Collectors.toList());
        long total = rows.size();
        return new PageDTO<>(1L, total, total, total == 0 ? 0L : 1L, rows);
    }

    @Override
    public List<String> querySubjectNames() {
        return lambdaQuery()
                .ne(Subject::getDeleted, 1)
                .orderByAsc(Subject::getSortNum)
                .list()
                .stream()
                .map(Subject::getName)
                .collect(Collectors.toList());
    }

    @Override
    public boolean saveSubject(SubjectDTO subjectDTO) {
        return saveOrUpdate(ms.subjectDtoToDo(subjectDTO));
    }

    @Override
    public boolean deleteSubjects(List<String> subjectIds) {
        List<Long> ids = toIds(subjectIds);
        if (ids.isEmpty()) {
            return false;
        }
        return updateDeletedByIds(ids);
    }

    protected boolean updateDeletedByIds(List<Long> ids) {
        return lambdaUpdate()
                .in(Subject::getId, ids)
                .ne(Subject::getDeleted, 1)
                .set(Subject::getDeleted, 1)
                .update();
    }

    private List<Long> toIds(List<String> ids) {
        if (ids == null || ids.isEmpty()) {
            return java.util.Collections.emptyList();
        }
        try {
            return ids.stream()
                    .filter(StringUtils::hasText)
                    .map(Long::valueOf)
                    .collect(Collectors.toList());
        } catch (NumberFormatException exception) {
            return java.util.Collections.emptyList();
        }
    }
}

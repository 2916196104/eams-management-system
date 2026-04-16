package com.zeroone.star.stumanager.service.impl;

import com.zeroone.star.stumanager.entity.ContactRecord;
import com.zeroone.star.stumanager.mapper.ContactRecordMapper;
import com.zeroone.star.stumanager.service.IContactRecordService;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.project.dto.ExtendPageDTO;
import com.zeroone.star.project.dto.j8.stumanager.AddFollowRecordDTO;
import com.zeroone.star.project.vo.j8.stumanager.FollowRecordVO;
import com.zeroone.star.project.components.user.UserHolder;
import com.zeroone.star.project.components.user.UserDTO;
import org.springframework.stereotype.Service;
import javax.annotation.Resource;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

/**
 * <p>
 * 学员跟进表 服务实现类
 * </p>
 *
 * @author dabidai
 * @since 2026-03-14
 */
@Service
public class ContactRecordServiceImpl extends ServiceImpl<ContactRecordMapper, ContactRecord> implements IContactRecordService {

    @Resource
    private UserHolder userHolder;

    @Override
    public ExtendPageDTO<FollowRecordVO> getFollowRecords(Long studentId, Integer page, Integer size) {
        if (studentId == null) {
            throw new IllegalArgumentException("学员ID不能为空");
        }
        if (page == null || page < 1) {
            page = 1;
        }
        if (size == null || size < 1) {
            size = 10;
        }

        List<ContactRecord> records = baseMapper.selectByStudentId(studentId);

        if (records == null || records.isEmpty()) {
            return new ExtendPageDTO<>(new ArrayList<>(), page, size, 0);
        }

        int total = records.size();
        int start = (page - 1) * size;
        int end = Math.min(start + size, total);

        if (start >= total) {
            return new ExtendPageDTO<>(new ArrayList<>(), page, size, total);
        }

        List<ContactRecord> pageRecords = records.subList(start, end);

        List<FollowRecordVO> voList = pageRecords.stream()
                .map(record -> {
                    FollowRecordVO vo = new FollowRecordVO();
                    vo.setId(record.getId());
                    vo.setStudentId(record.getStudentId());
                    vo.setInfo(record.getInfo());
                    vo.setContactTime(record.getContactTime());
                    vo.setContactNextTime(record.getContactNextTime());
                    vo.setContactType(record.getContactType());
                    vo.setContactPhone(record.getContactPhone());
                    vo.setCreator(record.getCreator());
                    vo.setAddTime(record.getAddTime());
                    vo.setStage(record.getStage());
                    return vo;
                }).collect(Collectors.toList());

        ExtendPageDTO<FollowRecordVO> pageDTO = new ExtendPageDTO<>(voList, page, size, total);

        return pageDTO;
    }

    @Override
    public Boolean addFollowRecord(AddFollowRecordDTO dto) {
        if (dto.getStudentId() == null) {
            throw new IllegalArgumentException("学员ID不能为空");
        }
        if (dto.getInfo() == null || dto.getInfo().trim().isEmpty()) {
            throw new IllegalArgumentException("跟进内容不能为空");
        }
        if (dto.getContactTime() == null) {
            throw new IllegalArgumentException("联系时间不能为空");
        }
        if (dto.getStage() == null) {
            throw new IllegalArgumentException("跟进阶段不能为空");
        }

        Long creatorId = 1L;
        try {
            UserDTO currentUser = userHolder.getCurrentUser();
            if (currentUser != null && currentUser.getId() != null && !currentUser.getId().isEmpty()) {
                try {
                    creatorId = Long.parseLong(currentUser.getId());
                } catch (NumberFormatException e) {
                    // ID格式错误，使用默认值
                }
            }
        } catch (Exception e) {

        }

        ContactRecord record = new ContactRecord();
        record.setStudentId(dto.getStudentId());
        record.setInfo(dto.getInfo());
        record.setContactTime(dto.getContactTime());
        record.setContactNextTime(dto.getContactNextTime());
        record.setContactType(dto.getContactType());
        record.setContactPhone(dto.getContactPhone());
        record.setStage(dto.getStage());
        record.setCreator(creatorId);
        record.setAddTime(LocalDateTime.now());
        record.setDeleted(false);
        record.setOrgId(1L);

        return save(record);
    }

    @Override
    public Boolean deleteFollowRecord(Long id) {
        if (id == null) {
            throw new IllegalArgumentException("跟进记录ID不能为空");
        }

        ContactRecord record = getById(id);
        if (record == null) {
            throw new IllegalArgumentException("跟进记录不存在");
        }

        if (record.getDeleted() != null && record.getDeleted()) {
            throw new IllegalArgumentException("跟进记录已被删除");
        }

        record.setDeleted(true);
        return updateById(record);
    }
}

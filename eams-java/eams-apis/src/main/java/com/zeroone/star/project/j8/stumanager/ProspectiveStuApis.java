package com.zeroone.star.project.j8.stumanager;

import com.zeroone.star.project.vo.JsonVO;
import org.springframework.http.ResponseEntity;
import org.springframework.web.multipart.MultipartFile;

import java.io.IOException;
import java.util.List;

/**
 * 意向学员
 */
public interface ProspectiveStuApis {
    // 导出意向学员
    ResponseEntity<byte[]> exportProspectiveStu(List<Long> ids) throws IOException;
    // 导入意向学员
    JsonVO<String> importProspectiveStu(MultipartFile file);
}

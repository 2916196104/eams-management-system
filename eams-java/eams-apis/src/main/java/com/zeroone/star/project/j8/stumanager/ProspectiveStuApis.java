package com.zeroone.star.project.j8.stumanager;

import com.zeroone.star.project.query.j8.stumanager.ProspectiveStuQuery;
import com.zeroone.star.project.vo.JsonVO;
import org.springframework.web.multipart.MultipartFile;

import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.List;

/**
 * 意向学员
 */
public interface ProspectiveStuApis {
    // 导出意向学员
    void exportProspectiveStu(HttpServletResponse response, ProspectiveStuQuery prospectiveStuQuery) throws IOException;
    // 导入意向学员
    JsonVO<String> importProspectiveStu(MultipartFile file) throws IOException;
}

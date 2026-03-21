package com.zeroone.star.student.config;

import javax.servlet.http.HttpServletRequest;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public final class RequestMetaUtil {

    private RequestMetaUtil() {}

    // 获取客户端IP地址，考虑了常见的代理头
    public static String getClientIp(HttpServletRequest request) {
        String ip = firstNonUnknown(
                request.getHeader("X-Forwarded-For"),
                request.getHeader("Proxy-Client-IP"),
                request.getHeader("WL-Proxy-Client-IP"),
                request.getHeader("X-Real-IP"),
                request.getRemoteAddr()
        );
        // X-Forwarded-For 可能是 "client, proxy1, proxy2"
        if (ip != null && ip.contains(",")) {
            ip = ip.split(",")[0].trim();
        }
        return ip;
    }

    // 把 User-Agent 字符串解析成 browserName/browserVer/osName
    public static UaInfo parseUa(String ua) {
        if (ua == null) {
            return new UaInfo("Unknown", "Unknown", "Unknown");
        }

        String os = detectOs(ua);
        String browser = detectBrowser(ua);
        String version = detectVersion(ua);

        return new UaInfo(browser, version, os);
    }

    // 关键字匹配系统（Windows/macOS/Android/iOS/Linux）
    private static String detectOs(String ua) {
        String u = ua.toLowerCase();
        if (u.contains("windows")) return "Windows";
        if (u.contains("mac os")) return "macOS";
        if (u.contains("android")) return "Android";
        if (u.contains("iphone") || u.contains("ipad")) return "iOS";
        if (u.contains("linux")) return "Linux";
        return "Unknown";
    }

    // 按标记匹配浏览器（Edge/Chrome/Firefox/Safari）
    private static String detectBrowser(String ua) {
        if (ua.contains("Edg/")) return "Edge";
        if (ua.contains("Chrome/")) return "Chrome";
        if (ua.contains("Firefox/")) return "Firefox";
        if (ua.contains("Safari/") && ua.contains("Version/")) return "Safari";
        return "Unknown";
    }

    // 用正则 (Edg|Chrome|Firefox|Version)/([\d.]+) 抓版本号
    private static String detectVersion(String ua) {
        Pattern p = Pattern.compile("(Edg|Chrome|Firefox|Version)/([\\d.]+)");
        Matcher m = p.matcher(ua);
        if (m.find()) {
            return m.group(2);
        }
        return "Unknown";
    }

    private static String firstNonUnknown(String... values) {
        for (String v : values) {
            if (v != null && v.length() > 0 && !"unknown".equalsIgnoreCase(v)) {
                return v;
            }
        }
        return null;
    }

    public static class UaInfo {
        private final String browserName;
        private final String browserVer;
        private final String osName;

        public UaInfo(String browserName, String browserVer, String osName) {
            this.browserName = browserName;
            this.browserVer = browserVer;
            this.osName = osName;
        }

        public String getBrowserName() { return browserName; }
        public String getBrowserVer() { return browserVer; }
        public String getOsName() { return osName; }
    }
}

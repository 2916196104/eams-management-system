package com.zeroone.star.oauth2.controller;

import com.zeroone.cloud.oauth2.entity.Oauth2Token;
import org.springframework.boot.autoconfigure.condition.ConditionalOnWebApplication;
import org.springframework.http.ResponseEntity;
import org.springframework.security.authentication.BadCredentialsException;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import org.springframework.security.oauth2.common.OAuth2AccessToken;
import org.springframework.security.oauth2.common.OAuth2RefreshToken;
import org.springframework.security.oauth2.common.exceptions.InvalidGrantException;
import org.springframework.security.oauth2.provider.endpoint.TokenEndpoint;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import java.security.Principal;
import java.util.Map;

@RestController
@ConditionalOnWebApplication
@RequestMapping("oauth")
public class AuthController {
    private static final String CREDENTIAL_ERROR_MESSAGE = "\u8d26\u53f7\u6216\u5bc6\u7801\u9519\u8bef";
    private static final String PASSWORD_GRANT_TYPE = "password";
    private static final String DEBUG_PREFIX = "postAccessToken:";

    private final TokenEndpoint tokenEndpoint;

    public AuthController(TokenEndpoint tokenEndpoint) {
        this.tokenEndpoint = tokenEndpoint;
    }

    @PostMapping("token")
    public Oauth2Token postAccessToken(Principal principal, @RequestParam Map<String, String> parameters) {
        Oauth2Token token = new Oauth2Token();
        OAuth2AccessToken accessToken;
        try {
            ResponseEntity<OAuth2AccessToken> response = tokenEndpoint.postAccessToken(principal, parameters);
            accessToken = response.getBody();
        } catch (Exception exception) {
            token.setErrorMsg(resolveErrorMessage(exception, parameters));
            return token;
        }

        if (accessToken == null) {
            token.setErrorMsg("oAuth2AccessToken\u4e3anull");
            return token;
        }

        token.setToken(accessToken.getValue());
        OAuth2RefreshToken refreshToken = accessToken.getRefreshToken();
        if (refreshToken != null) {
            token.setRefreshToken(refreshToken.getValue());
        }
        token.setTokenHead("Bearer");
        token.setExpiresIn(accessToken.getExpiresIn());
        token.setClientId(parameters.get("client_id"));
        return token;
    }

    private String resolveErrorMessage(Exception exception, Map<String, String> parameters) {
        if (isCredentialError(exception, parameters)) {
            return CREDENTIAL_ERROR_MESSAGE;
        }
        String message = exception.getMessage();
        return DEBUG_PREFIX + exception.getClass().getSimpleName() + ":" + (message == null ? "" : message);
    }

    private boolean isCredentialError(Throwable throwable, Map<String, String> parameters) {
        if (!PASSWORD_GRANT_TYPE.equals(parameters.get("grant_type"))) {
            return false;
        }

        Throwable current = throwable;
        while (current != null) {
            if (current instanceof BadCredentialsException || current instanceof UsernameNotFoundException) {
                return true;
            }
            if (current instanceof InvalidGrantException && containsCredentialMessage(current.getMessage())) {
                return true;
            }
            if (containsCredentialMessage(current.getMessage())) {
                return true;
            }
            current = current.getCause();
        }
        return false;
    }

    private boolean containsCredentialMessage(String message) {
        return message != null
                && (message.contains("Bad credentials") || message.contains("\u7528\u6237\u540d\u6216\u5bc6\u7801\u9519\u8bef"));
    }
}

package com.zeroone.star.oauth2.controller;

import com.zeroone.cloud.oauth2.entity.Oauth2Token;
import org.junit.jupiter.api.Test;
import org.springframework.http.ResponseEntity;
import org.springframework.security.authentication.BadCredentialsException;
import org.springframework.security.oauth2.common.DefaultOAuth2AccessToken;
import org.springframework.security.oauth2.common.DefaultOAuth2RefreshToken;
import org.springframework.security.oauth2.common.exceptions.InvalidGrantException;
import org.springframework.security.oauth2.provider.endpoint.TokenEndpoint;

import java.security.Principal;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNull;

class AuthControllerTest {

    @Test
    void postAccessTokenReturnsOauthTokenWhenRequestSucceeds() throws Exception {
        DefaultOAuth2AccessToken accessToken = new DefaultOAuth2AccessToken("access-token");
        accessToken.setRefreshToken(new DefaultOAuth2RefreshToken("refresh-token"));
        accessToken.setExpiration(new Date(System.currentTimeMillis() + 3600_000));

        StubTokenEndpoint tokenEndpoint = new StubTokenEndpoint();
        tokenEndpoint.response = ResponseEntity.ok(accessToken);

        AuthController controller = new AuthController(tokenEndpoint);
        Map<String, String> parameters = passwordParameters();
        parameters.put("client_id", "eams-manager");

        Oauth2Token token = controller.postAccessToken(null, parameters);

        assertEquals("access-token", token.getToken());
        assertEquals("refresh-token", token.getRefreshToken());
        assertEquals("Bearer", token.getTokenHead());
        assertEquals("eams-manager", token.getClientId());
        assertNull(token.getErrorMsg());
    }

    @Test
    void postAccessTokenMapsBadCredentialsToFriendlyMessageForPasswordGrant() {
        StubTokenEndpoint tokenEndpoint = new StubTokenEndpoint();
        tokenEndpoint.exception = new InvalidGrantException("Bad credentials");

        AuthController controller = new AuthController(tokenEndpoint);

        Oauth2Token token = controller.postAccessToken(null, passwordParameters());

        assertEquals("\u8d26\u53f7\u6216\u5bc6\u7801\u9519\u8bef", token.getErrorMsg());
    }

    @Test
    void postAccessTokenMapsBadCredentialsCauseToFriendlyMessageForPasswordGrant() {
        StubTokenEndpoint tokenEndpoint = new StubTokenEndpoint();
        tokenEndpoint.exception = new RuntimeException("wrapped", new BadCredentialsException("Bad credentials"));

        AuthController controller = new AuthController(tokenEndpoint);

        Oauth2Token token = controller.postAccessToken(null, passwordParameters());

        assertEquals("\u8d26\u53f7\u6216\u5bc6\u7801\u9519\u8bef", token.getErrorMsg());
    }

    @Test
    void postAccessTokenKeepsRefreshTokenErrorsAsOriginalMessage() {
        StubTokenEndpoint tokenEndpoint = new StubTokenEndpoint();
        tokenEndpoint.exception = new InvalidGrantException("Invalid refresh token");

        AuthController controller = new AuthController(tokenEndpoint);
        Map<String, String> parameters = new HashMap<>();
        parameters.put("grant_type", "refresh_token");

        Oauth2Token token = controller.postAccessToken(null, parameters);

        assertEquals("postAccessToken:InvalidGrantException:Invalid refresh token", token.getErrorMsg());
    }

    private Map<String, String> passwordParameters() {
        Map<String, String> parameters = new HashMap<>();
        parameters.put("grant_type", "password");
        parameters.put("username", "zhangsan");
        parameters.put("password", "123456");
        return parameters;
    }

    private static final class StubTokenEndpoint extends TokenEndpoint {
        private ResponseEntity<org.springframework.security.oauth2.common.OAuth2AccessToken> response;
        private Exception exception;

        @Override
        public ResponseEntity<org.springframework.security.oauth2.common.OAuth2AccessToken> postAccessToken(
                Principal principal, Map<String, String> parameters) throws org.springframework.web.HttpRequestMethodNotSupportedException {
            if (exception != null) {
                if (exception instanceof org.springframework.web.HttpRequestMethodNotSupportedException) {
                    throw (org.springframework.web.HttpRequestMethodNotSupportedException) exception;
                }
                if (exception instanceof RuntimeException) {
                    throw (RuntimeException) exception;
                }
                throw new RuntimeException(exception);
            }
            return response;
        }
    }
}

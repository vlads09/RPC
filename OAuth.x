struct authorization {
    string id<16>;
    string refresh<2>;
};

program GRADE_PROG {
    version GRADE_VERS {
        string request_authorization_token(authorization) = 1;
    } = 1;
} = 0x31234567;

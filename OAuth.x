struct authorization {
    string id<16>;
};

struct approve {
    string authorization_token<16>;
};

struct approve_response {
    string authorization_token<16>;
    int verify;
    string permissions<50>;
};

struct access {
    string id<16>;
    string refresh<2>;
    approve_response authorization_token;
};

struct access_response {
    string access_token<16>;
    string refresh_token<16>;
    int valability;
};

struct action {
    string operation<10>;
    string source<15>;
    string access_token<16>;
};

struct refresh_input {
    string id<16>;
    string refresh<16>;
};

struct refresh_output {
    string access_token<16>;
    string refresh_token<16>;
    int valability;
};

program GRADE_PROG {
    version GRADE_VERS {
        string request_authorization_token(authorization) = 1;
        approve_response approve_request_token(approve) = 2;
        access_response request_access_token(access) = 3;
    } = 1;

    version GRADE_VERS_2 {
        string validate_delegated_action(action)= 1;
    } = 2;

    version GRADE_VERS_3 {
        refresh_output get_new_token(refresh_input) = 1;
    } = 3;
} = 0x31234567;

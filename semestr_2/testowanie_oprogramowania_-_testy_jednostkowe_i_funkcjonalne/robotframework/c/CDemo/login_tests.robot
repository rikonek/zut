*** Settings ***
Library           LoginLibrary.py

*** Test Case ***
Validate Users
    [Template]    Login with valid user should succeed
    johns    long
    demo     mode

Login With Invalid User Should Fail
    [Template]    Login with invalid user should fail
    de          mo
    invalid     invalid
    long        invalid
    ${EMPTY}    ${EMPTY}

*** Keyword ***
Login with valid user should succeed
    [Arguments]    ${username}    ${password}
    Check User    ${username}    ${password}

Login with invalid user should fail
    [Arguments]    ${username}    ${password}
    Run Keyword And Expect Error    Wrong username/password combination
    ...    Check User    ${username}    ${password}

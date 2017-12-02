*** Settings ***
Documentation     This is a basic test documentation for second testl
Library           Selenium2Library

*** Variables ***
${APP}            robotframework
${URL}            http://localhost:7272
${BROWSER}        chrome


*** Test Cases ***
[TC-001] Open test browser
    [Documentation]    This a basic information about a test
    [Tags]    Req001, Smoke
    Launch Browser
    Close Browser
[TC-002]- Correct login
    [Documentation]  Good test
    [Tags]  Req002
    [Setup]     Launch Browser
    Insert credentials
    Test goodpage
    Logout
    Close Browser
[TC-003]- Incorrect login
    [Documentation]  Bad test
    [Tags]  Req003
    [Setup]     Launch Browser
    Insert badcredentials
    Test badpage
    Close Browser

*** Keywords ***
Launch Browser
    Open Browser    ${URL}  ${BROWSER}
    Maximize Browser Window
Insert credentials
    Input Text    id=username_field    demo
    Input Text    id=password_field    mode
    Press Key    id=login_button    \\13
Insert badcredentials
    Input Text    id=username_field    demo
    Input Text    id=password_field    demo
    Press Key    id=login_button    \\13
Test goodpage
    Title Should Be    Welcome Page
Test badpage
    Title Should Be    Error Page
Logout
    Wait Until Element Is Visible    link=logout      20 Seconds
    Click Element     link=logout

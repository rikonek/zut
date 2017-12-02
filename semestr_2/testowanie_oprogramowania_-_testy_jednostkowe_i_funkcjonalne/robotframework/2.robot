*** Settings ***
Documentation    This is a basic test documentation for second testl
Library    Selenium2Library

*** Variables ***
${APP}    robotframework
${URL}    https://www.google.pl
${BROWSER}    chrome

*** Test Cases ***
[TC-001] Open test browser
    [Documentation]    This a basic information about a test
    [Tags]    Req001, Smoke
    Launch Browser
    Close Browser

[TC-002] Search RobotFramework page
    [Documentation]    Launching the browser and search and launch the “robotframework” Application on Google.pl
    [Tags]    Req002
    Launch Browser
    Search Site On Google
    Launch Site
    Check Site
    [Teardown]    Close Browser

*** Keywords ***
Launch Browser
    Open Browser    ${URL}    ${BROWSER}
    Maximize Browser Window
Search Site On Google
    Input Text    id=lst-ib    ${APP}
    Press Key    name=q    \\13
Launch Site
    Wait Until Element Is Visible    link=Robot Framework    20 Seconds
    Click Element    link=Robot Framework
Check Site
    Page Should Contain    http://robotframework.org/    20 Seconds

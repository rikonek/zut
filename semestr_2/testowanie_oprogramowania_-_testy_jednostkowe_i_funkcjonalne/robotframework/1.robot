*** Settings ***
Documentation    This is a basic test
Library    Selenium2Library

*** Test Cases ***
Open test browser
    [Documentation]    This a basic information about a test
    [Tags]    Smoke
    Open Browser    http://www.google.com    chrome
    Close Browser

*** Keywords ***

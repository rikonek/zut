*** Settings ***
Documentation     Example test cases using the data-driven testing approach.

Test Template     Calculate
Library           CalculatorLibrary.py


*** Test Cases ***    Expression    Expected
Addition              2 + 2         4
Subtraction           6 - 2         4
Failing               1 + 1         3

*** Keywords ***
Calculate
    [Arguments]    ${expression}    ${expected}
    Push buttons    C${expression}=
    Result should be    ${expected}
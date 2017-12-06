*** Settings ***
Documentation     Example test case using the keyword-driven testing approach.

Library           CalculatorLibrary.py

*** Test Cases ***
Push button
    Push button    1
    Result should be    1

Clear
    Push button    1
    Push button    C
    Result should be    ${EMPTY}    # ${EMPTY} is a built-in variable
# testowanie operacji matematycznych na inteligencje kalkulatora
# w tescie 2+2x2=8 wynik wyzualny jest 8, ale powinno byc kontekstowo 6 
 
# -*- coding: utf-8 -*-


def main():
    startApplication("calqlatr")
    mouseClick(waitForObject(":1_Text"))
    mouseClick(waitForObject(":÷_Text"))
    mouseClick(waitForObject(":3_Text"))
    mouseClick(waitForObject(":=_Text"))
    mouseClick(waitForObject(":×_Text"))
    mouseClick(waitForObject(":3_Text"))
    mouseClick(waitForObject(":=_Text"))
    test.vp("VP1")
    mouseClick(waitForObject(":C_Text"))
    mouseClick(waitForObject(":2_Text"))
    mouseClick(waitForObject(":+_Text"))
    mouseClick(waitForObject(":2_Text"))
    mouseClick(waitForObject(":×_Text"))
    mouseClick(waitForObject(":2_Text"))
    mouseClick(waitForObject(":=_Text"))
    test.vp("VP2")
    test.compare(str(waitForObjectExists(":8_Text_3").text), "6")

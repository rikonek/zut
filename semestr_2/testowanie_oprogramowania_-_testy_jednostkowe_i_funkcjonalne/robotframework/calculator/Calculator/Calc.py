# -*- coding: utf-8 -*-
"""

@author: marcin.caryk
"""

from PyQt4 import QtCore, QtGui
import Calc_MainWin
import sys
from calculator import Calculator

class CalcHandler(object): 
    
    def __init__(self):
        
        self.app = QtGui.QApplication(sys.argv)
        self.MainWindow = QtGui.QMainWindow()
        self.ui = Calc_MainWin.Ui_MainWindow()
        self.ui.setupUi(self.MainWindow)
        self.ui.label_results.setText('0')
        self.initialize_conncetion()
        self.operation_string_dict = []
        
    def main_win_show(self):
        self.MainWindow.show()
        sys.exit(self.app.exec_())
        
    def initialize_conncetion(self):
        self.ui.pushButton_k1.clicked.connect(self.press_button_1)
        self.ui.pushButton_k2.clicked.connect(self.press_button_2)
        self.ui.pushButton_k3.clicked.connect(self.press_button_3)
        self.ui.pushButton_k4.clicked.connect(self.press_button_4)
        self.ui.pushButton_k5.clicked.connect(self.press_button_5)
        self.ui.pushButton_k6.clicked.connect(self.press_button_6)
        self.ui.pushButton_k7.clicked.connect(self.press_button_7)
        self.ui.pushButton_k8.clicked.connect(self.press_button_8)
        self.ui.pushButton_k9.clicked.connect(self.press_button_9)
        self.ui.pushButton_k0.clicked.connect(self.press_button_0)
        self.ui.pushButton_plus.clicked.connect(self.press_button_add)
        self.ui.pushButton_min.clicked.connect(self.press_button_sub)
        self.ui.pushButton_mult.clicked.connect(self.press_button_multi)
        self.ui.pushButton_div.clicked.connect(self.press_button_divide)
        self.ui.pushButton_C.clicked.connect(self.press_button_C)
        self.ui.pushButton_equal.clicked.connect(self.press_button_equal)

        
    def press_button_1(self):
        self.operation_string_dict.append('1')
        self.update_resluts_line()
        
    def press_button_2(self):
        self.operation_string_dict.append('2')
        self.update_resluts_line()
        
    def press_button_3(self):
        self.operation_string_dict.append('3')
        self.update_resluts_line()
        
    def press_button_4(self):
        self.operation_string_dict.append('4')
        self.update_resluts_line()
        
    def press_button_5(self):
        self.operation_string_dict.append('5')
        self.update_resluts_line()
        
    def press_button_6(self):
        self.operation_string_dict.append('6')
        self.update_resluts_line()
        
    def press_button_7(self):
        self.operation_string_dict.append('7')
        self.update_resluts_line()
        
    def press_button_8(self):
        self.operation_string_dict.append('8')
        self.update_resluts_line()
        
    def press_button_9(self):
        self.operation_string_dict.append('9')
        self.update_resluts_line()
        
    def press_button_0(self):
        self.operation_string_dict.append('0')
        self.update_resluts_line()
        
    def press_button_add(self):
        self.operation_string_dict.append('+')
        self.update_resluts_line()
        
    def press_button_sub(self):
        self.operation_string_dict.append('-')    
        self.update_resluts_line()
        
    def press_button_multi(self):
        self.operation_string_dict.append('*')    
        self.update_resluts_line()
        
    def press_button_divide(self):
        self.operation_string_dict.append('/')                                                                   
        self.update_resluts_line()
        
    def press_button_C(self):
        self.operation_string_dict = []           
        self.update_resluts_line()
         
    def press_button_equal(self):
        if self.operation_string_dict:
            self.operation_string_dict.append('=')
            calc = Calculator()
            for b in self.operation_string_dict:
                calc.push(b)
                self.ui.label_results.setText(str(calc._expression))
        
            self.operation_string_dict = []
        
    def update_resluts_line(self):
        op_str = ' '.join(self.operation_string_dict)
        if not op_str:
            self.ui.label_results.setText('0')
        else:
            self.ui.label_results.setText(op_str)
        

def main():
    Calculator = CalcHandler()
    Calculator.main_win_show()
        
main()    
    
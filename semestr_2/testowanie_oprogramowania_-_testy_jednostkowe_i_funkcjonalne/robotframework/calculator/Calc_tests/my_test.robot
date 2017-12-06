*** Settings ***
Documentation     Homework calculator test
Library           CalculatorLibrary.py

*** Test Cases ***
Push button 1
	Push button	1
	Result should be	1

Push button 2
	Push button	2
	Result should be	2

Push button 3
	Push button	3
	Result should be	3

Push button 4
	Push button	4
	Result should be	4

Push button 5
	Push button	5
	Result should be	5

Push button 6
	Push button	6
	Result should be	6

Push button 7
	Push button	7
	Result should be	7

Push button 8
	Push button	8
	Result should be	8

Push button 9
	Push button	9
	Result should be	9

Push button 0
	Push button	0
	Result should be	0

Push button +
	Push button	+
	Result should be	+

Push button -
	Push button	-
	Result should be	-

Push button *
	Push button	*
	Result should be	*

Push button /
	Push button	/
	Result should be	/

Push button clear
	Push button	1
	Result should be	1
	Push button	C
	Result should be	${EMPTY}

Multiple +
	Push button	3
	Push button	+
	Push button	+
	Push button	3
	Result should be	3+3

Multiple -
	Push button	3
	Push button	-
	Push button	-
	Push button	3
	Result should be	3-3

Multiple *
	Push button	3
	Push button	*
	Push button	*
	Push button	3
	Result should be	3*3

Multiple /
	Push button	3
	Push button	/
	Push button	/
	Push button	3
	Result should be	3/3

Operation +
	Push buttons	1+2=
	Result should be	3
	Push button	C

	Push buttons	-3+-4=
	Result should be	-7
	Push button	C

	Push buttons	-5+6=
	Result should be	1

Operation -
	Push buttons	9-8=
	Result should be	1
	Push button	C

	Push buttons	-7-6=
	Result should be	-13
	Push button	C

	Push buttons	-5--4=
	Result should be	-1

Operation *
	Push buttons	2*3=
	Result should be	6
	Push button	C

	Push buttons	-4*5=
	Result should be	-20
	Push button	C

	Push buttons	-6*-7=
	Result should be	42

Operation /
	Push buttons	9/3=
	Result should be	3
	Push button	C

	Push buttons	-8/4=
	Result should be	-2
	Push button	C

	Push buttons	-6/-3=
	Result should be	2

Operation ++
	Push buttons	2++3=
	Result should be	5

Operation --
	Push buttons	6--3=
	Result should be	9

Operation **
	Push buttons	3**3=
	Result should be	9

Operation //
	Push buttons	27//3=
	Result should be	9

Operation 1++=2=
	Push buttons	1++=2=
	Result should be	3

Operation 3--=3=
	Push buttons	3--=3=
	Result should be	6

Operation 3**=4=
	Push buttons	3**=4=
	Result should be	12

Operation 3//=3=
	Push buttons	3//=3=
	Result should be	1

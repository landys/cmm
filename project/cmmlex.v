#############################################################################
#                     U N R E G I S T E R E D   C O P Y
# 
# You are on day 105 of your 30 day trial period.
# 
# This file was produced by an UNREGISTERED COPY of Parser Generator. It is
# for evaluation purposes only. If you continue to use Parser Generator 30
# days after installation then you are required to purchase a license. For
# more information see the online help or go to the Bumble-Bee Software
# homepage at:
# 
# http://www.bumblebeesoftware.com
# 
# This notice must remain present in the file. It cannot be removed.
#############################################################################

#############################################################################
# cmmlex.v
# Lex verbose file generated from cmmlex.l.
# 
# Date: 06/26/06
# Time: 17:06:07
# 
# ALex Version: 2.07
#############################################################################


#############################################################################
# Expressions
#############################################################################

    1  "/*"

    2  "+"

    3  "-"

    4  "*"

    5  "/"

    6  ";"

    7  "("

    8  ")"

    9  "{"

   10  "}"

   11  "="

   12  "main"

   13  "return"

   14  "int"

   15  "void"

   16  "input"

   17  "output"

   18  [0-9]+

   19  [a-zA-Z]+

   20  \n

   21  [ \t]+

   22  .


#############################################################################
# States
#############################################################################

state 1
	INITIAL

	0x00 - 0x08 (9)    goto 3
	0x09               goto 4
	0x0a               goto 5
	0x0b - 0x1f (21)   goto 3
	0x20               goto 4
	0x21 - 0x27 (7)    goto 3
	0x28               goto 6
	0x29               goto 7
	0x2a               goto 8
	0x2b               goto 9
	0x2c               goto 3
	0x2d               goto 10
	0x2e               goto 3
	0x2f               goto 11
	0x30 - 0x39 (10)   goto 12
	0x3a               goto 3
	0x3b               goto 13
	0x3c               goto 3
	0x3d               goto 14
	0x3e - 0x40 (3)    goto 3
	0x41 - 0x5a (26)   goto 15
	0x5b - 0x60 (6)    goto 3
	0x61 - 0x68 (8)    goto 15
	0x69               goto 16
	0x6a - 0x6c (3)    goto 15
	0x6d               goto 17
	0x6e               goto 15
	0x6f               goto 18
	0x70 - 0x71 (2)    goto 15
	0x72               goto 19
	0x73 - 0x75 (3)    goto 15
	0x76               goto 20
	0x77 - 0x7a (4)    goto 15
	0x7b               goto 21
	0x7c               goto 3
	0x7d               goto 22
	0x7e - 0xff (130)  goto 3


state 2
	^INITIAL

	0x00 - 0x08 (9)    goto 3
	0x09               goto 4
	0x0a               goto 5
	0x0b - 0x1f (21)   goto 3
	0x20               goto 4
	0x21 - 0x27 (7)    goto 3
	0x28               goto 6
	0x29               goto 7
	0x2a               goto 8
	0x2b               goto 9
	0x2c               goto 3
	0x2d               goto 10
	0x2e               goto 3
	0x2f               goto 11
	0x30 - 0x39 (10)   goto 12
	0x3a               goto 3
	0x3b               goto 13
	0x3c               goto 3
	0x3d               goto 14
	0x3e - 0x40 (3)    goto 3
	0x41 - 0x5a (26)   goto 15
	0x5b - 0x60 (6)    goto 3
	0x61 - 0x68 (8)    goto 15
	0x69               goto 16
	0x6a - 0x6c (3)    goto 15
	0x6d               goto 17
	0x6e               goto 15
	0x6f               goto 18
	0x70 - 0x71 (2)    goto 15
	0x72               goto 19
	0x73 - 0x75 (3)    goto 15
	0x76               goto 20
	0x77 - 0x7a (4)    goto 15
	0x7b               goto 21
	0x7c               goto 3
	0x7d               goto 22
	0x7e - 0xff (130)  goto 3


state 3
	match 22


state 4
	0x09               goto 4
	0x20               goto 4

	match 21


state 5
	match 20


state 6
	match 7


state 7
	match 8


state 8
	match 4


state 9
	match 2


state 10
	match 3


state 11
	0x2a               goto 23

	match 5


state 12
	0x30 - 0x39 (10)   goto 12

	match 18


state 13
	match 6


state 14
	match 11


state 15
	0x41 - 0x5a (26)   goto 15
	0x61 - 0x7a (26)   goto 15

	match 19


state 16
	0x41 - 0x5a (26)   goto 15
	0x61 - 0x6d (13)   goto 15
	0x6e               goto 24
	0x6f - 0x7a (12)   goto 15

	match 19


state 17
	0x41 - 0x5a (26)   goto 15
	0x61               goto 25
	0x62 - 0x7a (25)   goto 15

	match 19


state 18
	0x41 - 0x5a (26)   goto 15
	0x61 - 0x74 (20)   goto 15
	0x75               goto 26
	0x76 - 0x7a (5)    goto 15

	match 19


state 19
	0x41 - 0x5a (26)   goto 15
	0x61 - 0x64 (4)    goto 15
	0x65               goto 27
	0x66 - 0x7a (21)   goto 15

	match 19


state 20
	0x41 - 0x5a (26)   goto 15
	0x61 - 0x6e (14)   goto 15
	0x6f               goto 28
	0x70 - 0x7a (11)   goto 15

	match 19


state 21
	match 9


state 22
	match 10


state 23
	match 1


state 24
	0x41 - 0x5a (26)   goto 15
	0x61 - 0x6f (15)   goto 15
	0x70               goto 29
	0x71 - 0x73 (3)    goto 15
	0x74               goto 30
	0x75 - 0x7a (6)    goto 15

	match 19


state 25
	0x41 - 0x5a (26)   goto 15
	0x61 - 0x68 (8)    goto 15
	0x69               goto 31
	0x6a - 0x7a (17)   goto 15

	match 19


state 26
	0x41 - 0x5a (26)   goto 15
	0x61 - 0x73 (19)   goto 15
	0x74               goto 32
	0x75 - 0x7a (6)    goto 15

	match 19


state 27
	0x41 - 0x5a (26)   goto 15
	0x61 - 0x73 (19)   goto 15
	0x74               goto 33
	0x75 - 0x7a (6)    goto 15

	match 19


state 28
	0x41 - 0x5a (26)   goto 15
	0x61 - 0x68 (8)    goto 15
	0x69               goto 34
	0x6a - 0x7a (17)   goto 15

	match 19


state 29
	0x41 - 0x5a (26)   goto 15
	0x61 - 0x74 (20)   goto 15
	0x75               goto 35
	0x76 - 0x7a (5)    goto 15

	match 19


state 30
	0x41 - 0x5a (26)   goto 15
	0x61 - 0x7a (26)   goto 15

	match 14


state 31
	0x41 - 0x5a (26)   goto 15
	0x61 - 0x6d (13)   goto 15
	0x6e               goto 36
	0x6f - 0x7a (12)   goto 15

	match 19


state 32
	0x41 - 0x5a (26)   goto 15
	0x61 - 0x6f (15)   goto 15
	0x70               goto 37
	0x71 - 0x7a (10)   goto 15

	match 19


state 33
	0x41 - 0x5a (26)   goto 15
	0x61 - 0x74 (20)   goto 15
	0x75               goto 38
	0x76 - 0x7a (5)    goto 15

	match 19


state 34
	0x41 - 0x5a (26)   goto 15
	0x61 - 0x63 (3)    goto 15
	0x64               goto 39
	0x65 - 0x7a (22)   goto 15

	match 19


state 35
	0x41 - 0x5a (26)   goto 15
	0x61 - 0x73 (19)   goto 15
	0x74               goto 40
	0x75 - 0x7a (6)    goto 15

	match 19


state 36
	0x41 - 0x5a (26)   goto 15
	0x61 - 0x7a (26)   goto 15

	match 12


state 37
	0x41 - 0x5a (26)   goto 15
	0x61 - 0x74 (20)   goto 15
	0x75               goto 41
	0x76 - 0x7a (5)    goto 15

	match 19


state 38
	0x41 - 0x5a (26)   goto 15
	0x61 - 0x71 (17)   goto 15
	0x72               goto 42
	0x73 - 0x7a (8)    goto 15

	match 19


state 39
	0x41 - 0x5a (26)   goto 15
	0x61 - 0x7a (26)   goto 15

	match 15


state 40
	0x41 - 0x5a (26)   goto 15
	0x61 - 0x7a (26)   goto 15

	match 16


state 41
	0x41 - 0x5a (26)   goto 15
	0x61 - 0x73 (19)   goto 15
	0x74               goto 43
	0x75 - 0x7a (6)    goto 15

	match 19


state 42
	0x41 - 0x5a (26)   goto 15
	0x61 - 0x6d (13)   goto 15
	0x6e               goto 44
	0x6f - 0x7a (12)   goto 15

	match 19


state 43
	0x41 - 0x5a (26)   goto 15
	0x61 - 0x7a (26)   goto 15

	match 17


state 44
	0x41 - 0x5a (26)   goto 15
	0x61 - 0x7a (26)   goto 15

	match 13


#############################################################################
# Summary
#############################################################################

1 start state(s)
22 expression(s), 44 state(s)


#############################################################################
# End of File
#############################################################################

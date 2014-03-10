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
# cmmyacc.v
# YACC verbose file generated from cmmyacc.y.
# 
# Date: 06/26/06
# Time: 19:14:11
# 
# AYACC Version: 2.07
#############################################################################


##############################################################################
# Rules
##############################################################################

    0  $accept : program $end

    1  program : main_decl

    2  main_decl : type_spec fun_ID SLB params SRB compound_stmt

    3  type_spec : INT

    4  fun_ID : MAIN

    5  params : VOID
    6         |

    7  compound_stmt : BLB var_decl_list stmt_list BRB

    8  var_decl_list : var_decl_list var_decl
    9                |

   10  $$1 :

   11  var_decl : type_spec ID $$1 SEMI

   12  stmt_list : stmt_list stmt
   13            |

   14  stmt : exp_stmt
   15       | I_stmt
   16       | O_stmt
   17       | ret_stmt

   18  exp_stmt : exp SEMI
   19           | SEMI

   20  ret_stmt : RETURN exp SEMI

   21  I_stmt : I_exp SEMI

   22  I_exp : INPUT SLB SRB

   23  O_stmt : OUTPUT SLB exp SRB SEMI

   24  exp : asgn_exp
   25      | algo_exp

   26  $$2 :

   27  asgn_exp : ID $$2 ASSIGN exp

   28  algo_exp : algo_exp addop term
   29           | term

   30  addop : PLUS
   31        | MINUS

   32  term : term multop factor
   33       | factor

   34  multop : MULT
   35         | DIV

   36  factor : NUM
   37         | ID
   38         | SLB exp SRB
   39         | I_exp
   40         | ERROR


##############################################################################
# States
##############################################################################

state 0
	$accept : . program $end

	INT  shift 1

	program  goto 2
	main_decl  goto 3
	type_spec  goto 4


state 1
	type_spec : INT .  (3)

	.  reduce 3


state 2
	$accept : program . $end  (0)

	$end  accept


state 3
	program : main_decl .  (1)

	.  reduce 1


state 4
	main_decl : type_spec . fun_ID SLB params SRB compound_stmt

	MAIN  shift 5

	fun_ID  goto 6


state 5
	fun_ID : MAIN .  (4)

	.  reduce 4


state 6
	main_decl : type_spec fun_ID . SLB params SRB compound_stmt

	SLB  shift 7


state 7
	main_decl : type_spec fun_ID SLB . params SRB compound_stmt
	params : .  (6)

	VOID  shift 8
	.  reduce 6

	params  goto 9


state 8
	params : VOID .  (5)

	.  reduce 5


state 9
	main_decl : type_spec fun_ID SLB params . SRB compound_stmt

	SRB  shift 10


state 10
	main_decl : type_spec fun_ID SLB params SRB . compound_stmt

	BLB  shift 11

	compound_stmt  goto 12


state 11
	compound_stmt : BLB . var_decl_list stmt_list BRB
	var_decl_list : .  (9)

	.  reduce 9

	var_decl_list  goto 13


state 12
	main_decl : type_spec fun_ID SLB params SRB compound_stmt .  (2)

	.  reduce 2


state 13
	compound_stmt : BLB var_decl_list . stmt_list BRB
	var_decl_list : var_decl_list . var_decl
	stmt_list : .  (13)

	INT  shift 1
	.  reduce 13

	type_spec  goto 14
	stmt_list  goto 15
	var_decl  goto 16


state 14
	var_decl : type_spec . ID $$1 SEMI

	ID  shift 17


state 15
	compound_stmt : BLB var_decl_list stmt_list . BRB
	stmt_list : stmt_list . stmt

	SEMI  shift 18
	SLB  shift 19
	BRB  shift 20
	RETURN  shift 21
	INPUT  shift 22
	OUTPUT  shift 23
	ID  shift 24
	NUM  shift 25
	ERROR  shift 26

	stmt  goto 27
	exp_stmt  goto 28
	I_stmt  goto 29
	O_stmt  goto 30
	ret_stmt  goto 31
	exp  goto 32
	I_exp  goto 33
	asgn_exp  goto 34
	algo_exp  goto 35
	term  goto 36
	factor  goto 37


state 16
	var_decl_list : var_decl_list var_decl .  (8)

	.  reduce 8


state 17
	var_decl : type_spec ID . $$1 SEMI
	$$1 : .  (10)

	.  reduce 10

	$$1  goto 38


state 18
	exp_stmt : SEMI .  (19)

	.  reduce 19


state 19
	factor : SLB . exp SRB

	SLB  shift 19
	INPUT  shift 22
	ID  shift 24
	NUM  shift 25
	ERROR  shift 26

	exp  goto 39
	I_exp  goto 40
	asgn_exp  goto 34
	algo_exp  goto 35
	term  goto 36
	factor  goto 37


state 20
	compound_stmt : BLB var_decl_list stmt_list BRB .  (7)

	.  reduce 7


state 21
	ret_stmt : RETURN . exp SEMI

	SLB  shift 19
	INPUT  shift 22
	ID  shift 24
	NUM  shift 25
	ERROR  shift 26

	exp  goto 41
	I_exp  goto 40
	asgn_exp  goto 34
	algo_exp  goto 35
	term  goto 36
	factor  goto 37


state 22
	I_exp : INPUT . SLB SRB

	SLB  shift 42


state 23
	O_stmt : OUTPUT . SLB exp SRB SEMI

	SLB  shift 43


state 24
	asgn_exp : ID . $$2 ASSIGN exp
	factor : ID .  (37)
	$$2 : .  (26)

	ASSIGN  reduce 26
	.  reduce 37

	$$2  goto 44


state 25
	factor : NUM .  (36)

	.  reduce 36


state 26
	factor : ERROR .  (40)

	.  reduce 40


state 27
	stmt_list : stmt_list stmt .  (12)

	.  reduce 12


state 28
	stmt : exp_stmt .  (14)

	.  reduce 14


state 29
	stmt : I_stmt .  (15)

	.  reduce 15


state 30
	stmt : O_stmt .  (16)

	.  reduce 16


state 31
	stmt : ret_stmt .  (17)

	.  reduce 17


state 32
	exp_stmt : exp . SEMI

	SEMI  shift 45


33: shift-reduce conflict (shift 46, reduce 39) on SEMI
state 33
	I_stmt : I_exp . SEMI
	factor : I_exp .  (39)

	SEMI  shift 46
	.  reduce 39


state 34
	exp : asgn_exp .  (24)

	.  reduce 24


state 35
	exp : algo_exp .  (25)
	algo_exp : algo_exp . addop term

	PLUS  shift 47
	MINUS  shift 48
	.  reduce 25

	addop  goto 49


state 36
	algo_exp : term .  (29)
	term : term . multop factor

	MULT  shift 50
	DIV  shift 51
	.  reduce 29

	multop  goto 52


state 37
	term : factor .  (33)

	.  reduce 33


state 38
	var_decl : type_spec ID $$1 . SEMI

	SEMI  shift 53


state 39
	factor : SLB exp . SRB

	SRB  shift 54


state 40
	factor : I_exp .  (39)

	.  reduce 39


state 41
	ret_stmt : RETURN exp . SEMI

	SEMI  shift 55


state 42
	I_exp : INPUT SLB . SRB

	SRB  shift 56


state 43
	O_stmt : OUTPUT SLB . exp SRB SEMI

	SLB  shift 19
	INPUT  shift 22
	ID  shift 24
	NUM  shift 25
	ERROR  shift 26

	exp  goto 57
	I_exp  goto 40
	asgn_exp  goto 34
	algo_exp  goto 35
	term  goto 36
	factor  goto 37


state 44
	asgn_exp : ID $$2 . ASSIGN exp

	ASSIGN  shift 58


state 45
	exp_stmt : exp SEMI .  (18)

	.  reduce 18


state 46
	I_stmt : I_exp SEMI .  (21)

	.  reduce 21


state 47
	addop : PLUS .  (30)

	.  reduce 30


state 48
	addop : MINUS .  (31)

	.  reduce 31


state 49
	algo_exp : algo_exp addop . term

	SLB  shift 19
	INPUT  shift 22
	ID  shift 59
	NUM  shift 25
	ERROR  shift 26

	I_exp  goto 40
	term  goto 60
	factor  goto 37


state 50
	multop : MULT .  (34)

	.  reduce 34


state 51
	multop : DIV .  (35)

	.  reduce 35


state 52
	term : term multop . factor

	SLB  shift 19
	INPUT  shift 22
	ID  shift 59
	NUM  shift 25
	ERROR  shift 26

	I_exp  goto 40
	factor  goto 61


state 53
	var_decl : type_spec ID $$1 SEMI .  (11)

	.  reduce 11


state 54
	factor : SLB exp SRB .  (38)

	.  reduce 38


state 55
	ret_stmt : RETURN exp SEMI .  (20)

	.  reduce 20


state 56
	I_exp : INPUT SLB SRB .  (22)

	.  reduce 22


state 57
	O_stmt : OUTPUT SLB exp . SRB SEMI

	SRB  shift 62


state 58
	asgn_exp : ID $$2 ASSIGN . exp

	SLB  shift 19
	INPUT  shift 22
	ID  shift 24
	NUM  shift 25
	ERROR  shift 26

	exp  goto 63
	I_exp  goto 40
	asgn_exp  goto 34
	algo_exp  goto 35
	term  goto 36
	factor  goto 37


state 59
	factor : ID .  (37)

	.  reduce 37


state 60
	algo_exp : algo_exp addop term .  (28)
	term : term . multop factor

	MULT  shift 50
	DIV  shift 51
	.  reduce 28

	multop  goto 52


state 61
	term : term multop factor .  (32)

	.  reduce 32


state 62
	O_stmt : OUTPUT SLB exp SRB . SEMI

	SEMI  shift 64


state 63
	asgn_exp : ID $$2 ASSIGN exp .  (27)

	.  reduce 27


state 64
	O_stmt : OUTPUT SLB exp SRB SEMI .  (23)

	.  reduce 23


##############################################################################
# Summary
##############################################################################

State 33 contains 1 shift-reduce conflict(s)


21 token(s), 25 nonterminal(s)
41 grammar rule(s), 65 state(s)


##############################################################################
# End of File
##############################################################################

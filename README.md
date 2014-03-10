# CMM (C Minus Minus Compiler)

本程序是大三下学期（2006年）编译原理的小程序，主要应用了lex和yacc技术进行词法语法分析，把C程序（支持语法有限）编译成汇编代码。详细的文档见“C Minus Minus Compiler Spec and Design.doc”

本程序代码包含五个文件：cmmlex.l，cmmyacc.y，types.h，code.h，code.c（在code中）。另外附有一个可执行文件cmm.exe和一个测试输入文件test.c（在bin中），bin中还包括文件MASM.EXE，LINK.EXE，ML.EXE（用来编译生成汇编程序为可执行文件，来自于MASM6.11），还包括文件test.t（符号表和语法树中间文件），test.s（生成的汇编代码文件，即最终目标文件），TEST.EXE（用MASM编译生成的test.s所得到的可执行文件）。包中还包含了Parser Generator 和 VC6.0的项目文件和生成结果（在project中），这些文件可直接在相应IDE下打开编译调试，不过首先要安装好Parser Generator，并在VC6.0配好相应路径。

程序应在控制台下执行，如编译test.c为汇编代码，可执行：</br>
\>cmm.exe test.c</br>
或者：</br>
\>cmm.exe</br>
之后在提示在输入要编译的文件名test.c</br>
即可生成test.t和test.s。若要把汇编代码再编译为可执行文件，可执行：</br>
\>ML.EXE test.s</br>
或者：</br>
\>MASM.EXE test.s</br>
\>LINK.EXE test.obj</br>
这样将生成中间文件test.obj和可执行文件test.exe，生成的test.exe可直接在控制台下执行：</br>
\>test.exe</br>
然后输入一个数字或字符等，输入之后，马上有东西输出，程序结束。</br>
这只是一个小测试。

cmm.exe对编译简单C语言时出错提示包含行号信息，并尽可能地给出错误原因。对于YACC的语法错误，只能找出一个错误之后即给出提示然后退出，对于其他如类型错误可以给出所有错误。

程序编译成功亦有相应提示。


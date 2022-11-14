import os
from os import system

OUTPUT = 1
STATUS = 2
OUT_STAT = 3
SUCCESS = 0

tests = """\
cat infile
<in pwd
cot infile
cd mandatory/..
cd jhg
cd mandatory/ lol
echo -n -z -n
echo -n coucou
echo -nz
echo lol -n
echo -nnnnnnnn ca va toi
echo -
pwd grop\
"""

test_split = tests.split('\n')


parsing_tests = """\
|cat infile
echo $USER
echo '$USER'\
"""
parsing_tests_split = parsing_tests.split('\n') 


def compare_output(cmd_line):

    size = 1
    cmd_mini = ' echo "' + cmd_line + '" | ../minishell > mini_output 2>/dev/null'
    cmd_bash = 'bash -c "' + cmd_line + '" > bash_output 2>/dev/null'
    ret_mini = system(cmd_mini)
    if (ret_mini % 256 == 0):
        ret_mini /= 256
    else: 
        ret_mini %= 256

    #print(f"status mini = {ret_mini}\n")
    ret_bash = system(cmd_bash)
    if (ret_bash % 256 == 0):
        ret_bash /= 256
    else: 
        ret_bash %= 256

    fd_mini = open("mini_output", "r")
    str_mini = fd_mini.read()
    print(f"str_mini = {str_mini}\n")
    str_mini_split = str_mini.split('\n')
    for(line) in str_mini_split:
        size += 1
    str_mini_split.pop(0)
    str_mini_split.pop(size - 4)

    fd_bash = open("bash_output", "r")
    str_bash = fd_bash.read()    
    str_bash_split = str_bash.split('\n')

    if (str_mini_split != str_bash_split and ret_mini != ret_bash):
         return (OUT_STAT)
    if (str_mini_split != str_bash_split):
        print(f"output mini = {str_mini_split}\n")
        print(f"output bash = {str_bash_split}\n")
        return (OUTPUT)
    if (ret_mini != ret_bash):
        print(f"status bash = {ret_bash}\n")
        print(f"status mini = {ret_mini}\n")
        return (STATUS)
    else:
        return (SUCCESS)

#for (cmd_line) in parsing_tests_split:
for (cmd_line) in test_split:
    ret = compare_output(cmd_line)
    if (ret == OUT_STAT):
        print(f"output and status error : {cmd_line}\n")
    elif (ret == OUTPUT):
        print(f"output error : {cmd_line}\n")
    elif (ret == STATUS):
        print(f"status error : {cmd_line}\n")
    elif (ret == SUCCESS):
        print(f"SUCCESS : {cmd_line}\n")
    print("-------------\n")

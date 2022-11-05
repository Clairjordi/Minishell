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
    ret_mini %= 255
    #print(f"status mini = {ret_mini}\n")
    ret_bash = system(cmd_bash)
    #print(f"status bash = {ret_bash}\n")
    ret_bash %= 255
    #print(f"status bash = {ret_bash}\n")

    fd_mini = open("mini_output", "r")
    str_mini = fd_mini.read()
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
        return (OUTPUT)
    if (ret_mini != ret_bash):
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

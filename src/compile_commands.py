# Generate compile_commands.json

cmd = "g++ -I. -Id:/loda-cpp/installed/x64-windows/include -D_CRT_SECURE_NO_WARNINGS -g -Wall -Werror -fmessage-length=0 -std=c++17 -O2 -c"
import os
compile_commands = open("compile_commands.json", "w")
compile_commands.write("[")
a = os.listdir("d:/loda-cpp/src")
flag = False
for i in a:
  if i.count(".") == 0 and i.count("Makefile") == 0 and i != "loda":
    b = os.listdir("d:/loda-cpp/src/" + i)
    for j in b:
      if j.count(".cpp") == 1:
        if flag:
          compile_commands.write(',')
        else:
          flag = True
        compile_commands.write('{"directory":"d:/loda-cpp/src","command":"' + cmd + ' -o ' + i + '/' + j.replace(".cpp", ".o") + ' ' + i + '/' + j + '","file":"' + i + '/' + j + '"}')
compile_commands.write("]")
compile_commands.close()
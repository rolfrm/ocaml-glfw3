gcc -std=c11 glfw3_stubs.c -c -fPIC
ocamlc -c -custom glfw3.ml
ocamlc -a  -o glfw3.cma glfw3.cmo glfw3_stubs.o -cclib -lglfw 

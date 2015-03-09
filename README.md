# ocaml-glfw3
Thin Ocaml wrapper for glfw3.

Example:
```ocaml
open Glfw3;;
glfwInit ();;
  
let no_mon =  no_monitor () in
    let no_win = no_window () in
    let win = glfwCreateWindow 200 200 "hello world!" no_mon no_win in
    glfwMakeContextCurrent win;
    (*...*)
    glfwDestroyWindow win;;

  glfwTerminate();;
```

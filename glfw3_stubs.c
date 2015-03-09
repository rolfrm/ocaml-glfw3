#include <stdbool.h>
#include <string.h>
#include <caml/misc.h>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/config.h>
#include <caml/custom.h>
#include <caml/callback.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "ml.h"

#define MAX_WINDOWS 10

struct _window_cb{
  value keycb;
  value charcb;
  value mouseposcb;
  value mousebtmcb;
  value cursorentercb;
  value scrollcb;
  GLFWwindow * win;
}window_cbs[MAX_WINDOWS];
typedef struct _window_cb window_cb;
bool init = false;
window_cb * get_window_cb(GLFWwindow * win){
  if(!init){
    for(int i = 0; i < MAX_WINDOWS; i++)
      window_cbs[i].win = NULL;
    init = true;
  }
  for(int i = 0; i < MAX_WINDOWS; i++)
    if(window_cbs[i].win == win)
      return window_cbs + i;
  return NULL;
}

value custom_copy(void * item, value (* allocator)(char const * str)){
  return allocator((char *) item);
}

static struct custom_operations glfw_monitor_ops = {
  "glfwMonitor",
  custom_finalize_default,
  custom_compare_default,
  custom_hash_default,
  custom_serialize_default,
  custom_deserialize_default
};

static struct custom_operations glfw_window_ops = {
  "glfwWindow",
  custom_finalize_default,
  custom_compare_default,
  custom_hash_default,
  custom_serialize_default,
  custom_deserialize_default
};

#define Window_val(v) (*((GLFWwindow **) Data_custom_val(v)))
#define Monitor_val(v) (*((GLFWmonitor **) Data_custom_val(v)))
#define Val_double(d) ((value)d)
value Val_monitor(GLFWmonitor * monitor){
  value r = alloc_custom(&glfw_monitor_ops, sizeof(GLFWmonitor *), 0 , 1);
  Monitor_val(r) = monitor;
  return r;
}

value Val_window(GLFWwindow * window){
  value r = alloc_custom(&glfw_window_ops, sizeof(GLFWwindow *), 0 , 1);
  Window_val(r)= window;
  return r;
}

value alloc_monitor(char const * str){
  return Val_monitor((GLFWmonitor *) str);
}

value alloc_window(char const * str){
  return Val_window((GLFWwindow *) str);
}

value Val_str(const char * str){
  int len = strlen(str);	 
  value ret = alloc_string(len); 
  memcpy(String_val(ret), str, len);
  return ret;
}

#define Str_val(value) String_val(value)

ML_0_(glfwInit,Val_int)
ML_0(glfwTerminate)
value ml_glfwGetVersion(){
  int mj,mi,r;
  glfwGetVersion(&mj,&mi,&r);
  value ret = caml_alloc_tuple(3);
  Field(ret,0) = Val_int(mj);
  Field(ret,1) = Val_int(mi);
  Field(ret,2) = Val_int(r);
  return ret;
}

ML_0_(glfwGetVersionString,Val_str)

value errorClosure;
void onGlfwError(int err, const char * message){
  caml_callback2(errorClosure,Val_int(err),Val_str(message));
}

value ml_glfwSetErrorCallback(value f){

  errorClosure = f;
  glfwSetErrorCallback(&onGlfwError);

  return Val_unit;
}

value ml_no_monitor(){
  return Val_monitor(NULL);
}

value ml_glfwGetMonitors(){
  int cnt;
  GLFWmonitor ** monitors = glfwGetMonitors(&cnt);
  int off = 0;
  GLFWmonitor * monitors2[cnt + 1];
  for(int i = 0; i < cnt;i++)
    monitors2[i] = monitors[i];
  monitors2[cnt] = NULL;
  return caml_alloc_array(&alloc_monitor,(const char **) monitors2);
}

value ml_printMonitor(value monitor){
  GLFWmonitor * mon = *((GLFWmonitor **) Data_custom_val(monitor));
  return Val_unit;
}

value ml_glfwGetPrimaryMonitor(){
return custom_copy(glfwGetPrimaryMonitor(),&alloc_monitor);
}

value ml_glfwGetMonitorPos(value monitor){
GLFWmonitor  * mon = *((GLFWmonitor **) Data_custom_val(monitor));
int x,y;
glfwGetMonitorPos(mon,&x, &y);

value ret = caml_alloc_tuple(2);
Field(ret,0) = Val_int(x);
Field(ret,1) = Val_int(y);
return ret;
}

value ml_glfwGetMonitorPhysicalSize(value monitor){
  GLFWmonitor  * mon = *((GLFWmonitor **) Data_custom_val(monitor));

  int x,y; 
  glfwGetMonitorPhysicalSize(mon,&x, &y);
  value ret = caml_alloc_tuple(2);
  Field(ret,0) = Val_int(x);
  Field(ret,1) = Val_int(y);
  return ret;
}


ML_1_(glfwGetMonitorName,Monitor_val,Val_str)

value monitorClosure;
void onGlfwMonitor(GLFWmonitor * monitor, int v){
  caml_callback2(monitorClosure,custom_copy(monitor,&alloc_monitor),Val_int(v));
}

value ml_glfwSetMonitorCallback(value f){
  monitorClosure = f;
  glfwSetMonitorCallback(&onGlfwMonitor);
  return Val_unit;
}

ML_0(glfwDefaultWindowHints)
ML_2(glfwWindowHint,Int_val,Int_val)

value ml_no_window(){
  return Val_window(NULL);
}

// external glfwCreateWindow : int -> int -> string -> monitor -> window -> unit == "ml_glfwCreateWindow";;
value ml_glfwCreateWindow(value _width, value _height, value _title, value _monitor, value _window){
  int width = Int_val(_width);
  int height = Int_val(_height);
  char * title = String_val(_title);
  GLFWmonitor * monitor = Monitor_val(_monitor);
  GLFWwindow * window = Window_val(_window);
  GLFWwindow * newwin = glfwCreateWindow(width, height, title, monitor, window);
  window_cb * cb = get_window_cb(NULL);
  cb->win = newwin;
  return custom_copy(newwin,&alloc_window);
}
 
// external glfwDestroyWindow : window -> unit = "ml_glfwDestroyWindow";;
//ML_1(glfwDestroyWindow,Window_val)
value ml_glfwDestroyWindow(value win){
  GLFWwindow * _win =  Window_val(win);
  window_cb * cb = get_window_cb(_win);
  cb->win = NULL;
  glfwDestroyWindow(_win);
}
// external glfwWindowShouldClose : window -> int = "ml_glfwWindowShouldClose";;
ML_1_(glfwWindowShouldClose,Window_val,Val_int)
// external glfwSetWindowShouldClose : window -> int -> unit = "ml_glfwSetWindowShouldClose";;
ML_2(glfwSetWindowShouldClose,Window_val,Val_int)
// external glfwSetWindowTitle : window -> string -> unit = "ml_glfwSetWindowTitle";;
ML_2(glfwSetWindowTitle,Window_val,Str_val)
// external glfwGetWindowPos : window -> int * int = "ml_glfwGetWindowPos";;
value ml_glfwGetWindowPos(value window){
  GLFWwindow  * mon = *((GLFWwindow **) Data_custom_val(window));
  int x,y;
  glfwGetWindowPos(mon,&x, &y);
  value ret = caml_alloc_tuple(2);
  Field(ret,0) = Val_int(x);
  Field(ret,1) = Val_int(y);
  return ret;
}
// external glfwSetWindowPos : window -> int * int -> unit = "ml_glfwSetWindowPos";;
value ml_glfwSetWindowPos(value window, value pos){
  GLFWwindow  * win = *((GLFWwindow **) Data_custom_val(window));
  int x = Val_int(Field(pos,0));
  int y  = Val_int(Field(pos,1));
  glfwSetWindowPos(win, x, y);
  return Val_unit;
}
// external glfwGetWindowSize : window -> int * int = "ml_glfwGetWindowSize";;
value ml_glfwGetWindowSize(value window){
  GLFWwindow  * mon = *((GLFWwindow **) Data_custom_val(window));
  int x,y;
  glfwGetWindowSize(mon,&x, &y);
  value ret = caml_alloc_tuple(2);
  Field(ret,0) = Val_int(x);
  Field(ret,1) = Val_int(y);
  return ret;
}

// external glfwSetWindowSize : window -> int * int -> unit = "ml_glfwSetWindowSize";;
value ml_glfwSetWindowSize(value window, value size){
  GLFWwindow  * win = *((GLFWwindow **) Data_custom_val(window));
  int x = Val_int(Field(size,0));
  int y  = Val_int(Field(size,1));
  glfwSetWindowSize(win, x, y);
  return Val_unit;
}
// external glfwGetFramebufferSize : window -> int * int = "ml_glfwGetFramebufferSize";;
value ml_glfwGetFramebufferSize(value window){
  GLFWwindow  * win = *((GLFWwindow **) Data_custom_val(window));
  int x,y;
  glfwGetFramebufferSize(win,&x, &y);
  value ret = caml_alloc_tuple(2);
  Field(ret,0) = Val_int(x);
  Field(ret,1) = Val_int(y);
  return ret;
}

// external glfwIconifyWindow : window -> unit = "ml_glfwIconifyWindow";;
ML_1(glfwIconifyWindow,Window_val)
// external glfwRestoreWindow : window -> unit = "ml_glfwRestoreWindow";;
ML_1(glfwRestoreWindow,Window_val)
// external glfwShowWindow : window -> unit = "ml_glfwShowWindow";;
ML_1(glfwShowWindow,Window_val)
// external glfwHideWindow : window -> unit = "ml_glfwHideWindow";;
ML_1(glfwHideWindow,Window_val)
// external glfwGetWindowMonitor : window -> monitor = "ml_glfwGetWindowMonitor";;
ML_1_(glfwGetWindowMonitor,Window_val,Val_monitor)
// external glfwGetWindowAttrib : window -> int -> int = "ml_glfwGetWindowAttrib";;
ML_2_(glfwGetWindowAttrib,Window_val,Int_val,Val_int)

//external glfwSetWindowPosCallback : window -> (window -> int * int -> unit) = "ml_glfwSetWindowPosCallback";;
//external glfwSetWindowSizeCallback : window -> (window -> int * int -> unit) = "ml_glfwSetWindowSizeCallback";;
//external glfwSetWindowCloseCallback : window -> (window -> unit) = "ml_glfwSetWindowCloseCallback";;
//external glfwSetWindowRefreshCallback : window -> (window -> unit) = "ml_glfwSetWindowRefreshCallback";;
//external glfwSetWindowFocusCallback : window -> (window -> unit) = "ml_glfwSetWindowFocusCallback";;
//external glfwSetWindowIconifyCallback : window -> (window -> unit) = "ml_glfwSetWindowIconifyCallback";;
//external glfwSetWindowFramebufferSizeCallback : window -> (window -> unit) = "ml_glfwSetWindowFramebufferSizeCallback";;
//external glfwPollEvents : unit -> unit = "ml_glfwPollEvents";;
ML_0(glfwPollEvents)
//external glfwWaitEvents : unit -> unit = "ml_glfwWaitEvents";;
ML_0(glfwWaitEvents)
//external glfwGetInputMode : window -> int -> int = "ml_glfwGetInputMode";;
ML_2_(glfwGetInputMode,Window_val,Int_val,Val_int)
//external glfwSetInputMode : window -> int -> int -> unit = "ml_glfwSetInputMode";;
ML_3(glfwSetInputMode,Window_val,Int_val,Int_val)
//external glfwGetKey : window -> int -> int = "ml_glfwGetKey";;
ML_2_(glfwGetKey,Window_val,Int_val,Val_int)
//external glfwGetMouseButton : window -> int -> int = "ml_glfwGetMouseButton";;
ML_2_(glfwGetMouseButton,Window_val,Val_int, Int_val)
//external glfwGetCursorPos : window -> double * double = "ml_glfwGetCursorPos";;
value ml_glfwGetCursorPos(value window){
  GLFWwindow  * win = Window_val(window);
  double x = 0.0, y = 1.0;
  glfwGetCursorPos(win, &x, &y);
  value ret = caml_alloc_tuple(2);
  Field(ret,0) = copy_double(x);
  Field(ret,1) = copy_double(y);
  
  return ret;
}
//external glfwSetCursorPos : window -> double * double -> unit = "ml_glfwSetCursorPos";;
value ml_glfwSetCursorPos(value window, value pos){
  GLFWwindow  * win = *((GLFWwindow **) Data_custom_val(window));
  double x = Double_val(Field(pos,0));
  double y  = Double_val(Field(pos,1));
  glfwSetCursorPos(win, x, y);
  return Val_unit;
}


//external glfwSetKeyCallback : window -> (window -> int -> int -> int -> int -> unit) -> unit = "ml_glfwSetKeyCallback";;
void keycb(GLFWwindow * win, int v1, int v2, int v3, int v4){
  window_cb * cbptr = get_window_cb(win);
  //leave_blocking_section();
  
  value _v1 = Val_int(v1);
  value _v2 = Val_int(v2);
  value _v3 = Val_int(v3);
  value _v4 = Val_int(v4);
  value args[] = {Val_window(win),_v1,_v2,_v3,_v4};
  callbackN(cbptr->keycb, 5, args);
  //enter_blocking_section();
}

value ml_glfwSetKeyCallback(value win, value cb){
  window_cb * cbptr = get_window_cb(Window_val(win));
  cbptr->keycb = cb;
  glfwSetKeyCallback(Window_val(win),&keycb);
}

//external glfwSetCharCallback : window -> (window -> int  -> unit) -> unit = "ml_glfwSetCharCallback";;
void charcb(GLFWwindow * win, unsigned int v1){
  window_cb * cbptr = get_window_cb(win);
  caml_callback2(cbptr->charcb,Val_window(win), Val_int((int)v1));
}

value ml_glfwSetCharCallback(value win, value cb){
  window_cb * cbptr = get_window_cb(Window_val(win));
  cbptr->charcb = cb;
  glfwSetCharCallback(Window_val(win),&charcb);
}

//external glfwSetMouseButtonCallback : window -> (window -> int -> int -> int  -> unit) -> unit = "ml_glfwSetMouseButtonCallback";;
void mousebtmcb(GLFWwindow * win, int v1, int v2, int v3){
  window_cb * cbptr = get_window_cb(win);
  value args[] = {Val_window(win), Val_int(v1), Val_int(v2), Val_int(v3)};
  callbackN(cbptr->mousebtmcb, 4, args);
}

value ml_glfwSetMouseButtonCallback(value win, value cb){
  window_cb * cbptr = get_window_cb(Window_val(win));
  cbptr->mousebtmcb = cb;
  glfwSetMouseButtonCallback(Window_val(win),&mousebtmcb);
}
//external glfwSetCursorPosCallback : window -> (window -> float * float -> unit) -> unit = "ml_glfwSetCursorPosCallback";;

void mouseposcb(GLFWwindow * win, double v1, double v2){
  window_cb * cbptr = get_window_cb(win);
  value ret = caml_alloc_tuple(2);
  Field(ret,0) = copy_double(v1);
  Field(ret,1) = copy_double(v2);
  callback2(cbptr->mouseposcb,Val_window(win), ret );
}

value ml_glfwSetCursorPosCallback(value win, value cb){
  window_cb * cbptr = get_window_cb(Window_val(win));
  cbptr->mouseposcb = cb;
  glfwSetCursorPosCallback(Window_val(win),&mouseposcb);
}

//external glfwSetCursorEnterCallback : window -> (window -> int -> unit) -> unit = "ml_glfwSetCursorEnterCallback";;

void cursorentercb(GLFWwindow * win,  int v1){
  window_cb * cbptr = get_window_cb(win);
  caml_callback2(cbptr->cursorentercb,Val_window(win), Val_int((int)v1));
}

value ml_glfwSetCursorEnterCallback(value win, value cb){
  window_cb * cbptr = get_window_cb(Window_val(win));
  cbptr->cursorentercb = cb;
  glfwSetCursorEnterCallback(Window_val(win),&cursorentercb);
}

//external glfwSetScrollCallback : window -> (window -> double * double -> unit) -> unit = "ml_glfwSetScrollCallback";;

void scrollcb(GLFWwindow * win, double v1, double v2){
  window_cb * cbptr = get_window_cb(win);
  value ret = caml_alloc_tuple(2);
  Field(ret,0) = copy_double(v1);
  Field(ret,1) = copy_double(v2);
  callback2(cbptr->scrollcb,Val_window(win), ret );
}

value ml_glfwSetScrollCallback(value win, value cb){
  window_cb * cbptr = get_window_cb(Window_val(win));
  cbptr->scrollcb = cb;
  glfwSetScrollCallback(Window_val(win),&scrollcb);
}


//external glfwMakeContextCurrent : window -> unit = "ml_glfwMakeContextCurrent";;
  ML_1(glfwMakeContextCurrent,Window_val)
//external glfwSwapBuffers : window -> unit = "ml_glfwSwapBuffers";;
  ML_1(glfwSwapBuffers,Window_val)
//external glfwSwapInterval : int -> unit = "ml_glfwSwapInterval";;
  ML_1(glfwSwapInterval,Int_val)

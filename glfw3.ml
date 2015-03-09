external glfwInit : unit -> int = "glfwInit";;
external glfwTerminate : unit -> unit = "glfwTerminate";;
external glfwGetVersionString : unit -> string = "ml_glfwGetVersionString";;
external glfwGetVersion : unit -> int * int * int = "ml_glfwGetVersion";;
external glfwSetErrorCallback : (int -> string -> unit) -> unit = "ml_glfwSetErrorCallback";;
type monitor;;
external no_monitor : unit -> monitor = "ml_no_monitor";;
external glfwGetMonitors : unit -> monitor array = "ml_glfwGetMonitors";;
external glfwGetPrimaryMonitor : unit -> monitor = "ml_glfwGetPrimaryMonitor";;
external glfwGetMonitorPos : monitor -> int * int = "ml_glfwGetMonitorPos";;
external glfwGetMonitorPhysicalSize : monitor -> int * int = "ml_glfwGetMonitorPhysicalSize";;
external glfwSetMonitorCallback : (monitor -> int -> unit) -> unit = "ml_glfwSetMonitorCallback";;

type vidmode = {width : int; height : int; red_bits : int; green_bits : int; blue_bits : int; refresh_ratr : int};;
(* not ported yet
external glfwGetVideoModes : monitor -> vidmode array = "ml_glfwGetVideoModes";;
external glfwGetVideoMode : monitor -> vidmode = "ml_glfwGetVideoMode";;
external glfwSetGamma : monitor -> float -> unit = "ml_glfwSetGamma";;
*)
(* not ported yet
  glfwGetGammaRamp
  glfwSetGammaRamp
*)
external glfwDefaultWindowHints : unit -> unit = "ml_glfwDefaultWindowHints";;
external glfwWindowHint : int -> int -> unit = "ml_glfwWindowHint";;
type window;;
external no_window : unit -> window = "ml_no_window";;
external glfwCreateWindow : int -> int -> string -> monitor -> window -> window = "ml_glfwCreateWindow";;
external glfwDestroyWindow : window -> unit = "ml_glfwDestroyWindow";;
external glfwWindowShouldClose : window -> int = "ml_glfwWindowShouldClose";;
external glfwSetWindowShouldClose : window -> int -> unit = "ml_glfwSetWindowShouldClose";;
external glfwSetWindowTitle : window -> string -> unit = "ml_glfwSetWindowTitle";;
external glfwGetWindowPos : window -> int * int = "ml_glfwGetWindowPos";;
external glfwSetWindowPos : window -> int * int -> unit = "ml_glfwSetWindowPos";;
external glfwGetWindowSize : window -> int * int = "ml_glfwGetWindowSize";;
external glfwSetWindowSize : window -> int * int -> unit = "ml_glfwSetWindowSize";;
external glfwGetFramebufferSize : window -> int * int = "ml_glfwGetFramebufferSize";;
external glfwIconifyWindow : window -> unit = "ml_glfwIconifyWindow";;
external glfwRestoreWindow : window -> unit = "ml_glfwRestoreWindow";;
external glfwShowWindow : window -> unit = "ml_glfwShowWindow";;
external glfwHideWindow : window -> unit = "ml_glfwHideWindow";;
external glfwGetWindowMonitor : window -> monitor = "ml_glfwGetWindowMonitor";;
external glfwGetWindowAttrib : window -> int -> int = "ml_glfwGetWindowAttrib";;
(* not ported yet 
  glfwSetWindowUserPointer
  glfwGetWindowUserPointer

external glfwSetWindowPosCallback : window -> (window -> int * int -> unit) = "ml_glfwSetWindowPosCallback";;
external glfwSetWindowSizeCallback : window -> (window -> int * int -> unit) = "ml_glfwSetWindowSizeCallback";;
external glfwSetWindowCloseCallback : window -> (window -> unit) = "ml_glfwSetWindowCloseCallback";;
external glfwSetWindowRefreshCallback : window -> (window -> unit) = "ml_glfwSetWindowRefreshCallback";;
external glfwSetWindowFocusCallback : window -> (window -> unit) = "ml_glfwSetWindowFocusCallback";;
external glfwSetWindowIconifyCallback : window -> (window -> unit) = "ml_glfwSetWindowIconifyCallback";;
external glfwSetWindowFramebufferSizeCallback : window -> (window -> unit) = "ml_glfwSetWindowFramebufferSizeCallback";;
*)
external glfwPollEvents : unit -> unit = "ml_glfwPollEvents";;
external glfwWaitEvents : unit -> unit = "ml_glfwWaitEvents";;
external glfwGetInputMode : window -> int -> int = "ml_glfwGetInputMode";;
external glfwSetInputMode : window -> int -> int -> unit = "ml_glfwSetInputMode";;
external glfwGetKey : window -> int -> int = "ml_glfwGetKey";;
external glfwGetMouseButton : window -> int -> int = "ml_glfwGetMouseButton";;
external glfwGetCursorPos : window -> float * float = "ml_glfwGetCursorPos";;
external glfwSetCursorPos : window -> float * float -> unit = "ml_glfwSetCursorPos";;

external glfwSetKeyCallback : window -> (window -> int -> int -> int -> int -> unit) -> unit = "ml_glfwSetKeyCallback";;

external glfwSetCharCallback : window -> (window -> int  -> unit) -> unit = "ml_glfwSetCharCallback";;

external glfwSetMouseButtonCallback : window -> (window -> int -> int -> int  -> unit) -> unit = "ml_glfwSetMouseButtonCallback";;
external glfwSetCursorPosCallback : window -> (window -> float * float -> unit) -> unit = "ml_glfwSetCursorPosCallback";;

external glfwSetCursorEnterCallback : window -> (window -> int -> unit) -> unit = "ml_glfwSetCursorEnterCallback";;
external glfwSetScrollCallback : window -> (window -> float * float -> unit) -> unit = "ml_glfwSetScrollCallback";;
(*
external glfwJoystickPresent : int -> int = "ml_glfwJoystickPresent";;
external glfwGetJoystickAxes : int -> float array = "ml_glfwGetJoystickAxes";;
external glfwGetJoystickButtons : int -> int array = "ml_glfwGetJoystickButtons";;
external glfwGetJoystickName : int -> string = "ml_glfwGetJoystickName";;
*)
(* not ported
 glfwSetClipboardString
 glfwGetClipboardString
 glfwGetTime
 glfwSetTime *)

external glfwMakeContextCurrent : window -> unit = "ml_glfwMakeContextCurrent";;
external glfwSwapBuffers : window -> unit = "ml_glfwSwapBuffers";;
external glfwSwapInterval : int -> unit = "ml_glfwSwapInterval";;

(* not ported
  glfwExtensionSupported
  glfwGetProcAddress
*)


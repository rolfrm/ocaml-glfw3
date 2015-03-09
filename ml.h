

#define Float_val(dbl) ((GLfloat) Double_val(dbl))
#define Addr_val(addr) ((GLvoid *) addr)
#define Val_addr(addr) ((value) addr)
#define Type_raw(raw) (GLenum_val(Kind_raw(raw)))
#define Type_void_raw(raw) Type_raw(raw), Void_raw(raw)


#define ML_0(cname) \
CAMLprim value ml_##cname (value unit) \
{ cname (); return Val_unit; }
#define ML_1(cname, conv1) \
CAMLprim value ml_##cname (value arg1) \
{ cname (conv1(arg1)); return Val_unit; }
#define ML_2(cname, conv1, conv2) \
CAMLprim value ml_##cname (value arg1, value arg2) \
{ cname (conv1(arg1), conv2(arg2)); return Val_unit; }
#define ML_3(cname, conv1, conv2, conv3) \
CAMLprim value ml_##cname (value arg1, value arg2, value arg3) \
{ cname (conv1(arg1), conv2(arg2), conv3(arg3)); return Val_unit; }
#define ML_4(cname, conv1, conv2, conv3, conv4) \
CAMLprim value ml_##cname (value arg1, value arg2, value arg3, value arg4) \
{ cname (conv1(arg1), conv2(arg2), conv3(arg3), conv4(arg4)); \
return Val_unit; }
#define ML_5(cname, conv1, conv2, conv3, conv4, conv5) \
CAMLprim value ml_##cname (value arg1, value arg2, value arg3, value arg4, \
value arg5) \
{ cname (conv1(arg1), conv2(arg2), conv3(arg3), conv4(arg4), conv5(arg5)); \
return Val_unit; }
#define ML_6(cname, conv1, conv2, conv3, conv4, conv5, conv6) \
CAMLprim value ml_##cname (value arg1, value arg2, value arg3, value arg4, \
value arg5, value arg6) \
{ cname (conv1(arg1), conv2(arg2), conv3(arg3), conv4(arg4), conv5(arg5), \
conv6(arg6)); \
return Val_unit; }
#define ML_7(cname, conv1, conv2, conv3, conv4, conv5, conv6, conv7) \
CAMLprim value ml_##cname (value arg1, value arg2, value arg3, value arg4, \
value arg5, value arg6, value arg7) \
{ cname (conv1(arg1), conv2(arg2), conv3(arg3), conv4(arg4), conv5(arg5), \
conv6(arg6), conv7(arg7)); \
return Val_unit; }
#define ML_8(cname, conv1, conv2, conv3, conv4, conv5, conv6, conv7, conv8) \
CAMLprim value ml_##cname (value arg1, value arg2, value arg3, value arg4, \
value arg5, value arg6, value arg7, value arg8) \
{ cname (conv1(arg1), conv2(arg2), conv3(arg3), conv4(arg4), conv5(arg5), \
conv6(arg6), conv7(arg7), conv8(arg8)); \
return Val_unit; }
#define ML_0_(cname, conv) \
CAMLprim value ml_##cname (value unit) \
{ return conv (cname ()); }
#define ML_1_(cname, conv1, conv) \
CAMLprim value ml_##cname (value arg1) \
{ return conv (cname (conv1(arg1))); }
#define ML_2_(cname, conv1, conv2, conv) \
CAMLprim value ml_##cname (value arg1, value arg2) \
{ return conv (cname (conv1(arg1), conv2(arg2))); }
#define ML_3_(cname, conv1, conv2, conv3, conv) \
CAMLprim value ml_##cname (value arg1, value arg2, value arg3) \
{ return conv (cname (conv1(arg1), conv2(arg2), conv3(arg3))); }
#define ML_4_(cname, conv1, conv2, conv3, conv4, conv) \
CAMLprim value ml_##cname (value arg1, value arg2, value arg3, value arg4) \
{ return conv (cname (conv1(arg1), conv2(arg2), conv3(arg3), conv4(arg4))); }
#define ML_5_(cname, conv1, conv2, conv3, conv4, conv5, conv) \
CAMLprim value ml_##cname (value arg1, value arg2, value arg3, value arg4, \
value arg5) \
{ return conv (cname (conv1(arg1), conv2(arg2), conv3(arg3), conv4(arg4), \
conv5(arg5))); }
#define ML_6_(cname, conv1, conv2, conv3, conv4, conv5, conv6, conv) \
CAMLprim value ml_##cname (value arg1, value arg2, value arg3, value arg4, \
value arg5, value arg6) \
{ return conv (cname (conv1(arg1), conv2(arg2), conv3(arg3), conv4(arg4), \
conv5(arg5), conv6(arg6))); }
#define ML_7_(cname, conv1, conv2, conv3, conv4, conv5, conv6, conv7, conv) \
CAMLprim value ml_##cname (value arg1, value arg2, value arg3, value arg4, \
value arg5, value arg6, value arg7) \
{ return conv (cname (conv1(arg1), conv2(arg2), conv3(arg3), conv4(arg4), \
conv5(arg5), conv6(arg6), conv7(arg7))); }
#define ML_8_(cname, conv1, conv2, conv3, conv4, conv5, conv6, conv7, conv8, \
conv) \
CAMLprim value ml_##cname (value arg1, value arg2, value arg3, value arg4, \
value arg5, value arg6, value arg7, value arg8) \
{ return conv (cname (conv1(arg1), conv2(arg2), conv3(arg3), conv4(arg4), \
conv5(arg5), conv6(arg6), conv7(arg7), conv8(arg8))); }

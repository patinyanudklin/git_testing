/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_grs_dragon_viewport_viewProg */

#ifndef _Included_com_grs_dragon_viewport_viewProg
#define _Included_com_grs_dragon_viewport_viewProg
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_grs_dragon_viewport_viewProg
 * Method:    SendViewportEvent
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_grs_dragon_viewport_viewProg_SendViewportEvent__I
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_grs_dragon_viewport_viewProg
 * Method:    SendViewportEvent
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_grs_dragon_viewport_viewProg_SendViewportEvent__Ljava_lang_String_2
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_grs_dragon_viewport_viewProg
 * Method:    FixupNCDialog
 * Signature: (Ljava/lang/String;Ljava/lang/String;Z)V
 */
JNIEXPORT void JNICALL Java_com_grs_dragon_viewport_viewProg_FixupNCDialog
  (JNIEnv *, jclass, jstring, jstring, jboolean);

/*
 * Class:     com_grs_dragon_viewport_viewProg
 * Method:    SetPandRNCDialogTopmost
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_com_grs_dragon_viewport_viewProg_SetPandRNCDialogTopmost
  (JNIEnv *, jclass, jboolean);

/*
 * Class:     com_grs_dragon_viewport_viewProg
 * Method:    logViewportP
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_grs_dragon_viewport_viewProg_logViewportP
  (JNIEnv *, jclass, jstring);

#ifdef __cplusplus
}
#endif
#endif

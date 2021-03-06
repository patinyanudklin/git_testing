/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_grs_dragon_ui_DImageHeader */

#ifndef _Included_com_grs_dragon_ui_DImageHeader
#define _Included_com_grs_dragon_ui_DImageHeader
#ifdef __cplusplus
extern "C" {
#endif
#undef com_grs_dragon_ui_DImageHeader_UNITSZ
#define com_grs_dragon_ui_DImageHeader_UNITSZ 16L
#undef com_grs_dragon_ui_DImageHeader_HDR_HIST_LEN
#define com_grs_dragon_ui_DImageHeader_HDR_HIST_LEN 65L
#undef com_grs_dragon_ui_DImageHeader_IMG_HIST_LEN
#define com_grs_dragon_ui_DImageHeader_IMG_HIST_LEN 257L
#undef com_grs_dragon_ui_DImageHeader_NUMLABELS
#define com_grs_dragon_ui_DImageHeader_NUMLABELS 256L
/*
 * Class:     com_grs_dragon_ui_DImageHeader
 * Method:    openImage
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_grs_dragon_ui_DImageHeader_openImage
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_grs_dragon_ui_DImageHeader
 * Method:    closeImage
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_grs_dragon_ui_DImageHeader_closeImage
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_grs_dragon_ui_DImageHeader
 * Method:    getImageNLines
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_grs_dragon_ui_DImageHeader_getImageNLines
  (JNIEnv *, jobject);

/*
 * Class:     com_grs_dragon_ui_DImageHeader
 * Method:    getImageNPix
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_grs_dragon_ui_DImageHeader_getImageNPix
  (JNIEnv *, jobject);

/*
 * Class:     com_grs_dragon_ui_DImageHeader
 * Method:    getImageFileType
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_grs_dragon_ui_DImageHeader_getImageFileType
  (JNIEnv *, jobject);

/*
 * Class:     com_grs_dragon_ui_DImageHeader
 * Method:    getImageBitsPerPix
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_grs_dragon_ui_DImageHeader_getImageBitsPerPix
  (JNIEnv *, jobject);

/*
 * Class:     com_grs_dragon_ui_DImageHeader
 * Method:    getImageMean
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_grs_dragon_ui_DImageHeader_getImageMean
  (JNIEnv *, jobject);

/*
 * Class:     com_grs_dragon_ui_DImageHeader
 * Method:    getImageMax
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_grs_dragon_ui_DImageHeader_getImageMax
  (JNIEnv *, jobject);

/*
 * Class:     com_grs_dragon_ui_DImageHeader
 * Method:    getImageMin
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_grs_dragon_ui_DImageHeader_getImageMin
  (JNIEnv *, jobject);

/*
 * Class:     com_grs_dragon_ui_DImageHeader
 * Method:    getImageVar
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_com_grs_dragon_ui_DImageHeader_getImageVar
  (JNIEnv *, jobject);

/*
 * Class:     com_grs_dragon_ui_DImageHeader
 * Method:    getImageSd
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_com_grs_dragon_ui_DImageHeader_getImageSd
  (JNIEnv *, jobject);

/*
 * Class:     com_grs_dragon_ui_DImageHeader
 * Method:    getImageHistElement
 * Signature: (I)J
 */
JNIEXPORT jlong JNICALL Java_com_grs_dragon_ui_DImageHeader_getImageHistElement
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_grs_dragon_ui_DImageHeader
 * Method:    getImageSource
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_grs_dragon_ui_DImageHeader_getImageSource
  (JNIEnv *, jobject);

/*
 * Class:     com_grs_dragon_ui_DImageHeader
 * Method:    getImageScene
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_grs_dragon_ui_DImageHeader_getImageScene
  (JNIEnv *, jobject);

/*
 * Class:     com_grs_dragon_ui_DImageHeader
 * Method:    getImageSubscene
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_grs_dragon_ui_DImageHeader_getImageSubscene
  (JNIEnv *, jobject);

/*
 * Class:     com_grs_dragon_ui_DImageHeader
 * Method:    getImageBand
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_grs_dragon_ui_DImageHeader_getImageBand
  (JNIEnv *, jobject);

/*
 * Class:     com_grs_dragon_ui_DImageHeader
 * Method:    getImageComment
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_grs_dragon_ui_DImageHeader_getImageComment
  (JNIEnv *, jobject);

/*
 * Class:     com_grs_dragon_ui_DImageHeader
 * Method:    getImageColorFile
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_grs_dragon_ui_DImageHeader_getImageColorFile
  (JNIEnv *, jobject);

/*
 * Class:     com_grs_dragon_ui_DImageHeader
 * Method:    getImageLabelCount
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_grs_dragon_ui_DImageHeader_getImageLabelCount
  (JNIEnv *, jobject);

/*
 * Class:     com_grs_dragon_ui_DImageHeader
 * Method:    getImageLabel
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_grs_dragon_ui_DImageHeader_getImageLabel
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_grs_dragon_ui_DImageHeader
 * Method:    getImageRegInit
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_grs_dragon_ui_DImageHeader_getImageRegInit
  (JNIEnv *, jobject);

/*
 * Class:     com_grs_dragon_ui_DImageHeader
 * Method:    getImageImgX
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_grs_dragon_ui_DImageHeader_getImageImgX
  (JNIEnv *, jobject);

/*
 * Class:     com_grs_dragon_ui_DImageHeader
 * Method:    getImageImgY
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_grs_dragon_ui_DImageHeader_getImageImgY
  (JNIEnv *, jobject);

/*
 * Class:     com_grs_dragon_ui_DImageHeader
 * Method:    getImageRefX
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_com_grs_dragon_ui_DImageHeader_getImageRefX
  (JNIEnv *, jobject);

/*
 * Class:     com_grs_dragon_ui_DImageHeader
 * Method:    getImageRefY
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_com_grs_dragon_ui_DImageHeader_getImageRefY
  (JNIEnv *, jobject);

/*
 * Class:     com_grs_dragon_ui_DImageHeader
 * Method:    getImageXCellSize
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_com_grs_dragon_ui_DImageHeader_getImageXCellSize
  (JNIEnv *, jobject);

/*
 * Class:     com_grs_dragon_ui_DImageHeader
 * Method:    getImageYCellSize
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_com_grs_dragon_ui_DImageHeader_getImageYCellSize
  (JNIEnv *, jobject);

/*
 * Class:     com_grs_dragon_ui_DImageHeader
 * Method:    getImageUnitname
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_grs_dragon_ui_DImageHeader_getImageUnitname
  (JNIEnv *, jobject);

/*
 * Class:     com_grs_dragon_ui_DImageHeader
 * Method:    getImageZScale
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_com_grs_dragon_ui_DImageHeader_getImageZScale
  (JNIEnv *, jobject);

/*
 * Class:     com_grs_dragon_ui_DImageHeader
 * Method:    getImageZOffset
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_com_grs_dragon_ui_DImageHeader_getImageZOffset
  (JNIEnv *, jobject);

/*
 * Class:     com_grs_dragon_ui_DImageHeader
 * Method:    getImageZUnit
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_grs_dragon_ui_DImageHeader_getImageZUnit
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif

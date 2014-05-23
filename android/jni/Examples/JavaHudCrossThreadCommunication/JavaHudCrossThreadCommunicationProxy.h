/*
 * JavaHudCrossThreadCommunicationProxy.h
 */

#ifndef JAVAHUDCROSSTHREADCOMMUNICATIONPROXY_H_
#define JAVAHUDCROSSTHREADCOMMUNICATIONPROXY_H_

#include <jni.h>

extern "C"
{
    JNIEXPORT void JNICALL Java_com_eegeo_examples_ThemeReaderWriterHud_setCurrentTheme(JNIEnv* jenv, jobject obj,
    		jlong nativeAppWindowPtr,
    		jstring name);

    JNIEXPORT void JNICALL Java_com_eegeo_examples_ThemeReaderWriterHud_readCurrentThemeName(JNIEnv* jenv, jobject obj,
    		jlong nativeObjectPtr);
}

#endif /* JAVAHUDCROSSTHREADCOMMUNICATIONPROXY_H_ */

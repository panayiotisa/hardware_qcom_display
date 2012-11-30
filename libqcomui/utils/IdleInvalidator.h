/*
 * Copyright (c) 2012, Code Aurora Forum. All rights reserved.

 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Code Aurora Forum, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef INCLUDE_IDLEINVALIDATOR
#define INCLUDE_IDLEINVALIDATOR

#include <cutils/log.h>
#include <utils/threads.h>

typedef void (*InvalidatorHandler)(void*);

class IdleInvalidator : public android::Thread {
    void *mHwcContext;
    bool mSleepAgain;
    unsigned int mSleepTime;
    static InvalidatorHandler mHandler;
    //This is a strong pointer just because this class derives indirectly from
    //RefBase. The instance having a process-lifetime, there is no need for ref
    //counting, so will never be exposed to clients.
    static android::sp<IdleInvalidator> sInstance;
    IdleInvalidator();
public:
    virtual ~IdleInvalidator(){}
    //init handler, store hwc context, init sleep time
    int init(InvalidatorHandler reg_handler, void* user_data, unsigned int
            idleSleepTime);
    //Called on mdp-comp update
    void markForSleep();
    //Overrides
    virtual bool        threadLoop();
    virtual int         readyToRun();
    virtual void        onFirstRef();
    static IdleInvalidator *getInstance();
};

#endif // INCLUDE_IDLEINVALIDATOR

/*
 * Copyright (c) 2011, INTEL CORPORATION
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 * Neither the name of INTEL CORPORATION nor the names of its contributors may
 * be used to endorse or promote products derived from this software without specific
 * prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include "base_allocator.h"

struct sBuffer
{
    union
    {
        mfxU32 id;
        char   idName[4];
    };
    mfxU32 nbytes;
    mfxU16 type;
};

struct sFrame
{
    union
    {
        mfxU32 id;
        char   idName[4];
    };
    mfxFrameInfo    info;
};

struct SysMemAllocatorParams : mfxAllocatorParams
{
    MFXBufferAllocator* pBufferAllocator;
}; 

class SysMemFrameAllocator: public BaseFrameAllocator
{
public:
    SysMemFrameAllocator();
    virtual ~SysMemFrameAllocator(); 

    virtual mfxStatus Init(mfxAllocatorParams* pParams);
    virtual mfxStatus Close();

protected:
    virtual mfxStatus LockFrame(mfxMemId mid, mfxFrameData* ptr);
    virtual mfxStatus UnlockFrame(mfxMemId mid, mfxFrameData* ptr);
    virtual mfxStatus GetFrameHDL(mfxMemId mid, mfxHDL* handle);       
    virtual mfxStatus CheckRequestType(mfxFrameAllocRequest* request);
    virtual mfxStatus ReleaseResponse(mfxFrameAllocResponse* response);
    virtual mfxStatus AllocImpl(mfxFrameAllocRequest* request, mfxFrameAllocResponse* response);

    MFXBufferAllocator* m_pBufferAllocator;
    bool m_bOwnBufferAllocator;
};

class SysMemBufferAllocator : public MFXBufferAllocator
{
public:
    SysMemBufferAllocator();
    virtual ~SysMemBufferAllocator();  

protected:
    virtual mfxStatus AllocBuffer(mfxU32 nbytes, mfxU16 type, mfxMemId* mid);
    virtual mfxStatus LockBuffer(mfxMemId mid, mfxU8** ptr);
    virtual mfxStatus UnlockBuffer(mfxMemId mid);    
    virtual mfxStatus FreeBuffer(mfxMemId mid); 
};
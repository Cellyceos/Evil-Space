//
//  FHAIFormat.h
//  HAI File Format.
//
//  Created by Kirill Bravichev on 03/15/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "IFIleFormat.h"


class FHAIFormat : public IFIleFormat
{
public:
    static constexpr float FRAME_TIME{ 50.0f };
    static TUniquePtr<FHAIFormat> Load(const FStringView& FileName);

    virtual ~FHAIFormat();

    virtual TSharedPtr<const ASurfaceClass> GetFrame(uint32 FrameIdx) const override { return Frames[FrameIdx]->shared_from_this(); }
    virtual uint32 GetFrameCount() const override { return static_cast<uint32>(Frames.size()); }

private:
    TArray<TSharedPtr<ASurfaceClass>> Frames;
};

//
//  FHAIFormat.h
//  HAI File Format.
//
//  Created by Kirill Bravichev on 03/15/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "CoreMinimal.h"


class FHAIFormat
{
public:
    static constexpr float FRAME_TIME{ 50.0f };
    static TUniquePtr<FHAIFormat> Load(const FStringView& FileName);

    virtual ~FHAIFormat();

    float GetWidth() const { return Width; }
    float GetHeight() const { return Height; }

    TSharedPtr<const ASurfaceClass> GetFrame(uint32 FrameIdx) const { return Frames[FrameIdx]->shared_from_this(); }
    uint32 GetFrameCount() const { return static_cast<uint32>(Frames.size()); }

private:
    float Width{ 0.0f };
    float Height{ 0.0f };

    TArray<TSharedPtr<ASurfaceClass>> Frames;
};

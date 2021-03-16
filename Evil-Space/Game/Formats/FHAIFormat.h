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

    void Draw(const TSharedPtr<ARendererClass>& Renderer) const;
private:
    float Width{ 0.0f };
    float Height{ 0.0f };
    uint32 FrameCount{ 0 };

    TArray<TSharedPtr<ASurfaceClass>> Frames;
};

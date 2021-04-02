//
//  FFileFormat.h
//  File Format Interface.
//
//  Created by Kirill Bravichev on 03/17/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "CoreMinimal.h"


class IFIleFormat
{
public:
    static TUniquePtr<IFIleFormat> Load(const FStringView& FileName) { return nullptr; }

    virtual ~IFIleFormat() = default;

    float GetWidth() const { return Width; }
    float GetHeight() const { return Height; }

    const FString GetFileName() const { return FileName; }

    virtual TSharedPtr<ATextureClass> GetFrame(uint32 FrameIdx) const = 0;
    virtual uint32 GetFrameCount() const = 0;

protected:
    FString FileName;

    float Width{ 0.0f };
    float Height{ 0.0f };
};


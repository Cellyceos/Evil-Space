//
//  FGImageFormat.h
//  GImage File Format.
//
//  Created by Kirill Bravichev on 03/17/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "IFileFormat.h"


class FGImageFormat : public IFileFormat
{
public:
    static TUniquePtr<FGImageFormat> Load(const FPath& FileName);
    static TSharedPtr<ATextureClass> LoadFrame(std::ifstream& FileStream);

    virtual ~FGImageFormat();

    virtual TSharedPtr<ATextureClass> GetFrame(uint32 = 0) const override { return Frame->shared_from_this(); }
    virtual uint32 GetFrameCount() const override { return 1u; }

private:
    TSharedPtr<ATextureClass> Frame;
};

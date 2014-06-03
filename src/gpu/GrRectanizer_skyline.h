/*
* Copyright 2014 Google Inc.
*
* Use of this source code is governed by a BSD-style license that can be
* found in the LICENSE file.
*/

#ifndef GrRectanizer_skyline_DEFINED
#define GrRectanizer_skyline_DEFINED

#include "GrRectanizer.h"
#include "SkTDArray.h"

// Pack rectangles and track the current silhouette
// Based in part on Jukka Jylänki's work at http://clb.demon.fi
class GrRectanizerSkyline : public GrRectanizer {
public:
    GrRectanizerSkyline(int w, int h) : INHERITED(w, h) {
        this->reset();
    }

    virtual ~GrRectanizerSkyline() { }

    virtual void reset() SK_OVERRIDE{
        fAreaSoFar = 0;
        fSkyline.reset();
        SkylineSegment* seg = fSkyline.append(1);
        seg->fX = 0;
        seg->fY = 0;
        seg->fWidth = this->width();
    }

    virtual bool addRect(int w, int h, GrIPoint16* loc) SK_OVERRIDE;

    virtual float percentFull() const SK_OVERRIDE{
        return fAreaSoFar / ((float)this->width() * this->height());
    }

private:
    struct SkylineSegment {
        int  fX;
        int  fY;
        int  fWidth;
    };

    SkTDArray<SkylineSegment> fSkyline;

    int32_t fAreaSoFar;

    bool rectangleFits(int skylineIndex, int width, int height, int* y) const;
    void addSkylineLevel(int skylineIndex, int x, int y, int width, int height);

    typedef GrRectanizer INHERITED;
};

#endif

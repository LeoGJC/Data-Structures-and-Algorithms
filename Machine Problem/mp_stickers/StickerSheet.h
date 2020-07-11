/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include <string>
#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "Image.h"
using namespace cs225;

class StickerSheet {
    public:
    StickerSheet(const Image & picture,unsigned max);
    ~StickerSheet();
    StickerSheet (const StickerSheet &other);
    int addSticker (Image & sticker, unsigned x, unsigned y);
    void changeMaxStickers (unsigned max);
    Image * getSticker(unsigned index);
    const StickerSheet & operator=(const StickerSheet & other);
    void removeSticker(unsigned index);
    Image render () const;
    bool translate(unsigned index, unsigned x, unsigned y);
    private:
    Image copyBase;
    Image ** sticker_;
    unsigned max_;
    unsigned *x_;
    unsigned *y_;
    unsigned index_;
    void copy(const StickerSheet &other);
    void clear();

    
};


 

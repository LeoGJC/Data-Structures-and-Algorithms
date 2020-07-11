#include "Image.h"
#include "StickerSheet.h"
#include <string>
#include <algorithm>



StickerSheet::StickerSheet(const Image & picture,unsigned max) {
    copyBase = picture;
    max_ = max;
    sticker_ = new Image*[max_];
    x_ = new unsigned[max_];
    y_ = new unsigned[max_];
    index_ = 0;
    for(unsigned i = 0; i < max_; i++) {
        sticker_[i] = NULL;
    }
}

StickerSheet::~StickerSheet() {
    clear();
}

void StickerSheet::clear() {
    for (unsigned i = 0;i < max_; i++) {
        if (sticker_[i] != NULL) {
            delete sticker_[i];
            sticker_[i] = NULL;
        }
    }
    delete[] sticker_;
    sticker_ = NULL;
    delete[] x_;
    x_ = NULL;
    delete[] y_;
    y_ = NULL;
}

StickerSheet::StickerSheet (const StickerSheet &other) {
   copy(other);
}

void StickerSheet::copy(const StickerSheet &other) {
    max_ = other.max_;
    index_ = other.index_;
    copyBase =other.copyBase;
    sticker_ = new Image*[max_];
    x_ = new unsigned[max_];
    y_ = new unsigned[max_];
    for(unsigned i = 0; i < max_; i++) {
        sticker_[i] = NULL;
    }
    for(unsigned i = 0; i < max_; i++) {
        x_[i] = other.x_[i];
        y_[i] = other.y_[i];
        if(other.sticker_[i] == NULL) {
            sticker_[i] = NULL;
        } else {
            sticker_[i] = new Image(*(other.sticker_[i]));
        }
    }
}
 
int StickerSheet::addSticker (Image & sticker, unsigned x, unsigned y) {
    if (index_< max_) {
        for (unsigned i = 0; i < max_; i++) {
            if (sticker_[i] == NULL) {
                sticker_[i]=new Image();
                *sticker_[i] = sticker;
                x_[i] = x;
                y_[i] = y;   
                index_++;
                return i;
            }
        }
    }
    return -1;
}

void StickerSheet::changeMaxStickers (unsigned max) {
    if(index_ == max) {
        return;
    }
    unsigned * newx_ = new unsigned[max];
    unsigned * newy_ = new unsigned[max];
    Image ** newsticker_ = new Image*[max];
    for (unsigned i = 0; i < max; i++) {
        newsticker_[i] = NULL;
    }
    if (index_ < max) {
        for (unsigned i = 0; i < index_; i++) {
            if (sticker_[i] != NULL) {
                newsticker_[i] = new Image();
                * newsticker_[i] = * sticker_[i];
                newx_[i] = x_[i];
                newy_[i] = y_[i];
            }
        }
        
    } else {
        for (unsigned i = 0; i < max; i++) {
            if (sticker_[i] != NULL) {
                newsticker_[i] = new Image();
                * newsticker_[i] = * sticker_[i];
                newx_[i] = x_[i];
                newy_[i] = y_[i];
            }
        }
        index_ = max;
    }
    
    clear();
    sticker_ = newsticker_;
    newsticker_ = NULL;
    x_ = newx_;
    newx_ = NULL;
    y_ =  newy_;
    newy_ = NULL;
    max_ = max;

}

Image * StickerSheet::getSticker(unsigned index) {
    if(index < max_) {
        return sticker_[index];
    } else {
        return NULL;
    }
}

const StickerSheet & StickerSheet::operator=(const StickerSheet & other) {
    if (this == & other) {
        return *this;
    }
    clear();
    copy(other);
    return *this;
}

void StickerSheet::removeSticker(unsigned index) {
    if (index >=max_  || sticker_[index] == NULL) {
		return;
	} else {
        delete sticker_[index];
        for (unsigned i = index; i < max_ - 1; i++) {
            sticker_[i] = sticker_[i+1];
            x_[i] = x_[i+1];
            y_[i] = y_[i+1];
        }
		sticker_[max_ - 1] = NULL;
		x_[max_-1] = 0;
        y_[max_-1] = 0;
        index_--;
    }
}

Image StickerSheet::render () const {
    Image printImage = copyBase;
    unsigned maxwidth = copyBase.width();
	unsigned maxheight = copyBase.height();
    
	for (unsigned i = 0; i < index_; i++) {
        if (sticker_[i] != NULL) {
            maxwidth = max(sticker_[i]->width() + x_[i], maxwidth);
    	    maxheight = max(sticker_[i]->height() + y_[i], maxheight);
        }
	}
    
	printImage.resize(maxwidth, maxheight);

	for (unsigned i = 0; i < index_; i++) {
        if (sticker_[i] != NULL) {
            for (unsigned x = x_[i]; x < (sticker_[i]->width() + x_[i]); x++) {
                for (unsigned y = y_[i]; y < (sticker_[i]->height()+ y_[i]); y++) {
                    if (sticker_[i]->getPixel((x - x_[i]), (y - y_[i])).a != 0) {
                        printImage.getPixel(x, y) = sticker_[i]->getPixel((x - x_[i]), (y - y_[i]));
                    }
                }	
			}
		}
	}
	return printImage;
    

}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
    if (sticker_[index] == NULL){
		return false;
	} else if(index >= index_){
        return false;
    } else {
        x_[index]=x;
        y_[index]=y;
        return true;
    }
}
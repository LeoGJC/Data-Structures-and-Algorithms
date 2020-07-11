#include "Image.h"
#include <string>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
using namespace std;
using namespace cs225;


    void Image::darken() {
        for (unsigned x = 0; x < this->width(); x++) {
            for (unsigned y = 0; y < this->height(); y++) {
                HSLAPixel & pixel = this->getPixel(x, y);
                if (pixel.l < 0.1) {
                    pixel.l = 0;
                } else {
                    pixel.l -= 0.1;
                }
                
            }
        }   
    }
    void Image::darken(double amount) {
        for (unsigned x = 0; x < this->width(); x++) {
            for (unsigned y = 0; y < this->height(); y++) {
                HSLAPixel & pixel = this->getPixel(x, y);
                if (amount >= 0) {
                    if (pixel.l < amount) {
                        pixel.l = 0;
                    } else {
                        pixel.l -= amount;
                    }
                } else {
                    if (pixel.l + amount < 0) {
                        pixel.l = 0;
                    } else {
                        pixel.l += amount;
                    }
                }
            }
        }      
    }
     void Image::desaturate() {
        for (unsigned x = 0; x < this->width(); x++) {
            for (unsigned y = 0; y < this->height(); y++) {
                HSLAPixel & pixel = this->getPixel(x, y);
                if (pixel.s < 0.1) {
                    pixel.s = 0;
                } else {
                    pixel.s -= 0.1;
                }
            } 
        }   
    }
    void Image::desaturate(double amount) {
        for (unsigned x = 0; x < this->width(); x++) {
            for (unsigned y = 0; y < this->height(); y++) {
                HSLAPixel & pixel = this->getPixel(x, y);
                if (amount >= 0) {
                    if (pixel.s < amount) {
                        pixel.s = 0;
                    } else {
                        pixel.s -= amount;
                    }
                } else {
                    if (pixel.s + amount < 0) {
                        pixel.s = 0;
                    } else {
                        pixel.s += amount;
                    }
                }
            }
        }   
    }
    void Image::grayscale() {
        for (unsigned x = 0; x < this->width(); x++) {
            for (unsigned y = 0; y < this->height(); y++) {
                HSLAPixel & pixel = this->getPixel(x, y);
                pixel.s = 0;
            }
        }
    }
    void Image::illinify() {
        for (unsigned x = 0; x < this->width(); x++) {
            for (unsigned y = 0; y < this->height(); y++) {
                HSLAPixel & pixel = this->getPixel(x, y);
                if (pixel.h>=113.5 && pixel.h<=293.5) {
                    pixel.h = 216;
                } else {
                    pixel.h = 11;
                }
            }
        }
    }
    void Image::lighten() {
        for (unsigned x = 0; x < this->width(); x++) {
            for (unsigned y = 0; y < this->height(); y++) {
                HSLAPixel & pixel = this->getPixel(x, y);
                if (pixel.l > 0.9) {
                    pixel.l = 1.0;
                } else {
                    pixel.l += 0.1;
                }
            }
            
        }   
    }
    void Image::lighten(double amount) {
        for (unsigned x = 0; x < this->width(); x++) {
            for (unsigned y = 0; y < this->height(); y++) {
                HSLAPixel & pixel = this->getPixel(x, y);
                if (amount >= 0) {
                    if (pixel.l > 1 - amount) {
                        pixel.l = 1;
                    } else {
                        pixel.l += amount;
                    }
                } else {
                    if (pixel.l - amount > 1) {
                        pixel.l = 0;
                    } else {
                        pixel.l -= amount;
                    }
                }
            }
        }   
    }
    void Image::rotateColor(double degrees) {
        for (unsigned x = 0; x < this->width(); x++) {
            for (unsigned y = 0; y < this->height(); y++) {
                HSLAPixel & pixel = this->getPixel(x, y);
                if (degrees >= 0) {
                    while(degrees >= 360) {
                        degrees -= 360;
                    }
                    if (pixel.h + degrees >= 360) {
                        pixel.h = pixel.h + degrees - 360;
                    } else {
                        pixel.h += degrees;
                    }
                } else {
                    while(degrees <= -360) {
                        degrees += 360;
                    }
                    if (pixel.h - degrees >= 360) {
                        pixel.h = pixel.h - degrees - 360;
                    } else {
                        pixel.h -= degrees;
                    }
                }
            }
        }   
    }
    void Image::saturate() {
        for (unsigned x = 0; x < this->width(); x++) {
            for (unsigned y = 0; y < this->height(); y++) {
                HSLAPixel & pixel = this->getPixel(x, y);
                if (pixel.s > 0.9) {
                    pixel.s = 1;
                } else {
                    pixel.s += 0.1;
                }
            }
        }   
    }
    void Image::saturate(double amount) {
        for (unsigned x = 0; x < this->width(); x++) {
            for (unsigned y = 0; y < this->height(); y++) {
                HSLAPixel & pixel = this->getPixel(x, y);
                if (amount >= 0) {
                    if (pixel.s > 1 - amount) {
                        pixel.s = 1;
                    } else {
                        pixel.s += amount;
                    }
                } else {
                    if (pixel.s - amount > 1) {
                        pixel.s = 0;
                    } else {
                        pixel.s -= amount;
                    }
                }
            }
        }   
    }
    void Image::scale(double factor) {
        Image png = *this;
        unsigned scalewidth = factor*width();
        unsigned scaleheight = factor*height();
        png.resize(scalewidth, scaleheight);
        for (unsigned x = 0; x < png.width(); x++) {
            for (unsigned y = 0; y < png.height(); y++) {
                HSLAPixel & pixel = png.getPixel(x,y);
                unsigned xw = x/factor;
                unsigned xh = y/factor;
                HSLAPixel & originalPixel = this->getPixel(xw,xh);
                pixel=originalPixel;
            }
        }
        (*this) = png;   
    }	
    void Image::scale(unsigned w, unsigned h) {
        double ratiow = (double) w / this->width();
        double ratioh = (double) h / this->height();
        double factor1;
        if(ratiow < ratioh) {
            factor1 = ratiow;
        } else {
            factor1 = ratioh;
        };
        scale(factor1);
    }

    

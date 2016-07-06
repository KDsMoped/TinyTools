/*
    Biquad.h
    
    Created 03.07.16.
 
    Author:  Dominik Koehler, Per Loenicker, Jan Selzer, Hendrik Bleier, Moritz Gueldenring, David Bau

================================================

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

================================================
 
 
 
 */

#ifndef Biquad_h
#define Biquad_h


enum {
    filterTypeHighPass = 0,
    filterTypeLowPass,
    filterTypeBandPass,
    filterTypeAllPass,
    
    filterOrder1 = 1,
    filterOrder2 = 2,
    filterOrder4 = 4,
    filterOrder6 = 6,
    filterOrder8 = 8,
    filterOrder10 = 10
};

class BiquadFilter {
public:
    BiquadFilter(int filterType, int filterOrder) : filterType(filterType), filterOrder(filterOrder) {}
    
    ~BiquadFilter(){}
    
    void processFilter(float *sample, int channel) {
        float x = *sample;
        float w1 = buffer[0][channel][0];
        float w2 = buffer[1][channel][0];
        
        // Compute difference equation
        float w = x - (coeffA1 * w1) - (coeffA2 * w2);
        float y = (coeffB0 * w) + (coeffB1 * w1) + (coeffB2 * w2);
        
        // Shift buffer values
        buffer[1][channel][0] = w1;
        buffer[0][channel][0] = w;
        
        if (filterOrder >= 4) {
            x = y;
            w1 = buffer[0][channel][1];
            w2 = buffer[1][channel][1];
            
            w = x - (coeffA1 * w1) - (coeffA2 * w2);
            y = (coeffB0 * w) + (coeffB1 * w1) + (coeffB2 * w2);
            
            buffer[1][channel][1] = w1;
            buffer[0][channel][1] = w;
        }
        if (filterOrder >= 6) {
            x = y;
            w1 = buffer[0][channel][2];
            w2 = buffer[1][channel][2];
            
            w = x - (coeffA1 * w1) - (coeffA2 * w2);
            y = (coeffB0 * w) + (coeffB1 * w1) + (coeffB2 * w2);
            
            buffer[1][channel][2] = w1;
            buffer[0][channel][2] = w;
        }
        if (filterOrder >= 8) {
            x = y;
            w1 = buffer[0][channel][3];
            w2 = buffer[1][channel][3];
            
            w = x - (coeffA1 * w1) - (coeffA2 * w2);
            y = (coeffB0 * w) + (coeffB1 * w1) + (coeffB2 * w2);
            
            buffer[1][channel][3] = w1;
            buffer[0][channel][3] = w;
        }
        if (filterOrder >= 10) {
            x = y;
            w1 = buffer[0][channel][4];
            w2 = buffer[1][channel][4];
            
            w = x - (coeffA1 * w1) - (coeffA2 * w2);
            y = (coeffB0 * w) + (coeffB1 * w1) + (coeffB2 * w2);
            
            buffer[1][channel][4] = w1;
            buffer[0][channel][4] = w;
        }
        
        *sample = y;
    }
    
    
    void setFilterCoeffs(float sr, float f, float q) {
        float k = tan((piFloat * f) / sr);
        
        if (filterType == filterTypeHighPass) {
            if (filterOrder == filterOrder1){
                coeffB0 = 1.f / (k + 1.f);
                coeffB1 = coeffB0 * -1.f;
                coeffB2 = 0.f;
                coeffA1 = (k - 1.f) / (k + 1.f);
                coeffA2 = 0.f;
            }
            else {
                coeffB0 = q / ((pow(k, 2.f) * q) + k + q);
                coeffB1 = (-2.f * q) / ((pow(k, 2.f) * q) + k + q);
                coeffB2 = coeffB0;
                coeffA1 = (2.f * q * (pow(k, 2.f) - 1)) / ((pow(k, 2.f) * q) + k + q);
                coeffA2 = ((pow(k, 2.f) * q) - k + q) / ((pow(k, 2.f) * q) + k + q);
            }
        }
        if (filterType == filterTypeLowPass) {
            if (filterOrder == filterOrder1) {
                coeffB0 = k / (k + 1.f);
                coeffB1 = coeffB0;
                coeffB2 = 0.f;
                coeffA1 = (k - 1.f) / (k + 1.f);
                coeffA2 = 0.f;
            }
            else {
                coeffB0 = (pow(k, 2.f) * q) / ((pow(k, 2.f) * q) + k + q);
                coeffB1 = (2.f * (pow(k, 2.f) * q)) / ((pow(k, 2.f) * q) + k + q);
                coeffB2 = coeffB0;
                coeffA1 = (2.f * q * (pow(k, 2.f) - 1.f)) / ((pow(k, 2.f) * q) + k + q);
                coeffA2 = ((pow(k, 2.f) * q) - k + q) / ((pow(k, 2.f) * q) + k + q);
            }
        }
        if (filterType == filterTypeBandPass) {
            coeffB0 = k / ((pow(k, 2.f) * q) + k + q);
            coeffB1 = 0.f;
            coeffB2 = coeffB0 * -1.f;
            coeffA1 = (2.f * q * (pow(k, 2.f) - 1.f)) / ((pow(k, 2.f) * q) + k + q);
            coeffA2 = ((pow(k, 2.f) * q) - k + q) / ((pow(k, 2.f) * q) + k + q);
        }
        if (filterType == filterTypeAllPass) {
            if (filterOrder == filterOrder1) {
                coeffB0 = (k - 1.f) / (k + 1.f);
                coeffB1 = 1.f;
                coeffB2 = 0.f;
                coeffA1 = coeffB0;
                coeffA2 = 0.f;
            }
            else {
                coeffB0 = ((pow(k, 2.f) * q) - k + q) / ((pow(k, 2.f) * q) + k + q);
                coeffB1 = (2.f * q * (pow(k, 2.f) - 1.f)) / ((pow(k, 2.f) * q) + k + q);
                coeffB2 = 1.f;
                coeffA1 = coeffB1;
                coeffA2 = coeffB0;
            }
        }
    }
    
    
    void flushBuffer() {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 5; k++) {
                    buffer[i][j][k] = 0.f;
                }
            }
        }
    }
    
private:
    int filterType;
    int filterOrder;
    
    float coeffB0, coeffB1, coeffB2, coeffA1, coeffA2;
    
    float buffer[2][2][5]; // <- Buffer array for 2 delays, 2 channels and 5 instances of computation
    
    const float piFloat = 3.1415926536;
};


#endif /* Biquad_h */

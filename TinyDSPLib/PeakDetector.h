/*
    PeakDetector.h
    
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

#ifndef PeakDetector_h
#define PeakDetector_h

class PeakDetector {
public:
    PeakDetector() {}
    ~PeakDetector() {}
    
    float calcEnvelope(float sample, float timeConstant, int sr) {
        float x = sample;
        float attack = 0.1f;
        float release = timeConstant;
        float dt = 1.f / sr;
        float tc = log10(0.01f);
        
        // Calculate rect, AT and RT values
        float rect = fabs(x);
        float at = 1.f - exp((-2.2f * dt) / (attack / 1000.f));
        float rt = 1.f - exp((-2.2f * dt) / (release / 1000.f));
        
        // Writing the output value before calculation starts imitates the one sample delay
        float y = vc;
        
        // Calculate the envelope value for attack and release case
        if (rect > vc) {
            vc = (1.f - at) * vc + at * rect;
        }
        else {
            vc = (1.f - rt) * vc;
        }
        
        return y;
    }
    
    void flushVC() {
        vc = 0.f;
    }
    
private:
    float vc;
};



#endif /* PeakDetector_h */

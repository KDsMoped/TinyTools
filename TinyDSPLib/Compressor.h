/*
    Compressor.h
    
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

#ifndef Compressor_h
#define Compressor_h


#include "PeakDetector.h"
#include "SignalProcessingHelpers.h"

class Compressor {
public:
    Compressor() : peakDetector(new PeakDetector) {}
    ~Compressor() { delete peakDetector; }
    
    float calcGain(float sample, float threshold, float ratio, float release, int sr) {
        // Set slope variable
        float cs = 1.f - (1.f / ratio);
        
        // Envelope detector
        float env = peakDetector->calcEnvelope(sample, release, sr);
        
        // Convert Envelope to logarithmic value
        float envDB = convertFloattoDB(env);
        
        // Compute gain; Threshold and detection values in dB
        float y = cs * (threshold - envDB);
        
        // Clamp; this allows ratios of 1:1 to still operate
        y = fminf(0.f, y);
        
        // Convert to linear values
        return convertDBtoFloat(y);
    }
    
    void flushDetector() {
        peakDetector->flushVC();
    }
    
private:
    PeakDetector *peakDetector;
};


#endif /* Compressor_h */

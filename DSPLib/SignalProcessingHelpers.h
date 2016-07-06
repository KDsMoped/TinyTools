/*
  ==============================================================================

    SignalProcessingHelpers.h
    Created: 1 Oct 2015 6:57:23pm
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
 
  Very tiny but useful functions 
 
  ==============================================================================
*/

#ifndef SIGNALPROCESSINGHELPERS_H_INCLUDED
#define SIGNALPROCESSINGHELPERS_H_INCLUDED



//==============================================================================



float convertDBtoFloat(float dbValue) {
	return pow(10, dbValue / 20);
}

float convertFloattoDB(float floatValue) {
	return 20 * log(floatValue);
}

/**
 Returns the corresponding frequency to a  MIDI-style note value
 */
float convertMidiToFreq(float midivalue){
    return  440.0*pow(2.0,(midivalue - 69.f) * 1.f/12.f);
}


//==============================================================================


#endif  // SIGNALPROCESSINGHELPERS_H_INCLUDED

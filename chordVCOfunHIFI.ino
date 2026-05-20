#include <MozziConfigValues.h>
#define MOZZI_AUDIO_MODE MOZZI_OUTPUT_2PIN_PWM // <-- Activa el modo HIFI en Pines D9 y D10
#include <Mozzi.h>
#include <Oscil.h> // oscillator template
#include <math.h>

#include <tables/saw2048_int8.h> // saw table for oscillator
#include <tables/square_no_alias512_int8.h> // saw table for oscillator
#include <tables/triangle_hermes_2048_int8.h> // saw table for oscillator
#include <tables/sin2048_int8.h> // sine table for oscillator
#include <tables/waveshape_chebyshev_3rd_256_int8.h> // sine table for oscillator
#include <tables/waveshape_sigmoid_int8.h> // sine table for oscillator
#include <tables/phasor256_int8.h> // sine table for oscillator

Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> aSaw1(SAW2048_DATA);
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> aSaw2(SAW2048_DATA);
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> aSaw3(SAW2048_DATA);
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> aSaw4(SAW2048_DATA);
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> aSaw5(SAW2048_DATA);

Oscil <SQUARE_NO_ALIAS512_NUM_CELLS, AUDIO_RATE> aSqu1(SQUARE_NO_ALIAS512_DATA);
Oscil <SQUARE_NO_ALIAS512_NUM_CELLS, AUDIO_RATE> aSqu2(SQUARE_NO_ALIAS512_DATA);
Oscil <SQUARE_NO_ALIAS512_NUM_CELLS, AUDIO_RATE> aSqu3(SQUARE_NO_ALIAS512_DATA);
Oscil <SQUARE_NO_ALIAS512_NUM_CELLS, AUDIO_RATE> aSqu4(SQUARE_NO_ALIAS512_DATA);
Oscil <SQUARE_NO_ALIAS512_NUM_CELLS, AUDIO_RATE> aSqu5(SQUARE_NO_ALIAS512_DATA);

Oscil <TRIANGLE_HERMES_2048_NUM_CELLS, AUDIO_RATE> aTri1(TRIANGLE_HERMES_2048_DATA);
Oscil <TRIANGLE_HERMES_2048_NUM_CELLS, AUDIO_RATE> aTri2(TRIANGLE_HERMES_2048_DATA);
Oscil <TRIANGLE_HERMES_2048_NUM_CELLS, AUDIO_RATE> aTri3(TRIANGLE_HERMES_2048_DATA);
Oscil <TRIANGLE_HERMES_2048_NUM_CELLS, AUDIO_RATE> aTri4(TRIANGLE_HERMES_2048_DATA);
Oscil <TRIANGLE_HERMES_2048_NUM_CELLS, AUDIO_RATE> aTri5(TRIANGLE_HERMES_2048_DATA);

Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin1(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin2(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin3(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin4(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin5(SIN2048_DATA);

Oscil <CHEBYSHEV_3RD_256_NUM_CELLS, AUDIO_RATE> aChb1(CHEBYSHEV_3RD_256_DATA);
Oscil <CHEBYSHEV_3RD_256_NUM_CELLS, AUDIO_RATE> aChb2(CHEBYSHEV_3RD_256_DATA);
Oscil <CHEBYSHEV_3RD_256_NUM_CELLS, AUDIO_RATE> aChb3(CHEBYSHEV_3RD_256_DATA);
Oscil <CHEBYSHEV_3RD_256_NUM_CELLS, AUDIO_RATE> aChb4(CHEBYSHEV_3RD_256_DATA);
Oscil <CHEBYSHEV_3RD_256_NUM_CELLS, AUDIO_RATE> aChb5(CHEBYSHEV_3RD_256_DATA);

Oscil <WAVESHAPE_SIGMOID_NUM_CELLS, AUDIO_RATE> aSig1(WAVESHAPE_SIGMOID_DATA);
Oscil <WAVESHAPE_SIGMOID_NUM_CELLS, AUDIO_RATE> aSig2(WAVESHAPE_SIGMOID_DATA);
Oscil <WAVESHAPE_SIGMOID_NUM_CELLS, AUDIO_RATE> aSig3(WAVESHAPE_SIGMOID_DATA);
Oscil <WAVESHAPE_SIGMOID_NUM_CELLS, AUDIO_RATE> aSig4(WAVESHAPE_SIGMOID_DATA);
Oscil <WAVESHAPE_SIGMOID_NUM_CELLS, AUDIO_RATE> aSig5(WAVESHAPE_SIGMOID_DATA);

Oscil <PHASOR256_NUM_CELLS, AUDIO_RATE> aPha1(PHASOR256_DATA);
Oscil <PHASOR256_NUM_CELLS, AUDIO_RATE> aPha2(PHASOR256_DATA);
Oscil <PHASOR256_NUM_CELLS, AUDIO_RATE> aPha3(PHASOR256_DATA);
Oscil <PHASOR256_NUM_CELLS, AUDIO_RATE> aPha4(PHASOR256_DATA);
Oscil <PHASOR256_NUM_CELLS, AUDIO_RATE> aPha5(PHASOR256_DATA);

#undef CONTROL_RATE
#define CONTROL_RATE 128 // Hz

// Pin del pulsador de función (MISO = Pin 12)
const byte PIN_FUNCTION = 12;

int freq1 = 110;//base freq
int voct = 1000;//external V/OCT LSB

int freqv1 = 440;//apply voct
int freqv2 = 440;
int freqv3 = 440;
int freqv4 = 440;
int freqv5 = 440;

byte note1 = 0;//Root
byte note2 = 0;//2nd
byte note3 = 0;//3rd
byte note4 = 0;//4th
byte note5 = 0;//Root

byte inv_aply1 = 0;
//0 = no inv , 1 = inv
byte inv_aply2 = 0; 
byte inv_aply3 = 0; 
byte inv_aply4 = 0;
bool inv_aply5 = 0; 

int inv = 0;
int inv_knob = 0;
int chord = 0;
byte wave = 0;

// Variables para el modo arpegiador rítmico
byte pasoArpegio = 0;
bool goingUp = true;
bool lastClockState = false;
byte extensionOctavaContador = 0; // Controla en qué ciclo de octava extra estamos (0=Base, 1=Modificada)

// Variables de memoria y candados para A2 (Arpegiador / Mutación)
byte modoArpGuardado = 0;
bool a2_captured = true;      
int lastPhysicalArpMode = 0;  
int valorA2AlPulsar = 0;       
bool mutacion_activa = false;

// Variables de memoria y candados para A1 (Intervalos / Detune / Rango de Octavas)
int invGuardada = 0;
int maxDetune = 0;             
bool a1_captured = true;       // Controla si la perilla física vuelve a mandar en capa normal
int lastPhysicalA1Mode = 0;

// Para catch-up de A1 (puede ser intervalo o rango octava)
int valorA1AlPulsar = 0;       
bool detune_activo = false;
byte rangoOctavaArp = 0;       // 0 = 1 Octava, 1 = 2 Octavas (+1 Oct), 2 = 2 Octavas (-1 Oct)
byte rangoOctavaGuardado = 0;  // Memoria del rango de octava al cambiar de capa

// Variables para congelamiento de Pitch y captura (Catch-up)
int lastSavedFreq1 = 110;
bool a0_captured = true;      
bool lastFuncState = false;   
bool lastArpActiveState = false; // Detecta flancos de encendido del arpegiador

static inline float voctRatio(unsigned int idx) {
  if (idx > 1023) {
    idx = 1023;
  }
  return powf(2.0f, idx * 0.0048828125f);
}

// =========================================================================
// MATRIZ DE 7 ESCALAS MODALES (CON TOQUE BLUESY AL FINAL)
// =========================================================================
const static byte chord_table[7][4] PROGMEM = {
 { 0,  68, 119,  205 }, // 0. MAYOR JÓNICA      
 { 0,  68, 119,  187 }, // 1. MIXOLIDIA         
 { 0,  68, 119,  153 }, // 2. PENTATÓNICA MAYOR 
 { 0,  51, 119,  153 }, // 3. MENOR DÓRICA      
 { 0,  51, 119,  136 }, // 4. MENOR NATURAL     
 { 0,  17, 119,  136 }, // 5. FRIGIA            
 { 0,  51, 119,  170 }  // 6. PENTATÓNICA MENOR -> Bluesy!
};

void setup()
{
 pinMode(PIN_FUNCTION, INPUT_PULLUP); // Pulsador momentáneo entre Pin 12 y GND
 startMozzi(CONTROL_RATE);
}

void updateControl() {
 const int analog0 = mozziAnalogRead(0); // Pote de PITCH / Selector de Escalas
 const int analog1 = mozziAnalogRead(1); // Pote de INVERSIONES / Detune / Tipo de Onda
 const int analog2 = mozziAnalogRead(2); // Pote de MODO ARPEGIO / Probabilidad Mutación
 const int analog3 = mozziAnalogRead(3); // Pote de Acorde L / Modificador estructural 1
 const int analog4 = mozziAnalogRead(4); // Clock entrada digital simulada
 const int analog5 = mozziAnalogRead(5); // Pote de Acorde R / Modificador estructural 2
 const int analog7 = mozziAnalogRead(7); // CV V/OCT externo

 // Leer el pulsador de función (LOW = Presionado)
 bool funcActive = (digitalRead(PIN_FUNCTION) == LOW);
 bool arpActive = (analog2 >= 50);

 int currentArpMode = 0;
 int mutacionProb = 0;

 // --- DETECCIÓN DE ENTRADA AL MODO ARPEGIO ---
 if (arpActive && !lastArpActiveState) {
   a1_captured = false;
   // Ponemos candado para forzar que inicie en Octava Base por defecto
   rangoOctavaGuardado = 0; // Forzamos 1 Octava por defecto
   if (inv_knob < 1020) {
     lastPhysicalA1Mode = analog1 / 323; // Registrar posición actual para catch-up
   }
 }
 lastArpActiveState = arpActive;

 // --- FLANCO DE SUBIDA (Se acaba de apretar el botón) ---
 if (funcActive && !lastFuncState) {
   valorA2AlPulsar = analog2;
   mutacion_activa = false;       
   if (arpActive) {
     modoArpGuardado = (analog2 - 50) / 244;
     modoArpGuardado = constrain(modoArpGuardado, 0, 3);
   }

   valorA1AlPulsar = analog1;
   detune_activo = false;
   if (!arpActive) {
     invGuardada = (analog1 / 64) + (analog4 / 64);
     invGuardada = constrain(invGuardada, 0, 15);
   } else {
     rangoOctavaGuardado = rangoOctavaArp; // Guardamos el rango de octavas antes de bloquear
   }
 }

 // --- FLANCO DE BAJADA (Se acaba de soltar el botón) ---
 if (!funcActive && lastFuncState) {
   a0_captured = false;
   a2_captured = false; 
   lastPhysicalArpMode = (analog2 - 50) / 244;
   lastPhysicalArpMode = constrain(lastPhysicalArpMode, 0, 3);

   a1_captured = false;
   if (!arpActive) {
     lastPhysicalA1Mode = (analog1 / 64) + (analog4 / 64);
     lastPhysicalA1Mode = constrain(lastPhysicalA1Mode, 0, 15);
   } else {
     if (analog1 < 1020) {
       lastPhysicalA1Mode = analog1 / 323; // Modo de octava físico al soltar
       lastPhysicalA1Mode = constrain(lastPhysicalA1Mode, 0, 2);
     }
   }
 }
 lastFuncState = funcActive;

 inv_knob = analog1;
 if (funcActive) {
   // =========================================================================
   // CAPA FUNCIÓN ACTIVA
   // =========================================================================
   currentArpMode = modoArpGuardado;
   inv = invGuardada;                
   rangoOctavaArp = rangoOctavaGuardado; // Mantenemos congelado el rango de octava elegido

   // 1. Gestión de Mutación (A2) -> Max 60%
   if (!mutacion_activa) {
     if (abs(analog2 - valorA2AlPulsar) > 15) { 
       mutacion_activa = true;
     }
   }
   if (mutacion_activa) {
     mutacionProb = map(analog2, 0, 1023, 0, 6);
     mutacionProb = mutacionProb * 10;
   } else {
     mutacionProb = 0;
   }

   // 2. Gestión de Detune en Vivo (A1)
   if (inv_knob < 1020) {
     if (!detune_activo) {
       if (abs(analog1 - valorA1AlPulsar) > 15) {
         detune_activo = true;
       }
     }
     if (detune_activo) {
       maxDetune = map(analog1, 0, 1019, 0, 14);
     }
   }

   if (arpActive) {
     chord = analog0 / 147;
     chord = constrain(chord, 0, 6);
   }

 } else {
   // =========================================================================
   // CAPA NORMAL
   // =========================================================================
   mutacionProb = 0;
   // 1. Catch-up para el modo del Arpegiador (A2)
   int physicalArpModeCurrent = (analog2 - 50) / 244;
   physicalArpModeCurrent = constrain(physicalArpModeCurrent, 0, 3);

   if (!a2_captured) {
     if (physicalArpModeCurrent != lastPhysicalArpMode) {
       a2_captured = true;
     }
   }
   if (a2_captured && arpActive) {
     currentArpMode = physicalArpModeCurrent;
     modoArpGuardado = currentArpMode; 
   } else {
     currentArpMode = modoArpGuardado;
   }

   // 2. Control Bifuncional de A1 (Intervalos en estático / Octavas en Arpegio)
   if (!arpActive) {
     // MODO ESTÁTICO: A1 controla Intervalos/Inversiones
     int physicalInvCurrent = (analog1 / 64) + (analog4 / 64);
     physicalInvCurrent = constrain(physicalInvCurrent, 0, 15);

     if (!a1_captured) {
       if (physicalInvCurrent != lastPhysicalA1Mode) {
         a1_captured = true;
       }
     }
     if (a1_captured) {
       inv = physicalInvCurrent;
       invGuardada = inv; 
     } else {
       inv = invGuardada;
     }
   } else {
     // MODO ARPEGIO: A1 controla el Rango de Octavas
     if (inv_knob < 1020) {
       int physicalOctaveMode = analog1 / 323; // Divide el pote en 3 porciones (0, 1, 2)
       physicalOctaveMode = constrain(physicalOctaveMode, 0, 2);
       if (!a1_captured) {
         if (physicalOctaveMode != lastPhysicalA1Mode) {
           a1_captured = true;
         }
       }
       if (a1_captured) {
         rangoOctavaArp = physicalOctaveMode;
         rangoOctavaGuardado = rangoOctavaArp; // Sincronizamos memoria
       } else {
         rangoOctavaArp = rangoOctavaGuardado; // Mantiene el valor por defecto o congelado
       }
     }
   }

   if (!arpActive) {
     chord = (analog3 / 128) + (analog5 / 128);
     chord = constrain(chord, 0, 6);
   }

   // Catch-up Pitch (A0)
   int currentPhysicalPitch = analog0 / 4;
   if (!a0_captured) {
     if (abs(currentPhysicalPitch - lastSavedFreq1) < 4) {
       a0_captured = true;
     }
   }
   if (a0_captured) {
     freq1 = currentPhysicalPitch;
     lastSavedFreq1 = freq1;
   } else {
     freq1 = lastSavedFreq1;
   }
 }

 // Asignación clásica de inversiones (Solo aplica si no hay arpegiador)
 if (inv_knob < 1020 && !arpActive) { 
   switch (inv) {
     case 0:  inv_aply1=0; inv_aply2=0; inv_aply3=0; inv_aply4=0; inv_aply5=0; break;
     case 1:  inv_aply1=1; inv_aply2=0; inv_aply3=0; inv_aply4=0; inv_aply5=0; break;
     case 2:  inv_aply1=1; inv_aply2=1; inv_aply3=0; inv_aply4=0; inv_aply5=0; break;
     case 3:  inv_aply1=1; inv_aply2=1; inv_aply3=1; inv_aply4=0; inv_aply5=0; break;
     case 4:  inv_aply1=1; inv_aply2=1; inv_aply3=1; inv_aply4=1; inv_aply5=0; break;
     case 5:  inv_aply1=2; inv_aply2=1; inv_aply3=1; inv_aply4=1; inv_aply5=0; break;
     case 6:  inv_aply1=2; inv_aply2=2; inv_aply3=1; inv_aply4=1; inv_aply5=0; break;
     case 7:  inv_aply1=2; inv_aply2=2; inv_aply3=2; inv_aply4=1; inv_aply5=0; break;
     case 8:  inv_aply1=2; inv_aply2=2; inv_aply3=2; inv_aply4=1; inv_aply5=1; break;
     case 9:  inv_aply1=2; inv_aply2=2; inv_aply3=1; inv_aply4=1; inv_aply5=1; break;
     case 10: inv_aply1=2; inv_aply2=1; inv_aply3=1; inv_aply4=1; inv_aply5=1; break;
     case 11: inv_aply1=1; inv_aply2=1; inv_aply3=1; inv_aply4=1; inv_aply5=1; break;
     case 12: inv_aply1=1; inv_aply2=1; inv_aply3=1; inv_aply4=0; inv_aply5=1; break;
     case 13: inv_aply1=1; inv_aply2=1; inv_aply3=0; inv_aply4=0; inv_aply5=1; break;
     case 14: inv_aply1=1; inv_aply2=0; inv_aply3=0; inv_aply4=0; inv_aply5=1; break;
     case 15: inv_aply1=0; inv_aply2=0; inv_aply3=0; inv_aply4=0; inv_aply5=1; break;
   }

   note1 = pgm_read_byte(&(chord_table[chord][0]));
   note2 = pgm_read_byte(&(chord_table[chord][1]));
   note3 = pgm_read_byte(&(chord_table[chord][2]));
   note4 = pgm_read_byte(&(chord_table[chord][3]));
   note5 = pgm_read_byte(&(chord_table[chord][0]));
 }

 // ====================================================
 // ARPEGIADOR RÍTMICO MODAL MUTANTE (CON RANGO DE OCTAVAS)
 // ====================================================
 if (arpActive) {
   bool clockState = (analog4 > 512);
   if (clockState && !lastClockState) { 
     
     int dadoGenerativo = random(0, 100);
     byte siguientePaso = pasoArpegio;

     if (dadoGenerativo >= mutacionProb) {
       // Avance de patrón normal de pasos (0 a 3)
       switch (currentArpMode) {
         case 0: siguientePaso = (pasoArpegio + 1) % 4; break;
         case 1: if (pasoArpegio == 0) siguientePaso = 3; else siguientePaso--; break;
         case 2: 
           if (goingUp) { siguientePaso++;
           if (siguientePaso >= 3) { siguientePaso = 3; goingUp = false;
           } } 
           else { if (pasoArpegio == 0) { siguientePaso = 1;
           goingUp = true; } else { siguientePaso--; if (siguientePaso == 0) goingUp = true;
           } }
           break;
         case 3: siguientePaso = random(0, 4); break;
       }
     } else {
       // Paso Mutante
       int tipoMutacion = random(0, 3);
       if (tipoMutacion == 0) siguientePaso = pasoArpegio;
       else if (tipoMutacion == 1) siguientePaso = random(0, 4);
       else { goingUp = !goingUp; siguientePaso = (pasoArpegio + 1) % 4;
       }
     }

     // LÓGICA DE DETECCIÓN DE REINICIO DE CICLO PARA EXTENSIÓN DE OCTAVAS
     if ((currentArpMode == 0 && siguientePaso == 0) || 
         (currentArpMode == 1 && siguientePaso == 3) || 
         (currentArpMode == 2 && pasoArpegio == 0 && siguientePaso == 1) || 
         (currentArpMode == 3 && random(0,10) > 7)) {
       
       if (rangoOctavaArp == 0) {
         extensionOctavaContador = 0; // Siempre octava base
       } else {
         extensionOctavaContador = (extensionOctavaContador + 1) % 2; // Alterna entre ciclo base y ciclo octavado
       }
     }
     
     pasoArpegio = siguientePaso;
   }
   lastClockState = clockState; 
   
   byte notaArpegio = pgm_read_byte(&(chord_table[chord][pasoArpegio]));
   // Modificadores estructurales de A3 y A5
   int offsetEstructural = 0;
   if (analog3 > 300) { offsetEstructural += (analog3 / 341) * 205;
   }
   if (analog5 > 200) { offsetEstructural += (analog5 / 256) * 17;
   }
   
   int subMutacionOctava = 0;
   if ((random(0, 100) < mutacionProb) && (mutacionProb > 0)) {
     subMutacionOctava = (random(0, 2) == 0) ? 205 : -205; 
   }

   // CALCULAR EL DESFASAJE EXACTO DEL RANGO DE OCTAVAS (A1)
   int octavaDesfasajeGeneral = 0;
   if (extensionOctavaContador == 1) {
     if (rangoOctavaArp == 1) {
       octavaDesfasajeGeneral = 205; // Una octava arriba (+205)
     } else if (rangoOctavaArp == 2) {
       octavaDesfasajeGeneral = -205; // Una octava abajo (-205)
     }
   }
   
   note1 = notaArpegio + subMutacionOctava + offsetEstructural + octavaDesfasajeGeneral;
   note2 = notaArpegio + offsetEstructural + octavaDesfasajeGeneral;
   note3 = notaArpegio + offsetEstructural + octavaDesfasajeGeneral;
   note4 = notaArpegio + offsetEstructural + octavaDesfasajeGeneral;
   note5 = notaArpegio + offsetEstructural + octavaDesfasajeGeneral;
   
   inv_aply1 = 0; inv_aply2 = 0;
   inv_aply3 = 0; inv_aply4 = 0;
   inv_aply5 = 1; 
 }

 // ====================================================
 // APLICACIÓN GENERAL DE DETUNE (ESTÁTICO Y ARPEGIO)
 // ====================================================
 int d1 = 0, d2 = 0, d3 = 0, d4 = 0, d5 = 0;
 if (inv_knob < 1020) {
   d1 = 0;
   d2 = maxDetune / 3;
   d3 = (maxDetune * 2) / 3;
   d4 = maxDetune;
   d5 = maxDetune / 2;
 }

 if (inv_knob >= 1020) { 
   wave = (analog3 / 128);
 }

 voct = analog7;
 freqv1 = freq1 * voctRatio(voct + 205 * inv_aply1 + note1 + d1);
 freqv2 = freq1 * voctRatio(voct + 205 * inv_aply2 + note2 + d2);
 freqv3 = freq1 * voctRatio(voct + 205 * inv_aply3 + note3 + d3);
 freqv4 = freq1 * voctRatio(voct + 205 * inv_aply4 + note4 + d4);
 freqv5 = freq1 * voctRatio(voct + note5 + d5);

 switch (wave) {
   case 0: aSaw1.setFreq(freqv1); aSaw2.setFreq(freqv2); aSaw3.setFreq(freqv3); aSaw4.setFreq(freqv4); aSaw5.setFreq(freqv5); break;
   case 1: aSqu1.setFreq(freqv1); aSqu2.setFreq(freqv2); aSqu3.setFreq(freqv3); aSqu4.setFreq(freqv4); aSqu5.setFreq(freqv5); break;
   case 2: aTri1.setFreq(freqv1); aTri2.setFreq(freqv2); aTri3.setFreq(freqv3); aTri4.setFreq(freqv4); aTri5.setFreq(freqv5); break;
   case 3: aSin1.setFreq(freqv1); aSin2.setFreq(freqv2); aSin3.setFreq(freqv3); aSin4.setFreq(freqv4); aSin5.setFreq(freqv5); break;
   case 4: aChb1.setFreq(freqv1); aChb2.setFreq(freqv2); aChb3.setFreq(freqv3); aChb4.setFreq(freqv4); aChb5.setFreq(freqv5); break;
   case 5: aSig1.setFreq(freqv1); aSig2.setFreq(freqv2); aSig3.setFreq(freqv3); aSig4.setFreq(freqv4); aSig5.setFreq(freqv5); break;
   case 6: aPha1.setFreq(freqv1); aPha2.setFreq(freqv2); aPha3.setFreq(freqv3); aPha4.setFreq(freqv4); aPha5.setFreq(freqv5); break;
   case 7: aPha1.setFreq(freqv1); aPha2.setFreq(freqv2); aPha3.setFreq(freqv3); aPha4.setFreq(freqv4); aPha5.setFreq(freqv5); break;
 }
}

// Mezclador de alta resolución (Suma limpia sin pre-dividir)
static inline int16_t mix5(int8_t a, int8_t b, int8_t c, int8_t d, int8_t e) {
  return (int16_t)a + b + c + d + (e * inv_aply5);
}

// Salida de audio configurada nativamente para escalar los 11 bits del mix al hardware
AudioOutput updateAudio() {
 switch (wave) {
   case 0: return MonoOutput::fromNBit(11, mix5(aSaw1.next(), aSaw2.next(), aSaw3.next(), aSaw4.next(), aSaw5.next())); break;
   case 1: return MonoOutput::fromNBit(11, mix5(aSqu1.next(), aSqu2.next(), aSqu3.next(), aSqu4.next(), aSqu5.next())); break;
   case 2: return MonoOutput::fromNBit(11, mix5(aTri1.next(), aTri2.next(), aTri3.next(), aTri4.next(), aTri5.next())); break;
   case 3: return MonoOutput::fromNBit(11, mix5(aSin1.next(), aSin2.next(), aSin3.next(), aSin4.next(), aSin5.next())); break;
   case 4: return MonoOutput::fromNBit(11, mix5(aChb1.next(), aChb2.next(), aChb3.next(), aChb4.next(), aChb5.next())); break;
   case 5: return MonoOutput::fromNBit(11, mix5(aSig1.next(), aSig2.next(), aSig3.next(), aSig4.next(), aSig5.next())); break;
   case 6: return MonoOutput::fromNBit(11, mix5(aPha1.next(), aPha2.next(), aPha3.next(), aPha4.next(), aPha5.next())); break;
   case 7: return MonoOutput::fromNBit(11, mix5(aPha1.next(), aPha2.next(), aPha3.next(), aPha4.next(), aPha5.next())); break;
   default: return MonoOutput::fromNBit(11, 0);
 }
}

void loop() {
 audioHook(); 
}
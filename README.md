Este es un proyecto basado en el VCO de HAgiwo, para Arduino Nano/ATmega328, con algunas modificaciones extras, tanto para mejorar el audio(uso de audio output hifi de Mozzi) como para agregar mas variables a un modulo que puede ser usado de tanto de forma estatica como de una manera muy ritmica y musical. 
este proyecto es 100% compatible con el esquema y pinout original, solo se agrega D12 como salida para Pulsador(normal abierto; pin a d12 y gnd en el otro pin) y un potenciometro en A2 de la misma forma en que se implementan los otros potenciometros.
A2 de ahora en mas controla modo chord/arpegiador, y d12 es el switch de FUNCION.

 Les dejo el resumen de ia:  lol


💡 El Concepto Esencial: Doble Capa ([FUNC])
Para darte el doble de funciones sin llenar el panel de perillas, el módulo cuenta con un botón rotulado como [FUNC].
Modo Normal: Ocurre cuando el botón está suelto. Las perillas hacen lo que dice su etiqueta principal.
Modo Alternativo: Se activa mientras mantienes presionado el botón [FUNC]. Las perillas cambian por completo para controlar parámetros ocultos.

🔒 Sistema Anti-Saltos (Catch-up): Cuando modificas un parámetro en la capa oculta y sueltas el botón [FUNC], el sonido de la capa normal se quedará "congelado". No cambiará bruscamente hasta que muevas la perilla física y "alcances" la posición en la que se había quedado originalmente

1. PITCH / SCALES (Afinación y Escalas)A02: 
Es la perilla principal para el control de la altura musical.

⚙️ Capa Normal (PITCH): Ajusta la afinación o nota raíz de todo el módulo. Al girarla a la izquierda obtendrás bajos profundos y subsónicos; al girarla a la derecha, leads agudos y cristalinos.

✨ Capa [FUNC] (SCALES): Nota: Solo funciona si el Arpegiador está encendido. En lugar de cambiar la afinación libremente, la perilla se transforma en un selector rotativo de 7 posiciones fijas para elegir la escala musical en la que jugará el arpegiador (Ver sección de Escalas Modales).

2. INVERSIONS / RANGE / DETUNE (Inversiones, Octavas y Coro)A01:
Esta perilla es el núcleo de la textura y el orden de las notas.

⚙️ Capa Normal (Con Arpegiador APAGADO - INVERSIONS): Funciona como un selector de 16 niveles de inversiones. Mover esta perilla no cambia las notas del acorde, sino el orden en el que se apilan (por ejemplo, pasa la nota más grave arriba del todo, o la del medio al suelo). Es ideal para buscar tensiones sutiles o dar espacio a otros instrumentos.

⚙️ Capa Normal (Con Arpegiador ENCENDIDO - RANGE): Define el rango de octavas por las que viajará el arpegio, dividido en tres zonas del potenciómetro:
Primer tercio: El arpegio se queda en su octava base de forma constante.
Segundo tercio: El arpegio da una vuelta normal y la siguiente vuelta la da una octava más arriba (+1 Oct).
Tercer tercio: Alterna una vuelta normal y otra una octava más abajo (-1 Oct).

✨ Capa general [FUNC] (DETUNE): Controla la desafinación interna de los 5 osciladores. Al mínimo, el sonido es perfectamente puro y afinado. A medida que lo subes, los osciladores se separan sutilmente entre sí creando un sonido gigantesco, masivo y con un efecto de coro analógico (Supersaw) arrollador.

3. ARPEGGIATOR / MUTATION (Modo de Arpegio y Probabilidad de Mutación)A02:
Esta perilla activa el movimiento rítmico secuencial. El arpegiador se enciende automáticamente en cuanto subes la perilla un poco (pasando el umbral inicial).

⚙️ Capa Normal (ARPEGGIATOR): Divide el recorrido de la perilla en 4 modos de dirección para el arpegio:
Modo 1 (Up): Las notas del acorde suben en escalera limpia (1, 2, 3, 4).
Modo 2 (Down): Las notas bajan en escalera limpia (4, 3, 2, 1).
Modo 3 (Up/Down): Las notas suben y bajan de forma continua (1, 2, 3, 4, 3, 2...).
Modo 4 (Random): El módulo elige la siguiente nota completamente al azar.

✨ Capa [FUNC] (MUTATION): El modo de dirección elegido se bloquea (no cambia), y la perilla pasa a controlar la Probabilidad de Mutación (de 0% a 60%). Al subirla, inyectas "errores" controlados por computadora: el arpegiador romperá su patrón lógico de vez en cuando, cambiará de sentido repentinamente o lanzará notas locas a otras octavas, logrando melodías infinitas que nunca se repiten.
*funcion a mejorar, aun posee glitches.

4. CHORD SELECTION / ESTRUCTURA (Selección de Acordes)A03:
Estas funciones se controlan mediante un par de perillas aliadas (potenciómetros izquierdo y derecho del bloque de acordes).

⚙️ Capa Normal (Con Arpegiador APAGADO): La combinación de estas perillas selecciona cuál de los 7 acordes de la lista interna estará sonando de forma continua.

⚙️ Capa Normal (Con Arpegiador ENCENDIDO): Se transforman en Modificadores Estructurales. En lugar de cambiar el acorde base, reconfiguran matemáticamente las distancias entre los osciladores en tiempo real, añadiendo tensiones armónicas exóticas o variaciones melódicas sin que tengas que cambiar la escala.

5. CLOCK INPUT (Entrada de Reloj)/ INTERVALO V/C :
Es la entrada encargada de darle el pulso y la velocidad al arpegiador. Cada vez que esta entrada recibe un cambio de voltaje alto (un pulso, un LFO de onda cuadrada o el reloj de una caja de ritmos), el arpegiador avanza al siguiente paso. Esta entrada de clock es compatible con la serie VOlca,
 es la misma entrada que se usa para controlar el potenciometro de INVERSION, pero esta solo se activa cuando entra en modo ARPGG.

7. V/OCT INPUT (Voltaje por Octava): entrada apta +5v
8. CHORD V/C: entrada apta +5v
9. FUNC D12: Accede a los demas parametros
   
   
Cuando usas el arpegiador en la capa [FUNC], puedes elegir entre 7 ambientes preprogramados que dictarán las notas disponibles:
Mayor Jónica: 
Mixolidia: 
Pentatónica Mayor: 
Menor Dórica: 
Menor Natural: 
Frigia: 
Pentatónica Menor:

Para cambiar de onda, lleva la perilla 2 (INVERSIONS) al máximo absoluto. Al hacer esto, la perilla 4 (CHORD SELECTION) dejará de cambiar acordes y se convertirá en un selector para recorrer los 7 motores de ondas disponibles:
Tipo de Onda
Icono
Característica Auditiva 🎧: 

Sawtooth (Sierra)
🪚
Sonido clásico, brillante y con muchos armónicos. Ideal para acordes masivos de música electrónica y leads afilados.

Square (Cuadrada)
🔲
Tono hueco y con un toque "hueco" de madera. Recuerda al sonido de las consolas de videojuegos retro de 8 bits o a un clarinete.

Triangle (Triangular)
🔺
Sonido muy dulce, redondo y flautado. Tiene pocos armónicos, ideal para texturas suaves que no tapen la mezcla.

Sine (Senoidal)
🌊
La onda más pura de la naturaleza, sin armónicos. Suena como un silbido limpio o un subbajo profundo que hace vibrar el piso.

Chebyshev
🦾
Ondas distorsionadas matemáticamente. Entrega una textura metálica, fría e industrial, excelente para sonidos modernos.

Sigmoid
🌡️
Una forma de onda híbrida y suave. Produce un sonido cálido, gordo, un tanto saturado y muy orgánico.

Phasor
🌀
Sonido experimental, rústico y texturizado, perfecto para drones de fondo o timbres de ciencia ficción.



Proyecto principal en el que esta basado:
https://note.com/solder_state/n/n681d2e07e324

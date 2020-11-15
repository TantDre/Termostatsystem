# Termostatsystem  
Styrning av termostaten på ett element via kaskadreglering.  
Framtida förbättringar är framkoppling av utomhustemperaturen och loggning.
  
# Version 
v1 (release)  : Av och på reglering   
v2 (release)  : PID reglering  
v3 (future)   : MPC
  
# Blockdiagram  
Beskrivning av reglersystemet.  
![Blockdiagram](https://github.com/TantDre/Termostatsystem/blob/master/Blockdiagram.png?raw=true)
  
# Kopplingsschema  
Arduino : Uno  
Servo   : MG 995  
Sensor  : DHT 22  
  
![Kopplingsschema](https://github.com/TantDre/Termostatsystem/blob/master/Kopplingsschema.png?raw=true)
  
# System test och modell
Stegsvar utan reglering.    
![System](https://github.com/TantDre/Termostatsystem/blob/master/Systemidentifiering/Test_Plot.png?raw=true)

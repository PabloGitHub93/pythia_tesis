// Headers and Namespaces.
#include "Pythia8/Pythia.h"  //Incluye los headers de pythia
using namespace Pythia8;

int main() {          


Pythia pythia;	//Declara un objeto de Pythia con nombre pythia

// Create an LHAup object that can access relevant information in pythia.
  LHAupFromPYTHIA8 myLHA(&pythia.process, &pythia.info);

// Open a file on which LHEF events should be stored, and write header.
  myLHA.openLHEF("SSDM_pythia_output.lhe");

// Set up generation
pythia.readString("Beams:frameType = 4"); //Le dice al programa que lea la información del beam en el LHEF
pythia.readString("Beams:LHEF = SSDM_pp_qqH-single.lhe");
pythia.init(); //Inicializa; haces pp incidentes por defecto. Lee los archivos Settings y ParticleData

// Store initialization info in the LHAup object.
  myLHA.setInit();

// Write out this initialization info on the file.
  myLHA.initLHEF();

//Bucle de eventos
for(int iEvent = 0; iEvent < 1000; ++iEvent){

 if(!pythia.next()){	//pythia.next retorna un valor booleano, falso si la generación falla
   if(pythia.info.atEndOfFile()) break; //Salida al terminar el decomuento LHEF
   continue;  //Saltar evento en caso de problema
  }

// Store event info in the LHAup object.
    myLHA.setEvent();

    // Write out this event info on the file.
    // With optional argument (verbose =) false the file is smaller.
    myLHA.eventLHEF();
  
 }

pythia.stat();  //Imprime las estadísticas de la corrida get some run statistics, on cross sections and the number of errors and warnings encountered. 

return 0;
}

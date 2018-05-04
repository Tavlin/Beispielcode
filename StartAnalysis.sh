#! /bin/bash
#
#  Powerweek neutrale Pionen
#  Zur Verfügung gestellt von AG Büsching
#  IKF, Goethe Universität Frankfurt

##### Lass uns anfangen!!
##### Die Komentare sollen dir helfen den Code zu verstehen

##### Zuerst initialisieren wir einige Variablen die wir später verwenden
DoWelcome=1 # DoWelcome zum Beispiel regelt die Ausgabe einer kleinen Begrüßung für den Nutzer
##### Variablen sollten immer möglichst selbsterklärend benannt werden
#DoLD_V3_new_final=1 ist kein hilfreicher name

DoToyMC=0
#DoExtractSignal=0
#DoCorrection=1
#DoPlotting=1

##### Dieses Skipt stellt den Startpunkt für uns da
##### je nach Bedarf soll es jedoch andere Prozesse starten
##### mit $1 greift man auf das erste Argument zu, dass man dem skript übergibt (StartAnalysis.sh  xxxxx)
if [[ "$1" == *-*NoWelcome* ]]; then
    DoWelcome=0
    echo "switched off welcome massage"
fi
##### -NoWelcome setzt also die Variable DoWelcome auf 0
##### Dadurch wirst du den Willkommensgruß nicht immer lesen müssen!!




if [[ "$1" == *-*ToyMC* ]]; then
    DoWelcome=0
    DoToyMC=1
fi



if [[ "$1" == *-*all* ]]; then
    DoWelcome=0
    DoToyMC=1
    #DoExtractSignal=1
    #DoCorrection=1
    #DoPlotting=1
fi




if [ $DoWelcome = 1 ] ; then
  echo "*****************************************";
  echo "";
  echo "Hi,";
  echo "Willkommen bei der Powerweek(s)!! :D";
  echo "";
  echo "Dieses Skipt stellt den Startpunkt für uns da.";
  echo "";
  echo "Schau zuerst mal in den Code und versuche ihn zu verstehen.";
  echo "Öffne ihn dafür im Editor deines vertrauens xD.";
  echo "";
  echo "*****************************************";
fi

if [ $DoWelcome = 0 ] ; then
  echo "";
  echo "Starte StartAnalysis.sh...";
  echo $1;
  echo "";
fi


if [ $DoToyMC = 1 ] ; then
  echo "";
  echo "Starte Pi0Simulation.C...";
  rm Pi0Simulation_*
  mkdir -p Simulation  #Neuer Ordner
  mkdir -p Simulation2
  root -q -l -b Pi0Simulation.C\+\(\)
  cd ..
  rm -r Simulation3/
  mv  Beispielcode/Simulation/ Simulation3/
  cd Beispielcode

  mkdir -p Corrected
  rm DetectorRatio_C*
  echo "Starte DetectorRatio.C...";
  root -q -l -b DetectorRatio.C\+\(\)
  cd ..
  rm -r Corrected/
  mv  Beispielcode/Corrected/ Corrected/
  cd Beispielcode



  #root -q -l -b Tset.C\+\(\)
  # Hier wird ein C++ Macro in root aufgerufen
  # Das + bedeutet, dass wir den code kompilieren wollen (.C+),
  #         die \ werden nur verwendet, da einige symbole in bash
  #         "escaped" werden müssen
fi



##################### To Be Modified
#if [ $DoCorrection = 1 ] ; then
#  echo "";
#  echo "Starte Correction.C...";
#  option = "z.B."\,0\,8\,15\,"xD" # irgendeinSetting
#  root -q -l -b  Correction.C\+\(option\)
#fi
#.....

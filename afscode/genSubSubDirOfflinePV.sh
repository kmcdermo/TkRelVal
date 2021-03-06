#! /bin/bash

release=$1
web="https://cmsdoc.cern.ch/Physics/tracking/validation/DATA"

printf "<html>\n" > index.html               
#printf "     <body text=\"#000000\" bgcolor=\"#FFFFFF\" link=\"#FFFF00\" vlink=\"#FF00FF\">\n" >> index.html  
printf "  <title>OfflinePV Distributions</title>\n" >> index.html
printf "     <body>\n" >> index.html  
printf "        <h3> Primary Vertices Distributions (Linear) </h3>\n" >> index.html
printf "           <ul>\n" >> index.html
printf "              <li/><a href=\"%s/%s/OfflinePV/Alignment_lin\">PV Alignment</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/OfflinePV/ResPV_lin\">PV Resolution</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/OfflinePV/ResOtherV_lin\">OtherV Resolution</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/OfflinePV/offlineBS_lin\">Offline Beamspot</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/OfflinePV/offlinePVs_lin\">Offline Primary Vertices</a>\n" ${web} ${release} >> index.html
printf "           </ul>\n" >> index.html
printf "        <h3> Primary Vertices Distributions (Log) </h3>\n" >> index.html
printf "           <ul>\n" >> index.html
printf "              <li/><a href=\"%s/%s/OfflinePV/Alignment_log\">PV Alignment</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/OfflinePV/ResPV_log\">PV Resolution</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/OfflinePV/ResOtherV_log\">OtherV Resolution</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/OfflinePV/offlineBS_log\">Offline Beamspot</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/OfflinePV/offlinePVs_log\">Offline Primary Vertices</a>\n" ${web} ${release} >> index.html
printf "           </ul>\n" >> index.html
printf "     </body>\n" >> index.html
printf "</html>\n" >> index.html

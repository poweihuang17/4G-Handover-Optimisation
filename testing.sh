#!/bin/bash
#COUNTER SEED FUNCTION TTT HYS
COUNTER=0

SEEDARRAY[0]=6476689
SEEDARRAY[1]=5436
SEEDARRAY[2]=324853
SEEDARRAY[3]=24534
SEEDARRAY[4]=5634563
SEEDARRAY[5]=3456374658
SEEDARRAY[6]=123213098
SEEDARRAY[7]=485729385
SEEDARRAY[8]=34543095
SEEDARRAY[9]=54352532
SEEDARRAY[10]=45234523521342
SEEDARRAY[11]=15423456547
SEEDARRAY[12]=4581730598
SEEDARRAY[13]=2347523576
SEEDARRAY[14]=8123749832174
SEEDARRAY[15]=1342341
SEEDARRAY[16]=23452345324
SEEDARRAY[17]=1234243
SEEDARRAY[18]=246255463
SEEDARRAY[19]=123414341254362456
SEEDARRAY[20]=3204823048234
SEEDARRAY[21]=65875686782562
SEEDARRAY[22]=239814578901
SEEDARRAY[23]=5478095134
SEEDARRAY[24]=734562
SEEDARRAY[25]=467254367
SEEDARRAY[26]=365467803
SEEDARRAY[27]=5367850
SEEDARRAY[28]=234769676782
SEEDARRAY[29]=456389050
SEEDARRAY[30]=68934680
SEEDARRAY[31]=78923147798234
SEEDARRAY[32]=8034087650783
SEEDARRAY[33]=1789479432
SEEDARRAY[34]=23456078
SEEDARRAY[35]=12349703789012
SEEDARRAY[36]=3452782378904
SEEDARRAY[37]=7823487902137089234
SEEDARRAY[38]=75447809235789023

for (( i=0; i<=7; i++ ))
do
    for (( COUNTER=0; COUNTER<=4; COUNTER++ ))
    do
    	echo Type: $i Run: $COUNTER
        ./bin/simulation $COUNTER ${SEEDARRAY[$COUNTER]} $i
    done
done

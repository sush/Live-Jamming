#!/bin/bash

CPP_NOGUI="server/*.cpp client/*.cpp core/*.cpp"
INC_NOGUI="server/include/*.h client/include/*.h core/include/*.h"
CPP_GUI="client/gui/livejamming/app/*.cpp"
INC_GUI="client/gui/livejamming/app/*.h"
GREP_LINE=

echo "\###### without GUI"
echo "* CPP only"
wc $CPP_NOGUI |grep total
echo "* CPP+INC only"
wc $CPP_NOGUI $INC_NOGUI|grep total
echo
echo "\###### with GUI"
echo "* CPP only"
wc $CPP_NOGUI $CPP_GUI|grep total
echo "* CPP+INC only"
wc $CPP_NOGUI $INC_NOGUI $CPP_GUI $INC_GUI|grep total

=======
Warning
=======
not compiled with full project to test,
check back in an hour or two ( posted 02:46 am 12/4/2018 )

===========
graph usage
===========
CentralApplication.h should call
void graphMenu(HashTable<Day> daysTable);
with its daysTable

i.e.
#include "graphMenu.h"

graphMenu(this->daysTable);

=======================
files necessary to add:
=======================
graph.h
graphMenu.h
Day.h

=====================
Day.h has been edited
=====================
reason:
need access to fat, carb, prot

change: 
added int return functions getFat(), getCarb, getProt

note:
left functions inline like the getCal() because I was in a rush and getCal() was commented with "only seems to work inline"

================================
graph project file requirements:
================================
everything Hashtable.h needs

===========================
current graph functionality
===========================
View cal/fat/carb/prot by week ( requires at least 1 day )

=================
current graph wip
=================
View average weekly cal/fat/carb/prot ( requires at least 8 days )
need to finish pagination and then copy paste everything

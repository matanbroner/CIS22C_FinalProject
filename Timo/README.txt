========
ISSUE(S)
========
All issues fixed--basically I was treating the hash table like an array when I had to treat it like a hash table...

data:
I realized I'm not displaying data vs calorie target but instead just displaying data and I can't easily just write a whole thing to do that so I'm sticking with just displaying a week of data and displaying averages...

===========
graph usage
===========
CentralApplication.h should call
void graphMenu(HashTable<Day> daysTable);
with its daysTable

i.e.
#include "graphMenu.h"

graphMenu(this->daysTable);

============================
files necessary to add/edit:
============================
graph.h
graphMenu.h
Day.h
CentralApplication.h

files necessary to edit:
CentralApplication.h & Day.h
#include "graphMenu.h"
line 86 in processMenuChoice
std::cout << "[8] - Visualization of logged days data" << std::endl;

line 134 in processMenuChoice
case 8: // graph function
	graphMenu(this->daysTable);
	break;

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
View average weekly cal/fat/carb/prot ( requires at least 8 days )



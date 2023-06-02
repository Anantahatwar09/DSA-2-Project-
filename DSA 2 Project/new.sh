#!/bin/bash

gcc main.c dijkstra.c Heaps.c graph.c
./a.out
python3 ui.py

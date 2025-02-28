//File Name: constants.h
//Author: Liam Campbell
//Date: 2/28/25
//Desc: Declares constants
//Class: CS260
//Assignment: project 4

#ifndef CONSTANTS_H
#define CONSTANTS_H

const int M_CHAR = 101;
const int G_CHAR = 10;
const int GRADES = 5;
const int PROG_W = 25;
const int NAME_W = 20;
const int GNUM_W = 12;
const int STAND_W = 20;
const char STAND[GRADES][20] = { "Unacceptable", "Needs Improvement", "Meets Expectations",
	"Above Expectations", "Exceedingly Good"};
const char FILENAME[13] = "datafile.txt";
const int TOTAL_OPTIONS = 8;
const char OPTIONS[TOTAL_OPTIONS] = {'d', 'm', 'r', 'e', 'g', 'a','q'};
#endif

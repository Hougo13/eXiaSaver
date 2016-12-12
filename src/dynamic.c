//
// Created by hougo on 08/12/16.
//

#include <stdio.h>
#include "../libs/controller2.c"

int main(int argc, char *argv[]) 
{
    
	int i;

	int dec_h=0;
	int dec_m=0;
	int dec_s=0;

	time_t secondes;
    struct tm instant;
    time(&secondes);
    instant=*localtime(&secondes);
    printf("%d:%d:%d\n",instant.tm_hour, instant.tm_min, instant.tm_sec);    

    if(instant.tm_hour >= 20){
    	instant.tm_hour = instant.tm_hour - 20;
    	dec_h = 2;}
    if(instant.tm_hour >= 10 && dec_h == 0)
    {
    	instant.tm_hour = instant.tm_hour - 10;
    	dec_h = 1;}

    if(instant.tm_min >= 50){
    	instant.tm_min = instant.tm_min - 50;
    	dec_m = 5;}
    if(instant.tm_min >= 40 && dec_m == 0){
    	instant.tm_min = instant.tm_min - 40;
    	dec_m = 4;}
    if(instant.tm_min >= 30 && dec_m == 0){
    	instant.tm_min = instant.tm_min - 30;
    	dec_m = 3;}
    if(instant.tm_min >= 20 && dec_m == 0){
    	instant.tm_min = instant.tm_min - 20;
    	dec_m = 2;}
    if(instant.tm_min >= 10 && dec_m == 0){
    	instant.tm_min = instant.tm_min - 10;
    	dec_m = 1;}

    if(instant.tm_sec >= 50){
    	instant.tm_sec = instant.tm_sec - 50;
    	dec_s = 5;}
    if(instant.tm_sec >= 40 && dec_s == 0){
    	instant.tm_sec = instant.tm_sec - 40;
    	dec_s = 4;}
    if(instant.tm_sec >= 30 && dec_s == 0){
    	instant.tm_sec = instant.tm_sec - 30;
    	dec_s = 3;}
    if(instant.tm_sec >= 20 && dec_s == 0){
    	instant.tm_sec = instant.tm_sec - 20;
    	dec_s = 2;}
    if(instant.tm_sec >= 10 && dec_s == 0){
    	instant.tm_sec = instant.tm_sec - 10;
    	dec_s = 1;}


    switch(dec_h)
    {
    	case 0:

    		break;
    	case 1:

    		break;
    	case 2:

    		break;}
    switch(instant.tm_hour)
    {
    	case 0:

    		break;
    	case 1:

    		break;
    	case 2:

    		break;
    	case 3:

    		break;
    	case 4:

    		break;
    	case 5:

    		break;}

    switch(dec_m)
    {
    	case 0:

    		break;
    	case 1:

    		break;
    	case 2:

    		break;
    	case 3:

    		break;
    	case 4:

    		break;
    	case 5:

    		break;}
    switch(instant.tm_min)
    {
    	case 0:

    		break;
    	case 1:

    		break;
    	case 2:

    		break;
    	case 3:

    		break;
    	case 4:

    		break;
    	case 5:

    		break;}

    switch(dec_s)
    {
    	case 0:

    		break;
    	case 1:

    		break;
    	case 2:

    		break;
    	case 3:

    		break;
    	case 4:

    		break;
    	case 5:

    		break;}
    switch(instant.tm_sec)
    {
    	case 0:

    		break;
    	case 1:

    		break;
    	case 2:

    		break;
    	case 3:

    		break;
    	case 4:

    		break;
    	case 5:

    		break;}




    return 0;
}

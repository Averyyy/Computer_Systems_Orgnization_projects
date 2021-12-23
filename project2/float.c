#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "float.h"


int is_special ( float f ) {
    if(isinf(f)||isnan(f) ){
        return 1;
    }else{
        return 0;
    }

}


float get_M  ( float f ) {

    int s = get_s(f);
    int e = get_E(f);

    float result = f/(s*(pow(2,e)));
    if (is_special(f)== 1){
        if (isinf(f)){
            return 0.0; 
            
        }else{ 
        return 0.5;
        }
    }
    return result;
}


int get_s ( float f ) {

	if (f < 0){
        return -1;
    }else{
        return 1;
    }
}



int get_E ( float f ) {
    long eint = fabs(f);
    float efloat = fabs(f) - eint;
    int result = 0;

    if(is_special(f)){
        result = 255;
    }else{

        if (fabs(f) < 1){
          
            while (efloat < 1){
                efloat  = efloat * 2;
                result--;
            } 
        }else{

            while (eint >=1){
            eint = eint/2;
            result++;
            }
        
            result--;  
        }
    }
    
	
    return result;
}













      



    
    

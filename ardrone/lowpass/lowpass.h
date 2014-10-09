
#ifndef _LOWPASS_C
#define _LOWPASS_C

#ifdef __cplusplus
extern "C" {
#endif


/** a kaiser-window lowpass-filter, currently only working for LENGTH=4
* design parameters
* sample_rate=200
* 10 Hz transition width.
* 10 dB attenuation in the stop band
* 25 hz cutoff frequency of the filter.
*/

// do not change 
#define FIR_LENGTH 4

struct lowpass_struct {
  float lastValues[FIR_LENGTH-1];
};

void lowpass_init(struct lowpass_struct *lp);

/** does one filter step
 * @param lp the lowpass structure
 * @param newVal the new value to enter the filter
 * @returns the filtered value */
float lowpass_update(struct lowpass_struct *lp, float newVal);


#ifdef __cplusplus
}
#endif



#endif

#pragma once
/* Misc functions with no dependencies */
//Guess that technically means this is in C, not c++ but w/e
template<class T>
void mMax(T numA, T numB, T &iMin, T &iMax) {
	iMin = (numA > numB) ? numB : numA;
	iMax = (numA > numB) ? numA : numB;
}

template<class T>
bool valueInRange(T value, T min, T max){ 
	return (int(value) >= int(min)) && (int(value) <= int(max)); 
}

template<class T>
bool lValueInRange(T value, T min, T max){ 
	//The -2 and +2 are to correct for fringe cases
	/* Removed the +/- 2 on 4/16/19 */
	return ((int(value) >= int(min)) && (int(value) <= int(max))); 
}

template<class T>
bool lValueInRange(T value, T *min, T *max){ 
	return lValueInRange(int(value), int(*min), int(*max));
}

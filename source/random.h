//Misc functions with no dependencies
//Guess that technically means this is in C, not c++ but w/e
void mMax(int numA, int numB, int &iMin, int &iMax) {
	if (numA >= numB) {
		iMin = numB;
		iMax = numA;
	} else {
		iMin = numA;
		iMax = numB;
	}
}
void mMax(int numA, int numB, float &iMin, float &iMax) {
	if (numA >= numB) {
		iMin = numB;
		iMax = numA;
	} else {
		iMin = numA;
		iMax = numB;
	}
}

bool valueInRange(int value, int min, int max){ 
	return (value >= min) && (value <= max); 
}

bool valueInRange(float value, float min, float max){ 
	return (value >= min) && (value <= max); 
}

bool valueInRange(float value, float *min, float *max){ 
	return (value >= *min) && (value < *max); 
}

bool lValueInRange(float value, float min, float max){ 
	//The -2 and +2 are to correct for fringe cases
	return ((int(value) >= int(min)-2) && (int(value) <= int(max)+2)); 
}

bool lValueInRange(float value, float *min, float *max){ 
	return lValueInRange(int(value), int(*min), int(*max));
}

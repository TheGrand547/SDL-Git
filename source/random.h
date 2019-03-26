//Misc functions with no dependencies
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
	return ((value >= min) && (value <= max)); 
}

bool lValueInRange(float value, float *min, float *max){ 
	return ((value >= *min) && (value <= *max)); 
}

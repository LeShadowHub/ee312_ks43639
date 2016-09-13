/*Sheu Kevin
ks43639
16305
EE312-Assignment 2
*/

#include <stdio.h>

//conversions
const double EUROTOUS = 1.13;
const double USTOEURO = 0.89;
const double POUNDTOGRAM = 453.59237;
const double KILOTOMI = 0.6213712;

int main(void) {

	int selection = 0;
	int exit = 0;

	//variables for functions
	int ausTimeH = 0;
	int ausTimeM = 0;
	int irishTimeH = 0;
	int irishTimeM = 0;
	int usdDollar = 0;
	int usdCents = 0;
	double eur = 0;
	int tempF = 0;
	double tempC = 0;
	double weightKg = 0;
	int weightPound = 0;
	int weightOunce = 0;
	double distKm = 0;
	double distMi = 0;

	//main loop
	while (exit == 0) {
		printf("Enter a number from the menu (1-11) to select a specific conversion to perform or to quit: ");
		scanf("%d", &selection);

		if (selection == 1) {
			printf("Enter Austin time to be converted, expressed in hours and minutes: ");
			scanf("%d%d", &ausTimeH, &ausTimeM);
			time_AtoI(ausTimeH, ausTimeM);
		}
		if (selection == 2) {
			printf("Enter Irish time to be converted, expressed in hours and minutes: ");
			scanf("%d%d", &irishTimeH, &irishTimeM);
			time_ItoA(irishTimeH, irishTimeM);
		}
		if (selection == 3) {
			printf("Enter USD value: ");
			scanf("%d%d", &usdDollar, &usdCents);
			currency_UtoE(usdDollar, usdCents);
		}
		if (selection == 4) {
			printf("Enter EUR value: ");
			scanf("%lf", &eur);
			currency_EtoU(eur);
		}
		if (selection == 5) {
			printf("Enter temperature in Fahrenheit: ");
			scanf("%d", &tempF);
			temp_FtoC(tempF);
		}
		if (selection == 6) {
			printf("Enter temperature in Celsius: ");
			scanf("%lf", &tempC);
			temp_CtoF(tempC);
		}
		if (selection == 7) {
			printf("Enter weight in kg: ");
			scanf("%lf", &weightKg);
			weight_KtoP(weightKg);
		}
		if (selection == 8) {
			printf("Enter weight in pounds and ounces: ");
			scanf("%d%d", &weightPound, &weightOunce);
			weight_PtoK(weightPound, weightOunce);
		}
		if (selection == 9) {
			printf("Enter distances in km: ");
			scanf("%lf", &distKm);
			distance_KtoM(distKm);

		}
		if (selection == 10) {
			printf("Enter distance in miles: ");
			scanf("%lf", &distMi);
			distance_MtoK(distMi);
		}
		if (selection == 11) {
			printf("Good Bye");
			exit = 1;
		}
	}
}

//done
int time_AtoI(int hour,int min) {
	int iHour = (hour + 6)%24;
	if (hour >= 18) {
		printf("The time in Ireland equivalent to %d %d in Austin is %d %d of the next day\n", hour, min, iHour, min);
	}
	else {
		printf("The time in Ireland equivalent to %d %d in Austin is %d %d of the same day\n", hour, min, iHour, min);
	}
	return 0;
}

//done
int time_ItoA(int hour,int min) {
	int aHour = (hour - 6) % 24;
	if (aHour < 0) {
		aHour = aHour + 24;
	}
	if (hour < 6) {
		printf("The time in Ireland equivalent to %d %d in Austin is %d %d of the previous day\n", hour, min, aHour, min);
	}
	else {
		printf("The time in Ireland equivalent to %d %d in Austin is %d %d of the same day\n", hour, min, aHour, min);
	}
	return 0;
}

//done
int currency_UtoE(int dollar,int cents) {
	double totalMoney = (double)dollar + ((double)cents / 100);
	double euro = totalMoney * USTOEURO; 
	printf("EUR value is: %f Euros\n", euro);
	return 0;
}

//done
int currency_EtoU(double value) {
	double totalDollars = (double)value * EUROTOUS; 
	int dollars = totalDollars;
	int cents = (totalDollars - dollars) * 100 + 0.5; 
	printf("USD value is: $%d %d\n", dollars, cents);
	return 0;
}

//done
int temp_FtoC(int temp) {
	double celcius = ((double)temp - 32) * 5 / 9; 
	printf("Temperature in Celsius is: %f\n", celcius);
	return 0;
}

//done
int temp_CtoF(double temp) {
	double hold = (double)temp * 9 / 5 + 32.5; 
	int fahren = hold;
	printf("Temperature in Fahrenheit is: %d\n", fahren);
	return 0;
}

//done
int weight_KtoP(double weight) {
	double totalPounds = weight * 1000 / POUNDTOGRAM;
	int pounds = totalPounds; 
	int ounces = (totalPounds - pounds) * 16 + 0.5; 
	printf("Weight in pounds and ounces is: %d lb %d oz\n", pounds, ounces);
	return 0;
}

//done
int weight_PtoK(int pound,int ounce) {
	double totalWeight = (double)pound + ((double)ounce / 16); 
	double kilo = totalWeight * POUNDTOGRAM / 1000; 
	printf("Weight in kg is: %f kg\n", kilo);
	return 0;
}

//done
int distance_KtoM(double distance) {
	double miles = distance * KILOTOMI;
	printf("Distance in miles is: %f mi\n", miles);
	return 0;
}

//done
int distance_MtoK(double distance) {
	double kilo = distance / KILOTOMI;
	printf("Distance in km is: %f km\n", kilo);
	return 0;
}



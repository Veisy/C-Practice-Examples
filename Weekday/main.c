#include <stdio.h>
#include <stdlib.h>

//We will use anchorday to calculate doomsday, and then doomsday to canlculate weekday. Lastly we will convert day number to name.

//The anchorday is determined due year's divisibility to 400. 
int anchorDayCalculator (int _year) {
	
	int remainder = _year % 400;
	
	if (remainder >= 300)
		return 3;
	else if (remainder >= 200) 
		return 5;
	else if (remainder >= 100) 
		return 0;
	else if (remainder >= 0) 
		return 2;
	else {
		printf("Invalid year.");
		return -1;
	}
}

//The doomsday calculated due to the anchorday and year.
int doomsDayCalculator (int _year, int _anchorDay){
	
	int partA, partB, partC, partD;
	
	partA = (_year%100) / 12;
	partB = (_year%100) % 12;
	partC = partB / 4;
	partD = partA + partB + partC + _anchorDay;
	return (partD % 7);
}

//The weekday calculated due to doomsday, year , mounth and day;
int weekDayCalculator (int _year, int _mounth, int _day, int _doomsDay ) {
	
	int janDay = 3;
	int febDay = 28;

    switch (_mounth) {
        case 1:
            //check if it is a leap day or not for Jan and Feb.
            if ( ((_year%4 == 0) && (_year%100 != 0)) || (_year%400 == 0) ) {
                janDay++;
            }

            if ((_day-janDay) >= 0) {
                return  ((_day-janDay) + _doomsDay) % 7;
            } else {
                return  (7 + _doomsDay - (janDay-_day)%7) % 7;
            }
        case 2:

            if ( ((_year%4 == 0) && (_year%100 != 0)) || (_year%400 == 0) ) {
                febDay++;
            }

            if ((_day-febDay) >= 0) {
                return ((_day-febDay) + _doomsDay) % 7;
            } else {
                return (7 + _doomsDay - (febDay-_day)%7) % 7;
            }
        case 3:
            if ((_day-7) >= 0) {
                return ((_day-7) + _doomsDay) % 7;
            } else {
                return (7 + _doomsDay - (7-_day)%7) % 7;
            }
        case 4:
            if ((_day-4) >= 0) {
                return ((_day-4) + _doomsDay) % 7;
            } else {
                return (7 + _doomsDay - (4-_day)%7) % 7;
            }
        case 5:
            if ((_day-9) >= 0) {
                return ((_day-9) + _doomsDay) % 7;
            } else {
                return (7 + _doomsDay - (9-_day)%7) % 7;
            }
        case 6:
            if ((_day-6) >= 0) {
                return ((_day-6) + _doomsDay) % 7;
            } else {
                return (7 + _doomsDay - (6-_day)%7) % 7;
            }
        case 7:
            if ((_day-11) >= 0) {
                return ((_day-11) + _doomsDay) % 7;
            } else {
                return (7 + _doomsDay - (11-_day)%7) % 7;
            }
        case 8:
            if ((_day-8) >= 0) {
                return ((_day-8) + _doomsDay) % 7;
            } else {
                return (7 + _doomsDay - (8-_day)%7) % 7;
            }
        case 9:
            if ((_day-5) >= 0) {
                return ((_day-5) + _doomsDay) % 7;
            } else {
                return (7 + _doomsDay - (5-_day)%7) % 7;
            }
        case 10:
            if ((_day-10) >= 0) {
                return ((_day-10) + _doomsDay) % 7;
            } else {
                return (7 + _doomsDay - (10-_day)%7) % 7;
            }
        case 11:
            if ((_day-7) >= 0) {
                return ((_day-7) + _doomsDay) % 7;
            } else {
                return (7 + _doomsDay - (7-_day)%7) % 7;
            }
        case 12:
            if ((_day-12) >= 0) {
                return ((_day-12) + _doomsDay) % 7;
            } else {
                return (7 + _doomsDay - (12-_day)%7) % 7;
            }
        default:
            printf("Error! Fix the code.");
            return -1;
    }
}

//The weekday number converted to name.
void NameTheDay (int _weekday) {
	
	switch (_weekday) {
		case 0: 
			printf("It is Sunday!");
			break;
		case 1: 
			printf("It is Monday!");
			break;
		case 2: 
			printf("It is Tuesday!");
			break;
		case 3: 
			printf("It is Wednesday!");
			break;
		case 4: 
			printf("It is Thursday!");
			break;
		case 5: 
			printf("It is Friday!");
			break;
		case 6: 
			printf("It is Saturday!");
			break;
		default: printf("Error! Fix the code.");
	}
	
}

int main() {
	
	int day, mounth, year, 
		anchorDay, doomsDay, weekday;
	
	
	 
	printf("Enter the year : ");
	scanf("%d", &year);
	printf("Enter the mounth as an integer. (For exp. enter 7 for July) : ");
	scanf("%d", &mounth);
	printf("Enter the day as an integer : ");
	scanf("%d", &day);
	
	 anchorDay = anchorDayCalculator(year);
	 doomsDay = doomsDayCalculator(year, anchorDay);
	 weekday = weekDayCalculator(year, mounth, day, doomsDay);
	 NameTheDay(weekday); 
	
	//below code is to prevent console app exiting immediately after execution
	printf("\n");
	system("pause");
	return 0;
}

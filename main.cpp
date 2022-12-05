#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#define CAR 1
#define SCOOTER 2

struct vehicle
{
 int number_vehicle;
 int row_number;
 int col_number;
 int type_vehicle;
};

int parkinfo[4][10];
int vehicle_count;
int carcount;
int scootercount;
void display();
void changecol(struct vehicle *);
struct vehicle *add(int, int, int, int);
void del(struct vehicle *);
void getfreerowcol(int, int *);
void getrcbyinfo(int, int, int *);
void show();

void changecol(struct vehicle *v)
{
 v->col_number = v->col_number - 1;
}

struct vehicle *add(int t, int number_vehicle, int row_number, int col_number)
{
 struct vehicle *v;

 v = (struct vehicle *)malloc(sizeof(struct vehicle));

 v->type_vehicle = t;
 v->row_number = row_number;
 v->col_number = col_number;

 if (t == CAR)
  carcount++;
 else
  scootercount++;

 vehicle_count++;
 parkinfo[row_number][col_number] = number_vehicle;

 return v;
}

void del(struct vehicle *v)
{
 int c;

 for (c = v->col_number; c < 9; c++)
  parkinfo[v->row_number][c] = parkinfo[v->row_number][c + 1];

 parkinfo[v->row_number][c] = 0;

 if (v->type_vehicle == CAR)
  carcount--;
 else
  scootercount--;

 vehicle_count--;
}

void getfreerowcol(int type_vehicle, int *arr)
{
 int r, c, fromrow = 0, torow = 2;

 if (type_vehicle == SCOOTER)
 {
  fromrow += 2;
  torow += 2;
 }

 for (r = fromrow; r < torow; r++)
 {
  for (c = 0; c < 10; c++)
  {
   if (parkinfo[r][c] == 0)
   {
    arr[0] = r;
    arr[1] = c;
    return;
   }
  }
 }

 if (r == 2 || r == 4)
 {
  arr[0] = -1;
  arr[1] = -1;
 }
}

void getrcbyinfo(int type_vehicle, int number_vehicle, int *arr)
{
 int r, c, fromrow = 0, torow = 2;

 if (type_vehicle == SCOOTER)
 {
  fromrow += 2;
  torow += 2;
 }

 for (r = fromrow; r < torow; r++)
 {
  for (c = 0; c < 10; c++)
  {
   if (parkinfo[r][c] == number_vehicle)
   {
    arr[0] = r;
    arr[1] = c;
    return;
   }
  }
 }

 if (r == 2 || r == 4)
 {
  arr[0] = -1;
  arr[1] = -1;
 }
}

void display()
{
 int r, c;

 printf("Cars ->\n");

 for (r = 0; r < 4; r++)
 {
  if (r == 2)
   printf("Scooters ->\n");

  for (c = 0; c < 10; c++)
   printf("%d\t", parkinfo[r][c]);
  printf("\n");
 }
}

int main()
{
 int choice, type_vehicle, number_vehicle, row_number = 0, col_number = 0;
 int i, tarr[2];
 int finish = 1;
 struct vehicle *v;

 struct vehicle *car[2][10];
 struct vehicle *scooter[2][10];

 while (finish)
 {

  printf("\nCar Parking\n");
  printf("1. Arrival of a vehicle\n");
  printf("2. Total no. of vehicles parked\n");
  printf("3. Total no. of cars parked\n");
  printf("4. Total no. of scooters parked\n");
  printf("5. Display order in which vehicles are parked\n");
  printf("6. Departure of vehicle\n");
  printf("7. Exit\n");
  scanf("%d", &choice);

  switch (choice)
  {
  case 1:

   printf("\nAdd: \n");

   type_vehicle = 0;

   while (type_vehicle != CAR && type_vehicle != SCOOTER)
   {
    printf("Enter vehicle type (1 for Car / 2 for Scooter ): \n");
    scanf("%d", &type_vehicle);
    if (type_vehicle != CAR && type_vehicle != SCOOTER)
     printf("\nInvalid vehicle type.\n");
   }

   printf("Enter vehicle number_vehicle: ");
   scanf("%d", &number_vehicle);

   if (type_vehicle == CAR || type_vehicle == SCOOTER)
   {
    getfreerowcol(type_vehicle, tarr);

    if (tarr[0] != -1 && tarr[1] != -1)
    {
     row_number = tarr[0];
     col_number = tarr[1];

     if (type_vehicle == CAR)
      car[row_number][col_number] = add(type_vehicle, number_vehicle, row_number, col_number);
     else
      scooter[row_number - 2][col_number] = add(type_vehicle, number_vehicle, row_number, col_number);
     ;
    }
    else
    {
     if (type_vehicle == CAR)
      printf("\nNo parking slot free to park a car\n");
     else
      printf("\nNo parking slot free to park a scooter\n");
    }
   }
   else
   {
    printf("Invalid type_vehicle\n");
    break;
   }

   printf("\nPress any key to continue...");
   getch();
   break;

  case 2:

   printf("Total vehicles parked: %d\n", vehicle_count);
   printf("\nPress any key to continue...");
   getch();
   break;

  case 3:

   printf("Total cars parked: %d\n", carcount);

   printf("\nPress any key to continue...");
   getch();
   break;

  case 4:

   printf("Total scooters parked: %d\n", scootercount);
   printf("\nPress any key to continue...");
   getch();
   break;

  case 5:

   printf("Display\n");
   display();

   printf("\nPress any key to continue...");
   getch();
   break;

  case 6:

   printf("Departure\n");

   type_vehicle = 0;

   while (type_vehicle != CAR && type_vehicle != SCOOTER)
   {
    printf("Enter vehicle type_vehicle (1 for Car / 2 for Scooter ): \n");
    scanf("%d", &type_vehicle);
    if (type_vehicle != CAR && type_vehicle != SCOOTER)
     printf("\nInvalid vehicle type_vehicle.\n");
   }
   printf("Enter number_vehicle: ");
   scanf("%d", &number_vehicle);

   if (type_vehicle == CAR || type_vehicle == SCOOTER)
   {
    getrcbyinfo(type_vehicle, number_vehicle, tarr);
    if (tarr[0] != -1 && tarr[1] != -1)
    {
     col_number = tarr[1];

     if (type_vehicle == CAR)
     {
      row_number = tarr[0];
      del(car[row_number][col_number]);
      for (i = col_number; i < 9; i++)
      {
       car[row_number][i] = car[row_number][i + 1];
       changecol(car[row_number][i]);
      }
      free(car[row_number][i]);
      car[row_number][i] = NULL;
     }

     else
     {
      row_number = tarr[0] - 2;
      if (!(row_number < 0))
      {
       del(scooter[row_number][col_number]);
       for (i = col_number; i < 9; i++)
       {
        scooter[row_number][i] = scooter[row_number][i + 1];
        changecol(scooter[row_number][col_number]);
       }
       scooter[row_number][i] = NULL;
      }
     }
    }
    else
    {
     if (type_vehicle == CAR)
      printf("\nInvalid car number_vehicle, or a car with such number_vehicle has not been parked here.\n");
     else
      printf("\nInvalid scooter number_vehicle, or a scooter with such number_vehicle has not been parked here.\n");
    }
   }

   printf("\nPress any key to continue...");
   getch();
   break;

  case 7:

   for (row_number = 0; row_number < 2; row_number++)
   {
    for (col_number = 0; col_number < 10; col_number++)
    {
     if (car[row_number][col_number]->number_vehicle != 0)
      free(car[row_number][col_number]);
     if (scooter[row_number][col_number]->number_vehicle != 0)
      free(scooter[row_number + 2][col_number]);
    }
   }
   finish = 0;
   break;
  }
 }
 return 0;
}



#include <stdio.h>
#include <math.h>
#define pi 3.1415926

int main(int argc, const char * argv[]) {
    double radius, area;
    printf("Make Changes");
    printf("This is a test comment\n");
    printf("Enter the radius:\n");
    scanf("%lf",&radius);
    area=pi*pow(radius, 2);//use power function to calculate the area of given radius
    printf("Area of radius=%lf is %.2lf\n",radius,area);
    
    
}
